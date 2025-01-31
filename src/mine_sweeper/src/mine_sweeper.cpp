#include <random>

#include "mine_sweeper.hpp"

namespace mswp
{

inline BoardSize getSize(BoardWidth width, BoardHeight height)
{
    return static_cast<BoardSize>(width)*static_cast<BoardSize>(height);
}

inline void resetTiles(BoardSize size, Tiles& outTiles)
{
    for (BoardIndex i = 0; i < size; i++)
    {
        Tile& tile = outTiles[i];
        tile.adjBombs = 0u;
        tile.state = Tile::HIDDEN;
    }
}

void generateBombs(BoardSize size, BoardWidth width, BombCount bombCount, BoardSeed seed, Tiles& outTiles)
{
    std:: minstd_rand rand;
    rand.seed(seed);

    BombCount currBombCount = 0;

    BoardIndex y = static_cast<BoardIndex>(width);
    BoardIndex x = static_cast<BoardIndex>(1);

    BoardIndex offsets[8] =
    {
         y - x,  y,  y + x,
        -x,              x,
        -y - x, -y, -y + x,
    };

    while(currBombCount != bombCount)
    {
        BoardIndex index = rand() % size;
        Tile& tile = outTiles[index];
        if (tile.state & Tile::BOMB)
        {
            continue;
        }
        for (BoardIndex offset : offsets)
        {
            BoardIndex otherIndex = index + offset;
            if (otherIndex >= size)
            {
                continue;
            }
            Tile& otherTile = outTiles[otherIndex];
            otherTile.adjBombs += 1;
        }
        tile.state = static_cast<Tile::State>(tile.state | Tile::BOMB);
        currBombCount += 1;
    }
}

inline BombCount getBombCount(const BoardInitList& initList)
{
    BombCount bombCount = 0;
    for (Tile tile : initList)
    {
        bombCount += tile.state & Tile::BOMB;
    }
    return bombCount;
}

MineSweeper::MineSweeper(BoardWidth width, BoardHeight height, BombCount bombCount, BoardSeed boardSeed) :
    m_Size{getSize(width, height)},
    m_Width{width},
    m_BombCount{bombCount},
    m_BoardSeed{boardSeed},
    m_RemainingTiles{m_Size},
    m_GameState{START},
    m_FlagsRemaining{m_BombCount},
    m_TileString{TileStringSize(m_Size)}
{
    resetTiles(m_Size, m_Tiles);
    generateBombs(m_Size, m_Width, m_BombCount, m_BoardSeed, m_Tiles);
}

MineSweeper::MineSweeper(BoardWidth width, BoardInitList&& boardInitList) :
    m_Size{boardInitList.size()},
    m_Width{width},
    m_BombCount{getBombCount(boardInitList)},
    m_BoardSeed{0},
    m_RemainingTiles{m_Size},
    m_GameState{START},
    m_FlagsRemaining{m_BombCount},
    m_TileString{TileStringSize(m_Size)}
{
    std::copy(boardInitList.begin(), boardInitList.begin() + m_Size, m_Tiles.begin());
}

MineSweeper::MineSweeper(BoardWidth width, const BoardInitList& boardInitList) :
    m_Size{boardInitList.size()},
    m_Width{width},
    m_BombCount{getBombCount(boardInitList)},
    m_BoardSeed{0},
    m_RemainingTiles{m_Size},
    m_GameState{START},
    m_FlagsRemaining{m_BombCount},
    m_TileString{TileStringSize(m_Size)}
{
    std::copy(boardInitList.begin(), boardInitList.begin() + m_Size, m_Tiles.begin());
}

bool MineSweeper::click(BoardXPos x, BoardYPos y)
{}
bool MineSweeper::flag(BoardXPos x, BoardYPos y)
{}

const Tiles& MineSweeper::tiles() const
{
    return m_Tiles;
}
const TileString& MineSweeper::tileString() const
{
    return m_TileString;
}
BoardSize MineSweeper::size() const
{
    return m_Size;
}
BoardSize MineSweeper::remainingTile() const
{
    return m_RemainingTiles;
}
BoardWidth MineSweeper::width() const
{
    return m_Width;
}
MineSweeper::GameState MineSweeper::gameState() const
{
    return m_GameState;
}
FlagsRemaining MineSweeper::flagsRemaining() const
{
    return m_FlagsRemaining;
}

void MineSweeper::reset()
{
    resetTiles(m_Size, m_Tiles);
    generateBombs(m_Size, m_Width, m_BombCount, m_BoardSeed, m_Tiles);
}

bool MineSweeper::operator==(const MineSweeper& other) const
{
    for (BoardIndex i = 0; i < m_Size; i++)
    {
        if (m_Tiles[i].adjBombs != other.m_Tiles[i].adjBombs || m_Tiles[i].state != other.m_Tiles[i].state)
        {
            return false;
        }
    }
    return true;
}

bool MineSweeper::operator==(const BoardInitList& other) const
{
    for (BoardIndex i = 0; i < m_Size; i++)
    {
        Tile otherTile = *(other.begin() + i);
        if (m_Tiles[i].adjBombs != otherTile.adjBombs || m_Tiles[i].state != otherTile.state)
        {
            return false;
        }
    }
    return true;
}

std::ostream& operator<<(std::ostream &out, const MineSweeper& mineSweeper)
{
    return out;
}

} // mswp end