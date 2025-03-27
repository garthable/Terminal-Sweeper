#include "mine_sweeper_solver_functions.hpp"
#include "util.hpp"
#include "log.hpp"

namespace slvr
{

void useActionArrays(ActionArray& outClicks, ActionArray& outFlags, mswp::MineSweeper& outBoard)
{
    for (mswp::BoardIndex i = 0; i < outClicks.actionSize; i++)
    {
        outBoard.click(outClicks.actions[i]);
    }
    outClicks.actionSize = 0;
    for (mswp::BoardIndex i = 0; i < outFlags.actionSize; i++)
    {
        outBoard.flag(outFlags.actions[i]);
    }
    outFlags.actionSize = 0;
}

void lazySolve(MineSweeperSolver& outSolver, ActionArray& outClicks, ActionArray& outFlags)
{
    BoardBitMap isModified;

    outSolver.applyFuncToModified(
    [&outSolver, &outClicks, &outFlags, &isModified](const mswp::BoardIndex i, Tile& outCenterTile) 
    {
        auto width = outSolver.width();
        auto size = outSolver.size();
        auto& tiles = outSolver.tiles();

        /* Flags all adj hidden tiles if adjBombs and adjHidden are equal.
         * 
         * Example:
         * 
         * # # #
         * 2 3 2
         * 
         * '3' has 3 adjHidden tiles and 3 adjBombs.
         * Both 2's have 2 adjHidden tiles and 2 adjBombs.
         *   
         * @ @ @
         * 2 3 2
         * 
         * This allows lazySolve to flag those tiles.
         */
        if (outCenterTile.adjBombs == outCenterTile.adjUnknowns)
        {
            util::applyFuncToAdjObjects<Tiles, Tile>(i, width, size, tiles, 
            [&outSolver, &outFlags, &isModified](int32_t i, Tile& outAdjTile) 
            {
                if (outAdjTile.hidden() && !isModified[i] && outFlags.actionSize < SLVR_ACTION_BUFFER_SIZE)
                {
                    isModified[i] = true;
                    outFlags.actions[outFlags.actionSize] = i;
                    outFlags.actionSize++;
                }
            });
        }
        /**
         * Clicks on all hidden tiles if number of adjBombs is zero
         * 
         * Example:
         * 
         * # # 1
         * @ 2 @
         * 
         * The '1' and '2' both effectively become zero due to flagged tiles.
         * 
         * 1 2 1
         * @ 2 @
         * 
         * This allows lazySolve to click the hidden tiles!
         * 
         */
        else if (outCenterTile.adjBombs == 0)
        {
            util::applyFuncToAdjObjects<Tiles, Tile>(i, width, size, tiles, 
            [&outSolver, &outClicks, &isModified](int32_t i, Tile& outAdjTile) 
            {
                if (outAdjTile.hidden() && !isModified[i] && outClicks.actionSize < SLVR_ACTION_BUFFER_SIZE)
                {
                    outClicks.actions[outClicks.actionSize] = i;
                    outClicks.actionSize++;
                    isModified[i] = true;
                }
            });
        }
    });
}

struct IntersectionAndDifference
{
    IntersectionAndDifference() : intersectionCount{0}, differenceCenterCount{0}, differenceAdjCount{0} {}

    std::array<mswp::BoardIndex, 8> intersection;
    std::array<mswp::BoardIndex, 8> differenceCenter;
    std::array<mswp::BoardIndex, 8> differenceAdj;

    uint8_t intersectionCount;
    uint8_t differenceCenterCount;
    uint8_t differenceAdjCount;
};

IntersectionAndDifference getIntersectionAndDifference(const BoardBitMap& boardBitMapCenter, const BoardBitMap& boardBitMapAdj, 
                                                       const MineSweeperSolver& solver, mswp::BoardIndex centerIndex, mswp::BoardIndex adjIndex)
{
    IntersectionAndDifference interAndDiff;
    util::applyFuncToAdjObjects<Tiles, Tile>(adjIndex, solver.width(), solver.size(), solver.tiles(),
    [&boardBitMapCenter, &interAndDiff](int32_t index, const Tile& tile)
    {
        if (tile.hidden())
        {
            // Intersection
            if (boardBitMapCenter[index] && interAndDiff.intersectionCount < 8)
            {
                interAndDiff.intersection[interAndDiff.intersectionCount] = index;
                interAndDiff.intersectionCount++;
            }
            // Adj Difference
            else if (interAndDiff.differenceAdjCount < 8)
            {
                interAndDiff.differenceAdj[interAndDiff.differenceAdjCount] = index;
                interAndDiff.differenceAdjCount++;
            }
        }
    });

    util::applyFuncToAdjObjects<Tiles, Tile>(centerIndex, solver.width(), solver.size(), solver.tiles(),
    [&boardBitMapAdj, &interAndDiff](int32_t index, const Tile& tile)
    {
        // Center Difference
        if (!boardBitMapAdj[index] && tile.hidden() && interAndDiff.differenceCenterCount < 8)
        {
            interAndDiff.differenceCenter[interAndDiff.differenceCenterCount] = index;
            interAndDiff.differenceCenterCount++;
        }
    });

    return interAndDiff;
}

void applyActionIntersection(uint8_t count, const std::array<mswp::BoardIndex, 8>& indicies, ActionArray& outAction, BoardBitMap& outClickedOrFlagged)
{
    for (int8_t i = 0; i < count; i++)
    {
        if (outClickedOrFlagged[indicies[i]] && outAction.actionSize < SLVR_ACTION_BUFFER_SIZE)
        {
            continue;
        }
        outClickedOrFlagged[indicies[i]] = true;
        outAction.actions[outAction.actionSize] = indicies[i];
        outAction.actionSize++;
    }
}

void intersectionSolver(MineSweeperSolver& outSolver, ActionArray& outClicks, ActionArray& outFlags)
{
    outClicks.actionSize = 0;
    outFlags.actionSize = 0;
    BoardBitMap clickedOrFlagged;
    outSolver.applyFuncToModified(
    [&](const mswp::BoardIndex centerIndex, Tile& centerTile) 
    {
        if (centerTile.hidden())
        {
            return;
        }
        auto width = outSolver.width();
        auto size = outSolver.size();
        auto& tiles = outSolver.tiles();
        BoardBitMap presentInCenterTile;
        util::applyFuncToAdjObjects<Tiles, Tile>(centerIndex, outSolver.width(), outSolver.size(), outSolver.tiles(),
        [&presentInCenterTile](int32_t index, Tile& tile)
        {
            presentInCenterTile[index] = true;
        });
        /**
         * 
         * # 3 1 #
         * # # # #
         * 
         * By splitting the board up based off visible tile intersection we can solve more complex puzzles.
         * 
         * A 3 1 B
         * A $ $ B
         * 
         * Since 3 only has two A's we know that 1 must be in $. 
         * Because of this we know that B is free to click. 
         * We also know that A's can be flagged since its restricted to that amount. 
         * 
         */
        util::applyFuncToAdjObjects<Tiles, Tile>(centerIndex, width, size, tiles, 
        [&](int32_t adjIndex, Tile& adjTile) 
        {
            if (adjTile.hidden())
            {
                return;
            }
            BoardBitMap presentInAdjTile;

            util::applyFuncToAdjObjects<Tiles, Tile>(adjIndex, outSolver.width(), outSolver.size(), outSolver.tiles(),
            [&presentInAdjTile](int32_t index, Tile& tile)
            {
                presentInAdjTile[index] = true;
            });

            auto interAndDiff = getIntersectionAndDifference(presentInCenterTile, presentInAdjTile, outSolver, centerIndex, adjIndex);

            int8_t minAmountOfBombsCenter = std::max(centerTile.adjBombs - interAndDiff.intersectionCount, 0);
            int8_t minAmountOfBombsAdj = std::max(adjTile.adjBombs - interAndDiff.intersectionCount, 0);

            int8_t maxAmountOfBombsCenter = std::min(static_cast<int>(centerTile.adjBombs), static_cast<int>(interAndDiff.differenceCenterCount));
            int8_t maxAmountOfBombsAdj = std::min(static_cast<int>(adjTile.adjBombs), static_cast<int>(interAndDiff.differenceAdjCount));

            int8_t minAmountOfBombsInter = std::max(centerTile.adjBombs - maxAmountOfBombsCenter, centerTile.adjBombs - maxAmountOfBombsCenter);
            int8_t maxAmountOfBombsInter = std::min(centerTile.adjBombs - minAmountOfBombsCenter, centerTile.adjBombs - minAmountOfBombsCenter);

            int8_t maxBombsInDiffCenter = centerTile.adjBombs - minAmountOfBombsInter;
            int8_t maxBombsInDiffAdj = adjTile.adjBombs - minAmountOfBombsInter;

            int8_t minBombsInDiffCenter = centerTile.adjBombs - maxAmountOfBombsInter;
            int8_t minBombsInDiffAdj = adjTile.adjBombs - maxAmountOfBombsInter;

            // Click entire intersection
            if (maxAmountOfBombsInter == 0 && interAndDiff.intersectionCount != 0)
            {
                applyActionIntersection(interAndDiff.intersectionCount, interAndDiff.intersection, outClicks, clickedOrFlagged);
            }
            // Flag entire intersection
            else if (minAmountOfBombsInter == interAndDiff.intersectionCount && interAndDiff.intersectionCount != 0)
            {
                applyActionIntersection(interAndDiff.intersectionCount, interAndDiff.intersection, outFlags, clickedOrFlagged);
            }

            // Click entire center difference
            if (maxBombsInDiffCenter == 0 && interAndDiff.differenceCenterCount != 0)
            {
                applyActionIntersection(interAndDiff.differenceCenterCount, interAndDiff.differenceCenter, outClicks, clickedOrFlagged);
            }
            // Flag entire center difference
            else if (minBombsInDiffCenter == interAndDiff.differenceCenterCount && interAndDiff.differenceCenterCount != 0)
            {
                applyActionIntersection(interAndDiff.differenceCenterCount, interAndDiff.differenceCenter, outFlags, clickedOrFlagged);
            }

            // Click entire adj difference
            if (maxBombsInDiffAdj == 0 && interAndDiff.differenceAdjCount != 0)
            {
                applyActionIntersection(interAndDiff.differenceAdjCount, interAndDiff.differenceAdj, outClicks, clickedOrFlagged);
            }
            // Flag entire adj difference
            else if (minBombsInDiffAdj == interAndDiff.differenceAdjCount && interAndDiff.differenceAdjCount != 0)
            {
                applyActionIntersection(interAndDiff.differenceAdjCount, interAndDiff.differenceAdj, outFlags, clickedOrFlagged);
            }
        });
    });
}

};