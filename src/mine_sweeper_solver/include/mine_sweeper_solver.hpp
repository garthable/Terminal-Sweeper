#pragma once

#include <cstdint>
#include <cmath>
#include <array>
#include <functional>
#include <bitset>

#include "mine_sweeper_constants.hpp"
#include "mine_sweeper.hpp"
#include "mine_sweeper_solver_constants.hpp"

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
    float bombProb;
    int8_t adjBombs;
    int8_t adjUnknowns;
};

typedef std::array<Tile, MSWP_MAX_TILES> Tiles;
typedef std::array<mswp::BoardIndex, MSWP_MAX_TILES> ModifiedBuffer;
typedef std::bitset<MSWP_MAX_TILES> BoardBitMap;
typedef std::initializer_list<Tile> SolverInitList;

class MineSweeperSolver
{
public:
    MineSweeperSolver(const mswp::MineSweeper& mineSweeper);
    void updateTile(const mswp::TileStringIndex i);
    void update(const mswp::TileString& otherTileString);

    void applyFuncToAll(std::function<void(const mswp::BoardIndex i, Tile& outTile)> func);
    void applyFuncToAll(std::function<void(Tile& outTile)> func);
    void applyFuncToAll(std::function<void(const mswp::BoardIndex i)> func);

    void applyFuncToModified(std::function<void(const mswp::BoardIndex i, Tile& outTile)> func);
    void applyFuncToModified(std::function<void(Tile& outTile)> func);
    void applyFuncToModified(std::function<void(const mswp::BoardIndex i)> func);

    inline Tile& operator[](mswp::BoardIndex i)
    {
        return m_Tiles[i];
    }
    inline const Tile& operator[](mswp::BoardIndex i) const
    {
        return m_Tiles[i];
    }
    
    inline mswp::BoardWidth width() const
    {
        return m_Width;
    }
    inline mswp::BoardSize size() const
    {
        return m_Size;
    }
    
    inline const mswp::TileString& tileString() const
    {
        return m_TileString;
    }
    inline mswp::FlagsRemaining remainingBombs() const
    {
        return m_RemainingBombs;
    }
    inline mswp::BoardSize remainingTiles() const
    {
        return m_RemainingTiles;
    }
    
    inline const Tiles& tiles() const
    {
        return m_Tiles;
    }
    
    inline const ModifiedBuffer& modifiedBuffer() const
    {
        return m_ModifiedBuffer;
    }
    inline mswp::BoardSize modifiedBufferSize() const
    {
        return m_ModifiedBufferSize;
    }
    
    inline mswp::TileString& tileString()
    {
        return m_TileString;
    }
    inline mswp::FlagsRemaining& remainingBombs()
    {
        return m_RemainingBombs;
    }
    inline mswp::BoardSize& remainingTiles()
    {
        return m_RemainingTiles;
    }
    
    inline Tiles& tiles()
    {
        return m_Tiles;
    }
    
    inline ModifiedBuffer& modifiedBuffer()
    {
        return m_ModifiedBuffer;
    }
    inline mswp::BoardSize& modifiedBufferSize()
    {
        return m_ModifiedBufferSize;
    }

    bool operator==(const MineSweeperSolver& other) const;
    bool operator==(const SolverInitList& other) const;

private:
    const mswp::BoardWidth m_Width;
    const mswp::BoardSize m_Size;
    
    mswp::TileString m_TileString;
    mswp::FlagsRemaining m_RemainingBombs;
    mswp::BoardSize m_RemainingTiles;
    Tiles m_Tiles;

    ModifiedBuffer m_ModifiedBuffer;
    BoardBitMap m_IsModifiedBuffer;
    mswp::BoardSize m_ModifiedBufferSize;
};

std::ostream& operator<<(std::ostream &out, const Tile& tile);
std::ostream& operator<<(std::ostream &out, const MineSweeperSolver& mineSweeperSolver);

} // namespace slvr end