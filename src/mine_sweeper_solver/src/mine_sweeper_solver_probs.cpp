#include "mine_sweeper_solver_probs.hpp"
#include "util.hpp"
#include "log.hpp"

namespace slvr
{

    namespace group
    {

    void findHiddenTiles(mswp::BoardIndex centerVisibleTileIndex, const MineSweeperSolver& solver, BoardBitMap& outVisited, TileGroup& outGroup)
    {
        outVisited[centerVisibleTileIndex] = true;
        outGroup.tiles[outGroup.size].tileIndex = centerVisibleTileIndex;
        outGroup.size += 1;
        util::applyFuncToAdjObjects<MineSweeperSolver, Tile>(centerVisibleTileIndex, solver, 
        [&](int32_t i, const Tile& tile)
        {
            if (!tile.hidden() || tile.bombProb == 1 || outVisited[i])
            {
                return;
            }
            findVisibleTiles(i, solver, outVisited, outGroup);
        });
    }

    void findVisibleTiles(mswp::BoardIndex centerTileIndex, const MineSweeperSolver& solver, BoardBitMap& outVisited, TileGroup& outGroup)
    {
        outVisited[centerTileIndex] = true;
        util::applyFuncToAdjObjects<MineSweeperSolver, Tile>(centerTileIndex, solver, 
        [&](int32_t i, const Tile& tile)
        {
            if (tile.hidden() || tile.adjBombs == 0 || tile.bombProb == 1 || outVisited[i])
            {
                return;
            }
            findHiddenTiles(i, solver, outVisited, outGroup);
        });
    }

    void groupTiles(MineSweeperSolver& outSolver)
    {
        BoardBitMap visited;
        TileGroup tileGroup;
        outSolver.applyFuncToAll(
        [&](mswp::BoardIndex i, Tile& tile) 
        {
            // Disgards invalid starting tiles (0, #, @)
            if (visited[i] || tile.hidden() || tile.adjBombs == 0 || tile.bombProb == 1)
            {
                return;
            }

            // Goes back and forth between find visible and 
            // find hidden tiles until a group has been fully 
            // created.
            findHiddenTiles(i, outSolver, visited, tileGroup);
            // Sorts combination count such that branches end 
            // earlier in NP computeProbabilities call.
            sortByCombinationCount(outSolver, tileGroup);
            // NP computeProbabilities call.
            computeProbabilities(tileGroup, outSolver);
        });
    }

    } // namespace group end

inline uint8_t* getHardcodedCombinations(uint8_t r)
{
    static uint8_t hardCodedCombinations[] = {0, 1, 2, 3, 4, 5, 6, 7, 9, 1, 0, 2, 0, 2, 1, 3, 0, 3, 1, 3, 2, 4, 0, 4, 1, 4, 2, 4, 3, 5, 0, 5, 1, 5, 2, 5, 3, 5, 4, 6, 0, 6, 1, 6, 2, 6, 3, 6, 4, 6, 5, 7, 0, 7, 1, 7, 2, 7, 3, 7, 4, 7, 5, 7, 6, 9, 2, 1, 0, 3, 1, 0, 3, 2, 0, 3, 2, 1, 4, 1, 0, 4, 2, 0, 4, 2, 1, 4, 3, 0, 4, 3, 1, 4, 3, 2, 5, 1, 0, 5, 2, 0, 5, 2, 1, 5, 3, 0, 5, 3, 1, 5, 3, 2, 5, 4, 0, 5, 4, 1, 5, 4, 2, 5, 4, 3, 6, 1, 0, 6, 2, 0, 6, 2, 1, 6, 3, 0, 6, 3, 1, 6, 3, 2, 6, 4, 0, 6, 4, 1, 6, 4, 2, 6, 4, 3, 6, 5, 0, 6, 5, 1, 6, 5, 2, 6, 5, 3, 6, 5, 4, 7, 1, 0, 7, 2, 0, 7, 2, 1, 7, 3, 0, 7, 3, 1, 7, 3, 2, 7, 4, 0, 7, 4, 1, 7, 4, 2, 7, 4, 3, 7, 5, 0, 7, 5, 1, 7, 5, 2, 7, 5, 3, 7, 5, 4, 7, 6, 0, 7, 6, 1, 7, 6, 2, 7, 6, 3, 7, 6, 4, 7, 6, 5, 9, 3, 2, 1, 0, 4, 2, 1, 0, 4, 3, 1, 0, 4, 3, 2, 0, 4, 3, 2, 1, 5, 2, 1, 0, 5, 3, 1, 0, 5, 3, 2, 0, 5, 3, 2, 1, 5, 4, 1, 0, 5, 4, 2, 0, 5, 4, 2, 1, 5, 4, 3, 0, 5, 4, 3, 1, 5, 4, 3, 2, 6, 2, 1, 0, 6, 3, 1, 0, 6, 3, 2, 0, 6, 3, 2, 1, 6, 4, 1, 0, 6, 4, 2, 0, 6, 4, 2, 1, 6, 4, 3, 0, 6, 4, 3, 1, 6, 4, 3, 2, 6, 5, 1, 0, 6, 5, 2, 0, 6, 5, 2, 1, 6, 5, 3, 0, 6, 5, 3, 1, 6, 5, 3, 2, 6, 5, 4, 0, 6, 5, 4, 1, 6, 5, 4, 2, 6, 5, 4, 3, 7, 2, 1, 0, 7, 3, 1, 0, 7, 3, 2, 0, 7, 3, 2, 1, 7, 4, 1, 0, 7, 4, 2, 0, 7, 4, 2, 1, 7, 4, 3, 0, 7, 4, 3, 1, 7, 4, 3, 2, 7, 5, 1, 0, 7, 5, 2, 0, 7, 5, 2, 1, 7, 5, 3, 0, 7, 5, 3, 1, 7, 5, 3, 2, 7, 5, 4, 0, 7, 5, 4, 1, 7, 5, 4, 2, 7, 5, 4, 3, 7, 6, 1, 0, 7, 6, 2, 0, 7, 6, 2, 1, 7, 6, 3, 0, 7, 6, 3, 1, 7, 6, 3, 2, 7, 6, 4, 0, 7, 6, 4, 1, 7, 6, 4, 2, 7, 6, 4, 3, 7, 6, 5, 0, 7, 6, 5, 1, 7, 6, 5, 2, 7, 6, 5, 3, 7, 6, 5, 4, 9, 4, 3, 2, 1, 0, 5, 3, 2, 1, 0, 5, 4, 2, 1, 0, 5, 4, 3, 1, 0, 5, 4, 3, 2, 0, 5, 4, 3, 2, 1, 6, 3, 2, 1, 0, 6, 4, 2, 1, 0, 6, 4, 3, 1, 0, 6, 4, 3, 2, 0, 6, 4, 3, 2, 1, 6, 5, 2, 1, 0, 6, 5, 3, 1, 0, 6, 5, 3, 2, 0, 6, 5, 3, 2, 1, 6, 5, 4, 1, 0, 6, 5, 4, 2, 0, 6, 5, 4, 2, 1, 6, 5, 4, 3, 0, 6, 5, 4, 3, 1, 6, 5, 4, 3, 2, 7, 3, 2, 1, 0, 7, 4, 2, 1, 0, 7, 4, 3, 1, 0, 7, 4, 3, 2, 0, 7, 4, 3, 2, 1, 7, 5, 2, 1, 0, 7, 5, 3, 1, 0, 7, 5, 3, 2, 0, 7, 5, 3, 2, 1, 7, 5, 4, 1, 0, 7, 5, 4, 2, 0, 7, 5, 4, 2, 1, 7, 5, 4, 3, 0, 7, 5, 4, 3, 1, 7, 5, 4, 3, 2, 7, 6, 2, 1, 0, 7, 6, 3, 1, 0, 7, 6, 3, 2, 0, 7, 6, 3, 2, 1, 7, 6, 4, 1, 0, 7, 6, 4, 2, 0, 7, 6, 4, 2, 1, 7, 6, 4, 3, 0, 7, 6, 4, 3, 1, 7, 6, 4, 3, 2, 7, 6, 5, 1, 0, 7, 6, 5, 2, 0, 7, 6, 5, 2, 1, 7, 6, 5, 3, 0, 7, 6, 5, 3, 1, 7, 6, 5, 3, 2, 7, 6, 5, 4, 0, 7, 6, 5, 4, 1, 7, 6, 5, 4, 2, 7, 6, 5, 4, 3, 9, 5, 4, 3, 2, 1, 0, 6, 4, 3, 2, 1, 0, 6, 5, 3, 2, 1, 0, 6, 5, 4, 2, 1, 0, 6, 5, 4, 3, 1, 0, 6, 5, 4, 3, 2, 0, 6, 5, 4, 3, 2, 1, 7, 4, 3, 2, 1, 0, 7, 5, 3, 2, 1, 0, 7, 5, 4, 2, 1, 0, 7, 5, 4, 3, 1, 0, 7, 5, 4, 3, 2, 0, 7, 5, 4, 3, 2, 1, 7, 6, 3, 2, 1, 0, 7, 6, 4, 2, 1, 0, 7, 6, 4, 3, 1, 0, 7, 6, 4, 3, 2, 0, 7, 6, 4, 3, 2, 1, 7, 6, 5, 2, 1, 0, 7, 6, 5, 3, 1, 0, 7, 6, 5, 3, 2, 0, 7, 6, 5, 3, 2, 1, 7, 6, 5, 4, 1, 0, 7, 6, 5, 4, 2, 0, 7, 6, 5, 4, 2, 1, 7, 6, 5, 4, 3, 0, 7, 6, 5, 4, 3, 1, 7, 6, 5, 4, 3, 2, 9, 6, 5, 4, 3, 2, 1, 0, 7, 5, 4, 3, 2, 1, 0, 7, 6, 4, 3, 2, 1, 0, 7, 6, 5, 3, 2, 1, 0, 7, 6, 5, 4, 2, 1, 0, 7, 6, 5, 4, 3, 1, 0, 7, 6, 5, 4, 3, 2, 0, 7, 6, 5, 4, 3, 2, 1, 7, 6, 5, 4, 3, 2, 1, 0};
    static uint16_t rToIndex[] = {0, 0, 9, 66, 235, 516, 797, 966, 1022};
    return &hardCodedCombinations[rToIndex[r]];
}

inline uint8_t getHardcodedCombinationsSize(uint8_t n, uint8_t r)
{
    static uint8_t hardCodedSize[] = {1, 2, 1, 3, 3, 1, 4, 6, 4, 1, 5, 10, 10, 5, 1, 6, 15, 20, 15, 6, 1, 7, 21, 35, 35, 21, 7, 1, 8, 28, 56, 70, 56, 28, 8, 1};
    const uint8_t k = n*(n+1)/2 + r;
    return hardCodedSize[k];
}

void sortByCombinationCount(const MineSweeperSolver& solver, group::TileGroup& outTileGroup)
{
    BoardBitMap claimed;
    for (mswp::BoardIndex i = 0; i < outTileGroup.size; i++)
    {
        // Finds max combination size
        mswp::BoardIndex maxIndex = 0;
        uint8_t maxCombinationSize = 0;
        for (mswp::BoardIndex j = i; j < outTileGroup.size; j++)
        {
            group::TileWithAdjs& tile = outTileGroup.tiles[j];

            uint8_t n = 0;

            util::applyFuncToAdjObjects<MineSweeperSolver, Tile>(tile.tileIndex, solver, 
            [&](int32_t adjIndex, const Tile& inTile) 
            {
                n += inTile.hidden() && !claimed[adjIndex];
            });
            uint8_t combinationSize = getHardcodedCombinationsSize(n, solver[tile.tileIndex].adjBombs);
            LOG_INFO(static_cast<int>(n) << " " << static_cast<int>(solver[tile.tileIndex].adjBombs) << " = " << static_cast<int>(combinationSize));
            if (combinationSize > maxCombinationSize)
            {
                maxCombinationSize = combinationSize;
                maxIndex = j;
            }
        }

        LOG_INFO(static_cast<int>(maxIndex) << " " << static_cast<int>(maxCombinationSize));

        // Moves tile to front
        util::swap(outTileGroup.tiles[maxIndex].tileIndex, outTileGroup.tiles[i].tileIndex);

        group::TileWithAdjs& tile = outTileGroup.tiles[i];

        // Claims tiles
        util::applyFuncToAdjObjects<MineSweeperSolver, Tile>(tile.tileIndex, solver, 
        [&](int32_t adjIndex, const Tile& inTile) 
        {
            if (claimed[adjIndex] || !inTile.hidden())
            {
                return;
            }
            tile.adjTiles[tile.size] = adjIndex;
            tile.size++;
            claimed[adjIndex] = true;
        });
    }
}

void computeProbabilities(const group::TileGroup& tileGroup, MineSweeperSolver& outSolver)
{
    
}

} // namespace slvr end