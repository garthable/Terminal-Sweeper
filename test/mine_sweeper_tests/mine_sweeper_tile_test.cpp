#include "gtest/gtest.h"
#include "mine_sweeper_tile.hpp"
#include "tile_string.hpp"

TEST(MineSweeperTileTests, Size)
{
    ASSERT_EQ(sizeof(mswp::Tile), 1);
}

TEST(MineSweeperTileCharTests, Size)
{
    ASSERT_EQ(sizeof(mswp::TileChar), 1);
}