#include "gtest/gtest.h"
#include "mine_sweeper.hpp"
#include "mine_sweeper_tile_aliases.hpp"

#include "mine_sweeper_solver.hpp"

TEST(SolverTests, update0)
{
    using namespace mswptileconsts;

    mswp::MineSweeper board(5, 
    {
        H0, H0, H0, H0, H0,
        H0, H0, H0, H0, H0,
        H0, H0, H0, H0, H0,
        H0, H0, H0, H0, H0
    });

    ASSERT_EQ(board.gameState(), mswp::MineSweeper::START);

    bool res = board.click(0, 0);

    mswp::BoardInitList postClick = 
    {
        V0, V0, V0, V0, V0,
        V0, V0, V0, V0, V0,
        V0, V0, V0, V0, V0,
        V0, V0, V0, V0, V0
    };

    mswp::MineSweeper boardPostClick(5, postClick);
    mswp::TileString tileStringPostClick(5, postClick);

    ASSERT_EQ(board, boardPostClick);
    ASSERT_EQ(board.tileString(), tileStringPostClick);
    ASSERT_EQ(board.remainingTile(), 0);
    ASSERT_TRUE(res);
    ASSERT_EQ(board.gameState(), mswp::MineSweeper::WON);
}