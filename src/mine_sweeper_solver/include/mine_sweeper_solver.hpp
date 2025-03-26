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
    constexpr Tile() : bombProb{NAN}, adjBombs{-1}, adjUnknowns{-1} {}
    constexpr Tile(float bombProb, int8_t adjBombs, int8_t adjUnknowns) : bombProb{bombProb}, adjBombs{adjBombs}, adjUnknowns{adjUnknowns} {}
    constexpr bool operator==(const Tile& other) const
    {
        return adjBombs == other.adjBombs && adjUnknowns == other.adjUnknowns && bombProb == other.bombProb;
    }
    constexpr bool operator!=(const Tile& other) const
    {
        return adjBombs != other.adjBombs || adjUnknowns != other.adjUnknowns || bombProb != other.bombProb;
    }
    bool hidden() const
    {
        return isnanf(bombProb) == 1;
    }
    constexpr void setHidden()
    {
        bombProb = NAN;
    }
    float bombProb;
    int8_t adjBombs;
    int8_t adjUnknowns;
};

typedef std::array<Tile, MSWP_MAX_TILES> Tiles;
typedef std::array<mswp::BoardIndex, MSWP_MAX_TILES> ModifiedBuffer;
typedef std::initializer_list<Tile> SolverInitList;

class MineSweeperSolver
{
public:
    MineSweeperSolver(mswp::BoardWidth width, mswp::BoardHeight height, mswp::BombCount bombCount, const mswp::TileString& initString);
    void update(const mswp::TileString& otherTileString);

    void applyFuncToAll(std::function<void(const mswp::BoardIndex i, Tile& outTile)> func);
    void applyFuncToAll(std::function<void(Tile& outTile)> func);
    void applyFuncToAll(std::function<void(const mswp::BoardIndex i)> func);

    void applyFuncToModified(std::function<void(const mswp::BoardIndex i, Tile& outTile)> func);
    void applyFuncToModified(std::function<void(Tile& outTile)> func);
    void applyFuncToModified(std::function<void(const mswp::BoardIndex i)> func);

    Tile& operator[](mswp::BoardIndex i);
    const Tile& operator[](mswp::BoardIndex i) const;

    mswp::BoardWidth width() const;
    mswp::BoardSize size() const;

    const mswp::TileString& tileString() const;
    mswp::BombCount remainingBombs() const;
    mswp::BoardSize remainingTiles() const;

    const Tiles& tiles() const;

    const ModifiedBuffer& modifiedBuffer() const;
    mswp::BoardSize modifiedBufferSize() const;

    mswp::TileString& tileString();
    mswp::BombCount& remainingBombs();
    mswp::BoardSize& remainingTiles();

    Tiles& tiles();

    ModifiedBuffer& modifiedBuffer();
    mswp::BoardSize& modifiedBufferSize();

    bool operator==(const MineSweeperSolver& other) const;
    bool operator==(const SolverInitList& other) const;

private:
    const mswp::BoardWidth m_Width;
    const mswp::BoardSize m_Size;
    
    mswp::TileString m_TileString;
    mswp::BombCount m_RemainingBombs;
    mswp::BoardSize m_RemainingTiles;
    Tiles m_Tiles;

    ModifiedBuffer m_ModifiedBuffer;
    mswp::BoardSize m_ModifiedBufferSize;
};

std::ostream& operator<<(std::ostream &out, const Tile& tile);
std::ostream& operator<<(std::ostream &out, const MineSweeperSolver& mineSweeperSolver);

} // namespace slvr end