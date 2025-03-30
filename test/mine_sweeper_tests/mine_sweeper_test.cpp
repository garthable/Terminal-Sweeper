#include "gtest/gtest.h"
#include "mine_sweeper.hpp"
#include "mine_sweeper_tile_aliases.hpp"

TEST(MineSweeperTests, click0)
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

TEST(MineSweeperTests, click1)
{
    using namespace mswptileconsts;

    mswp::MineSweeper board(5, 
    {
        H0, H1, B0, H1, H0,
        H1, H3, H2, H2, H0,
        B0, H2, B0, H1, H0,
        H1, H2, H1, H1, H0
    });

    ASSERT_EQ(board.gameState(), mswp::MineSweeper::START);

    bool res = board.click(0, 0);

    mswp::BoardInitList postClick =
    {
        V0, V1, B0, H1, H0,
        V1, V3, H2, H2, H0,
        B0, H2, B0, H1, H0,
        H1, H2, H1, H1, H0
    };

    mswp::MineSweeper boardPostClick(5, postClick);
    mswp::TileString tileStringPostClick(5, postClick);

    ASSERT_EQ(board, boardPostClick);
    ASSERT_EQ(board.tileString(), tileStringPostClick);
    ASSERT_EQ(board.remainingTile(), 16);
    ASSERT_FALSE(res);
    ASSERT_EQ(board.gameState(), mswp::MineSweeper::IN_PROGRESS);
}

TEST(MineSweeperTests, click2)
{
    using namespace mswptileconsts;

    mswp::MineSweeper board(5, 
    {
        H1, H1, H1, H0, H0,
        H1, B0, H1, H0, H0,
        H1, H1, H1, H0, H0,
        H0, H0, H0, H0, H0
    });

    ASSERT_EQ(board.gameState(), mswp::MineSweeper::START);

    bool res = board.click(4, 3);

    mswp::BoardInitList postClick = 
    {
        H1, H1, V1, V0, V0,
        H1, B0, V1, V0, V0,
        V1, V1, V1, V0, V0,
        V0, V0, V0, V0, V0
    };

    mswp::MineSweeper boardPostClick(5, postClick);
    mswp::TileString tileStringPostClick(5, postClick);

    ASSERT_EQ(board, boardPostClick);
    ASSERT_EQ(board.tileString(), tileStringPostClick);
    ASSERT_EQ(board.remainingTile(), 4);
    ASSERT_FALSE(res);
    ASSERT_EQ(board.gameState(), mswp::MineSweeper::IN_PROGRESS);
}

TEST(MineSweeperTests, click3)
{
    using namespace mswptileconsts;

    mswp::MineSweeper board(5, 
    {
        H1, H1, H1, H0, H0,
        H1, B0, H1, H0, H0,
        H1, H1, H1, H0, H0,
        H0, H0, H0, H0, H0
    });

    ASSERT_EQ(board.gameState(), mswp::MineSweeper::START);

    board.click(4, 3);
    bool res = board.click(1, 1);

    mswp::BoardInitList postClick = 
    {
        H1, H1, V1, V0, V0,
        H1, mswp::Tile(0, mswp::Tile::BOMB | mswp::Tile::VISIBLE), V1, V0, V0,
        V1, V1, V1, V0, V0,
        V0, V0, V0, V0, V0
    };

    mswp::MineSweeper boardPostClick(5, postClick);
    mswp::TileString tileStringPostClick(5, postClick);

    ASSERT_EQ(board, boardPostClick);
    ASSERT_EQ(board.tileString(), tileStringPostClick);
    ASSERT_EQ(board.remainingTile(), 3);
    ASSERT_TRUE(res);
    ASSERT_EQ(board.gameState(), mswp::MineSweeper::LOST);
}

TEST(MineSweeperTests, clickMoveBomb0)
{
    using namespace mswptileconsts;

    mswp::MineSweeper board(5, 
    {
        B0, H1, H0, H0, H0,
        H1, H1, H0, H0, H0,
        H0, H0, H0, H0, H0,
        H0, H0, H0, H0, H0
    });

    board.click(0, 0);

    ASSERT_EQ(board(0, 0), V0);
}
TEST(MineSweeperTests, clickMoveBomb1)
{
    using namespace mswptileconsts;

    mswp::MineSweeper board(5, 
    {
        B3, B5, B3, H2, H0,
        B5, B8, B5, H3, H0,
        B3, B5, B3, H2, H0,
        H2, H3, H2, H1, H0
    });

    board.click(1, 1);

    ASSERT_EQ(board(1, 1), V0);
    ASSERT_EQ(board(0, 1), V0);
    ASSERT_EQ(board(1, 0), V0);
    ASSERT_EQ(board(0, 0), V0);
}

TEST(MineSweeperTests, flag)
{
    using namespace mswptileconsts;

    mswp::MineSweeper board(5, 
    {
        H1, H1, H1, H0, H0,
        H1, B0, H1, H0, H0,
        H1, H1, H1, H0, H0,
        H0, H0, H0, H0, H0
    });

    bool res = board.flag(2, 2);

    mswp::BoardInitList postClick = 
    {
        H1, H1, H1, H0, H0,
        H1, B0, H1, H0, H0,
        H1, H1, F1, H0, H0,
        H0, H0, H0, H0, H0
    };

    mswp::MineSweeper boardPostClick(5, postClick);
    mswp::TileString tileStringPostClick(5, postClick);

    ASSERT_EQ(board, boardPostClick);
    ASSERT_EQ(board.tileString(), tileStringPostClick);
    ASSERT_EQ(board.flagsRemaining(), 0);
    ASSERT_TRUE(res);
}

TEST(MineSweeperTests, unflag)
{
    using namespace mswptileconsts;

    mswp::MineSweeper board(5, 
    {
        H1, H1, H1, H0, H0,
        H1, B0, H1, H0, H0,
        H1, H1, F1, H0, H0,
        H0, H0, H0, H0, H0
    });

    bool res = board.flag(2, 2);

    mswp::BoardInitList postClick = 
    {
        H1, H1, H1, H0, H0,
        H1, B0, H1, H0, H0,
        H1, H1, H1, H0, H0,
        H0, H0, H0, H0, H0
    };

    mswp::MineSweeper boardPostClick(5, postClick);
    mswp::TileString tileStringPostClick(5, postClick);

    ASSERT_EQ(board, boardPostClick);
    ASSERT_EQ(board.tileString(), tileStringPostClick);
    ASSERT_EQ(board.flagsRemaining(), 2);
    ASSERT_TRUE(res);
}
