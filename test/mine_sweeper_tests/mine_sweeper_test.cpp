#include "gtest/gtest.h"
#include "mine_sweeper.hpp"
#include "mine_sweeper_tile_aliases.hpp"

#include "log.hpp"

TEST(MineSweeperTests, click0)
{
    using namespace mswpalias;

    mswp::MineSweeper board(5, 
    {
        H0, H0, H0, H0, H0,
        H0, H0, H0, H0, H0,
        H0, H0, H0, H0, H0,
        H0, H0, H0, H0, H0
    });

    board.click(0, 0);

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
}

TEST(MineSweeperTests, click1)
{
    using namespace mswpalias;

    mswp::MineSweeper board(5, 
    {
        H1, H1, H1, H0, H0,
        H1, BO, H1, H0, H0,
        H1, H1, H1, H0, H0,
        H0, H0, H0, H0, H0
    });

    board.click(0, 0);

    mswp::BoardInitList postClick =
    {
        V1, H1, H1, H0, H0,
        H1, BO, H1, H0, H0,
        H1, H1, H1, H0, H0,
        H0, H0, H0, H0, H0
    };

    mswp::MineSweeper boardPostClick(5, postClick);
    mswp::TileString tileStringPostClick(5, postClick);

    ASSERT_EQ(board, boardPostClick);
    ASSERT_EQ(board.tileString(), tileStringPostClick);
    ASSERT_EQ(board.remainingTile(), 19);
}

TEST(MineSweeperTests, click2)
{
    using namespace mswpalias;

    mswp::MineSweeper board(5, 
    {
        H1, H1, H1, H0, H0,
        H1, BO, H1, H0, H0,
        H1, H1, H1, H0, H0,
        H0, H0, H0, H0, H0
    });

    board.click(4, 3);

    mswp::BoardInitList postClick = 
    {
        H1, H1, V1, V0, V0,
        H1, BO, V1, V0, V0,
        V1, V1, V1, V0, V0,
        V0, V0, V0, V0, V0
    };

    mswp::MineSweeper boardPostClick(5, postClick);
    mswp::TileString tileStringPostClick(5, postClick);

    ASSERT_EQ(board, boardPostClick);
    ASSERT_EQ(board.tileString(), tileStringPostClick);
    ASSERT_EQ(board.remainingTile(), 4);
}

TEST(MineSweeperTests, flag)
{
    using namespace mswpalias;

    mswp::MineSweeper board(5, 
    {
        H1, H1, H1, H0, H0,
        H1, BO, H1, H0, H0,
        H1, H1, H1, H0, H0,
        H0, H0, H0, H0, H0
    });

    board.flag(2, 2);

    mswp::BoardInitList postClick = 
    {
        H1, H1, H1, H0, H0,
        H1, BO, H1, H0, H0,
        H1, H1, F1, H0, H0,
        H0, H0, H0, H0, H0
    };

    mswp::MineSweeper boardPostClick(5, postClick);
    mswp::TileString tileStringPostClick(5, postClick);

    ASSERT_EQ(board, boardPostClick);
    ASSERT_EQ(board.tileString(), tileStringPostClick);
    ASSERT_EQ(board.flagsRemaining(), 0);
}

TEST(MineSweeperTests, unflag)
{
    using namespace mswpalias;

    mswp::MineSweeper board(5, 
    {
        H1, H1, H1, H0, H0,
        H1, BO, H1, H0, H0,
        H1, H1, F1, H0, H0,
        H0, H0, H0, H0, H0
    });

    board.flag(2, 2);

    mswp::BoardInitList postClick = 
    {
        H1, H1, H1, H0, H0,
        H1, BO, H1, H0, H0,
        H1, H1, H1, H0, H0,
        H0, H0, H0, H0, H0
    };

    mswp::MineSweeper boardPostClick(5, postClick);
    mswp::TileString tileStringPostClick(5, postClick);

    ASSERT_EQ(board, boardPostClick);
    ASSERT_EQ(board.tileString(), tileStringPostClick);
    ASSERT_EQ(board.flagsRemaining(), 1);
}
