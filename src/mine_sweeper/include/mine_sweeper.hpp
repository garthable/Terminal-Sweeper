#pragma once

#include "mine_sweeper_tile.hpp"
#include "stack_vector.hpp"

#define MSWP_MAX_WIDTH 30
#define MSWP_MAX_HEIGHT 16
#define MSWP_MAX_TILES MSWP_MAX_WIDTH*MSWP_MAX_HEIGHT

namespace mswp
{

typedef svec::SVector<MineSweeperTile, MSWP_MAX_TILES> MineSweeperTiles;
typedef svec::SVector<MineSweeperTileExport, MSWP_MAX_TILES/2> MineSweeperTileExports;

enum MineSweeperGameState : uint8_t 
{
    IN_PROGRESS = 0,
    WON = 1,
    LOST = 2
};

class MineSweeper
{
public:
    MineSweeper(uint8_t width, uint8_t height);

    void click(uint8_t x, uint8_t y);
    void flag(uint8_t x, uint8_t y);

    void exportTiles(MineSweeperTileExports& outMineSweeperTileExports);

    void reset();

    MineSweeperGameState getGameState();

    inline MineSweeperTile& operator[](uint16_t index);
    inline MineSweeperTile& operator()(uint8_t x, uint8_t y);

private:
    MineSweeperTiles m_Tiles;
    uint16_t m_Size;
    uint16_t m_RemainingTiles;
    uint8_t m_Width;
};

std::ostream& operator<<(std::ostream &out, const MineSweeper& mineSweeper);

} // mswp end