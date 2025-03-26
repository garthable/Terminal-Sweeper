#pragma once

#include <cstdint>
#include <cmath>
#include <array>
#include <functional>

#include "mine_sweeper_constants.hpp"
#include "mine_sweeper.hpp"

namespace slvr
{

struct Tile
{
    Tile() : bombProb{NAN}, adjBombs{-1}, adjUnkowns{-1} {}
    float bombProb;
    int8_t adjBombs;
    int8_t adjUnkowns;
};

typedef std::array<Tile, MSWP_MAX_TILES> Tiles;

class MineSweeperSolver
{
public:
    MineSweeperSolver(mswp::BoardWidth width, mswp::BoardHeight height, mswp::BombCount bombCount, const mswp::TileString& initString);

    void update(const mswp::TileString& otherTileString);
    void applyFuncToAll(std::function<void(Tile& tile)> func);
    Tile& operator[](mswp::BoardIndex i);
    const Tile& operator[](mswp::BoardIndex i) const;

    mswp::BoardWidth width() const;
    mswp::BoardSize size() const;

    const mswp::TileString& tileString() const;
    mswp::BombCount remainingBombs() const;
    mswp::BoardSize remainingTiles() const;

    const Tiles& tiles() const;

    mswp::TileString& tileString();
    mswp::BombCount& remainingBombs();
    mswp::BoardSize& remainingTiles();

    Tiles& tiles();

private:
    const mswp::BoardWidth m_Width;
    const mswp::BoardSize m_Size;
    
    mswp::TileString m_TileString;
    mswp::BombCount m_RemainingBombs;
    mswp::BoardSize m_RemainingTiles;
    Tiles m_Tiles;
};

} // namespace slvr end