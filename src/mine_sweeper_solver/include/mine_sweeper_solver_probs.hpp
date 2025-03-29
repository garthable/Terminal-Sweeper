#pragma once

#include "mine_sweeper_solver.hpp"
#include "mine_sweeper_solver_probs.hpp"

#include <vector>

namespace slvr
{
    namespace group
    {

    struct TileWithAdjs
    {
        TileWithAdjs() : size{0} {}
        std::array<mswp::BoardIndex, 8> adjTiles;
        mswp::BoardIndex tileIndex;
        uint8_t size;
    };

    struct TileGroup
    {
        TileGroup() : size{0} 
        {
            std::fill(bombFrequency.begin(), bombFrequency.end(), 0);
        }
        TileGroup(std::initializer_list<mswp::BoardIndex> indices) :
            size{indices.size()}
        {
            for (int32_t i = 0; i < size; i++)
            {
                tiles[i].tileIndex = *(indices.begin() + i);
            }
            std::fill(bombFrequency.begin(), bombFrequency.end(), 0);
        }
        std::array<TileWithAdjs, MSWP_MAX_TILES> tiles;
        std::array<uint32_t, MSWP_MAX_TILES> bombFrequency;
        mswp::BoardSize size;
    };

    void findHiddenTiles(mswp::BoardIndex centerTileIndex, const MineSweeperSolver& solver, BoardBitMap& outVisited, TileGroup& outGroup);
    void findVisibleTiles(mswp::BoardIndex centerTileIndex, const MineSweeperSolver& solver, BoardBitMap& outVisited, TileGroup& outGroup);
    void groupTiles(MineSweeperSolver& outSolver);

    } // namespace group end

void sortByCombinationCount(const MineSweeperSolver& solver, group::TileGroup& outTileGroup);
void computeProbabilities(group::TileGroup& outTileGroup, MineSweeperSolver& outSolver, BoardBitMap& outBombLocations, uint32_t& outSolutionCount, const mswp::BoardIndex i = 0, const uint8_t bombsInSolution = 0);

} // namespace slvr end