#pragma once

#include "mine_sweeper_solver.hpp"
#include "mine_sweeper_solver_probs.hpp"

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
        TileGroup() : size{0} {}
        TileGroup(std::initializer_list<mswp::BoardIndex> indices) :
            size{indices.size()}
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
    void groupTiles(MineSweeperSolver& outSolver);

    } // namespace group end

void sortByCombinationCount(const MineSweeperSolver& solver, group::TileGroup& outTileGroup);
bool validCombination(const BoardBitMap& bombLayout, mswp::FlagsRemaining bombsRemaining, mswp::BoardWidth width, mswp::BoardSize size);
void computeProbabilities(const group::TileGroup& tileGroup, MineSweeperSolver& outSolver, const mswp::BoardIndex i = 0);

} // namespace slvr end