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
    IntersectionAndDifference() : intersection{0}, differenceCenterCount{0}, differenceAdjCount{0} {}

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
            if (boardBitMapCenter[index])
            {
                interAndDiff.intersection[interAndDiff.intersectionCount] = index;
                interAndDiff.intersectionCount++;
            }
            else
            {
                interAndDiff.differenceCenter[interAndDiff.differenceCenterCount] = index;
                interAndDiff.differenceCenterCount++;
            }
        }
    });
    util::applyFuncToAdjObjects<Tiles, Tile>(centerIndex, solver.width(), solver.size(), solver.tiles(),
    [&boardBitMapAdj, &interAndDiff](int32_t index, const Tile& tile)
    {
        if (!boardBitMapAdj[index] && tile.hidden())
        {
            interAndDiff.differenceCenter[interAndDiff.differenceCenterCount] = index;
            interAndDiff.differenceCenterCount++;
        }
    });
    return interAndDiff;
}

void intersectionSolver(MineSweeperSolver& outSolver, ActionArray& outClicks, ActionArray& outFlags)
{
    outSolver.applyFuncToModified(
    [&outSolver, &outClicks, &outFlags](const mswp::BoardIndex centerIndex, Tile& centerTile) 
    {
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
        [&centerTile, &centerIndex, &outSolver, &presentInCenterTile, &outClicks, &outFlags](int32_t adjIndex, Tile& adjTile) 
        {
            BoardBitMap presentInAdjTile;
            util::applyFuncToAdjObjects<Tiles, Tile>(adjIndex, outSolver.width(), outSolver.size(), outSolver.tiles(),
            [&presentInAdjTile](int32_t index, Tile& tile)
            {
                presentInAdjTile[index] = true;
            });
            auto interAndDiff = getIntersectionAndDifference(presentInCenterTile, presentInAdjTile, outSolver, centerIndex, adjIndex);

            int8_t minAmountOfBombsCenter = std::max(centerTile.adjBombs - interAndDiff.differenceCenterCount, 0);
            int8_t minAmountOfBombsAdj = std::max(adjTile.adjBombs - interAndDiff.differenceAdjCount, 0);
            int8_t minAmountOfBombsInter = std::max(minAmountOfBombsCenter, minAmountOfBombsAdj);

            int8_t bombsInDiffCenter = centerTile.adjBombs - minAmountOfBombsInter;
            int8_t bombsInDiffAdj = adjTile.adjBombs - minAmountOfBombsInter;

            if (interAndDiff.intersectionCount == minAmountOfBombsInter)
            {
                for (int8_t i = 0; i < interAndDiff.intersectionCount; i++)
                {
                    outFlags.actions[outFlags.actionSize] = interAndDiff.intersection[i];
                    outFlags.actionSize++;
                }
            }

            if (bombsInDiffCenter == 0)
            {
                for (int8_t i = 0; i < interAndDiff.differenceCenterCount; i++)
                {
                    outClicks.actions[outClicks.actionSize] = interAndDiff.differenceCenter[i];
                    outClicks.actionSize++;
                }
            }
            else if (bombsInDiffCenter == interAndDiff.differenceCenterCount)
            {
                for (int8_t i = 0; i < interAndDiff.differenceCenterCount; i++)
                {
                    outFlags.actions[outFlags.actionSize] = interAndDiff.differenceCenter[i];
                    outFlags.actionSize++;
                }
            }
            if (bombsInDiffAdj == 0)
            {
                for (int8_t i = 0; i < interAndDiff.differenceAdjCount; i++)
                {
                    outClicks.actions[outClicks.actionSize] = interAndDiff.differenceAdj[i];
                    outClicks.actionSize++;
                }
            }
            else if (bombsInDiffAdj == interAndDiff.differenceAdjCount)
            {
                for (int8_t i = 0; i < interAndDiff.differenceAdjCount; i++)
                {
                    outFlags.actions[outFlags.actionSize] = interAndDiff.differenceAdj[i];
                    outFlags.actionSize++;
                }
            }
        });
    });
}

};