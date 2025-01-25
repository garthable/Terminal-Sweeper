#include "gtest/gtest.h"
#include "mine_sweeper_tile.hpp"

TEST(MineSweeperTile_Tests, MineSweeperTile_Size)
{
    ASSERT_EQ(sizeof(mswp::MineSweeperTile), 1);
}

TEST(MineSweeperTile_Tests, MineSweeperTileExport_Size)
{
    ASSERT_EQ(sizeof(mswp::MineSweeperTileExport), 1);
}