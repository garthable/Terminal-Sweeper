#pragma once

#include <array>

#include "mine_sweeper_constants.hpp"
#include "mine_sweeper_tile.hpp"
#include "tile_string.hpp"

namespace mswp
{

typedef std::array<Tile, MSWP_MAX_TILES> Tiles;

typedef int16_t BoardSize;
typedef uint8_t BoardWidth;
typedef uint8_t BoardHeight;
typedef uint8_t BombCount;
typedef uint32_t BoardSeed;
typedef int8_t FlagsRemaining;

typedef BoardSize BoardIndex;
typedef BoardWidth BoardXPos;
typedef BoardHeight BoardYPos;

typedef std::initializer_list<Tile> BoardInitList;

class MineSweeper
{
public:
    enum GameState : uint8_t 
    {
        START = 1,
        IN_PROGRESS = 2,
        WON = 4,
        LOST = 8
    };
    MineSweeper(BoardWidth width, BoardHeight height, BombCount bombCount, BoardSeed boardSeed);
    MineSweeper(BoardWidth width, BoardInitList&& boardInitList);
    MineSweeper(BoardWidth width, const BoardInitList& boardInitList);

    bool click(BoardXPos x, BoardYPos y);
    bool flag(BoardXPos x, BoardYPos y);

    const Tiles& tiles() const; 
    const TileString& tileString() const;
    BoardSize size() const;
    BoardSize remainingTile() const;
    BoardWidth width() const;
    GameState gameState() const;
    FlagsRemaining flagsRemaining() const;

    void reset();

    bool operator==(const MineSweeper& other) const;
    bool operator==(const BoardInitList& other) const;

    inline Tile operator[](BoardIndex index) const
    {
        return m_Tiles[index];
    }
    inline Tile operator()(BoardXPos x, BoardYPos y) const
    {
        return m_Tiles[x + y*m_Width];
    }
    inline Tile& operator[](BoardIndex index)
    {
        return m_Tiles[index];
    }
    inline Tile& operator()(BoardXPos x, BoardYPos y)
    {
        return m_Tiles[x + y*m_Width];
    }
    
private:
    const BoardSize m_Size;
    const BoardWidth m_Width;
    const BombCount m_BombCount;
    const BoardSeed m_BoardSeed;
    
    BoardSize m_RemainingTiles;
    GameState m_GameState;
    FlagsRemaining m_FlagsRemaining;

    Tiles m_Tiles;
    TileString m_TileString;
};

std::ostream& operator<<(std::ostream &out, const MineSweeper& mineSweeper);

} // mswp end