#pragma once

#include "mine_sweeper_solver.hpp"
#include "mine_sweeper_solver_probs.hpp"

namespace slvr
{

    namespace group
    {

    struct TileGroup
    {
        TileGroup() : size{0} {}
        std::array<mswp::BoardIndex, MSWP_MAX_TILES> tiles;
        mswp::BoardSize size;
    };

    void findHiddenTiles(mswp::BoardIndex centerTileIndex, const MineSweeperSolver& solver, BoardBitMap& outVisited, TileGroup& outGroup);
    void findVisibleTiles(mswp::BoardIndex centerTileIndex, const MineSweeperSolver& solver, BoardBitMap& outVisited, TileGroup& outGroup);
    void groupTiles(MineSweeperSolver& outSolver);

    } // namespace group end

void sortByCombinationCount(const MineSweeperSolver& solver, group::TileGroup& outTileGroup);
bool validCombination(const BoardBitMap& bombLayout, mswp::FlagsRemaining bombsRemaining, mswp::BoardWidth width, mswp::BoardSize size);
void computeProbabilities(const group::TileGroup& tileGroup, MineSweeperSolver& outSolver);

} // namespace slvr end