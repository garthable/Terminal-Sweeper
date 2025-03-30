#pragma once

#include "mine_sweeper_solver.hpp"
#include "mine_sweeper_solver_probs.hpp"

#include "solution_set.hpp"

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

        }
        TileGroup(std::initializer_list<mswp::BoardIndex> indices) :
            size{static_cast<mswp::BoardSize>(indices.size())}
        {
            for (int32_t i = 0; i < size; i++)
            {
                tiles[i].tileIndex = *(indices.begin() + i);
            }
        }
        std::array<TileWithAdjs, MSWP_MAX_TILES> tiles;
        mswp::BoardSize size;
    };

    void findHiddenTiles(mswp::BoardIndex centerTileIndex, const MineSweeperSolver& solver, BoardBitMap& outVisited, TileGroup& outGroup);
    void findVisibleTiles(mswp::BoardIndex centerTileIndex, const MineSweeperSolver& solver, BoardBitMap& outVisited, TileGroup& outGroup);

    } // namespace group end

typedef std::array<double, MSWP_MAX_TILES> TileProbs;

void sortByCombinationCount(const MineSweeperSolver& solver, group::TileGroup& outTileGroup);
void getSolutions(group::TileGroup& outTileGroup, MineSweeperSolver& outSolver, BoardBitMap& outBombLocations, SolutionSet& outSolutionSet, const mswp::BoardIndex i = 0, const uint8_t bombsInSolution = 0);

void calculateProbs(MineSweeperSolver& outSolver, TileProbs& outProbs);

} // namespace slvr end