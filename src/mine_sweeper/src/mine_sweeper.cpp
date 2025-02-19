#include <random>
#include <array>
#include <functional>

#include "mine_sweeper.hpp"
#include "log.hpp"
#include "util.hpp"

namespace mswp
{

/**
 * @brief Sets all tiles to hidden
 * 
 * @param size 
 * @param outTiles 
 */
inline void resetTiles(BoardSize size, Tiles& outTiles)
{
    for (BoardIndex i = 0; i < size; i++)
    {
        Tile& tile = outTiles[i];
        tile.adjBombs = 0u;
        tile.state = Tile::HIDDEN;
    }
}

/**
 * @brief Generates bombs for board
 * 
 * @param size Size of board
 * @param width Width of board
 * @param bombCount Amount of bombs in board
 * @param seed Seed of board
 * @param outTiles Tiles to be modified
 */
void generateBombs(BoardSize size, BoardWidth width, BombCount bombCount, BoardSeed seed, Tiles& outTiles)
{
    std:: minstd_rand rand;
    rand.seed(seed);

    BombCount currBombCount = 0;

    BoardIndex y = static_cast<BoardIndex>(width);
    BoardIndex x = static_cast<BoardIndex>(1);

    while(currBombCount != bombCount)
    {
        BoardIndex index = rand() % size;
        Tile& tile = outTiles[index];
        if (tile.state & Tile::BOMB)
        {
            continue;
        }
        util::applyFuncToAdjObjects<Tiles, Tile>(index, width, size, outTiles, 
        [](Tile& tile) 
        {
            tile.adjBombs += 1;
        });
        tile.state = static_cast<Tile::State>(tile.state | Tile::BOMB);
        currBombCount += 1;
    }
}

/**
 * @brief Gets the amount of bombs in an initialization list
 * 
 * @param initList 
 * @return BombCount 
 */
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
    m_Size{util::multI8sToI16(width, height)},
    m_Width{width},
    m_BombCount{bombCount},
    m_BoardSeed{boardSeed},
    m_RemainingTiles{m_Size},
    m_GameState{START},
    m_FlagsRemaining{static_cast<FlagsRemaining>(m_BombCount)},
    m_TileString{TileString(m_Size, m_Width)}
{
    resetTiles(m_Size, m_Tiles);
    generateBombs(m_Size, m_Width, m_BombCount, m_BoardSeed, m_Tiles);
}

MineSweeper::MineSweeper(BoardWidth width, BoardInitList&& boardInitList) :
    m_Size{static_cast<BoardSize>(boardInitList.size())},
    m_Width{width},
    m_BombCount{getBombCount(boardInitList)},
    m_BoardSeed{0},
    m_RemainingTiles{m_Size},
    m_GameState{START},
    m_FlagsRemaining{static_cast<FlagsRemaining>(m_BombCount)},
    m_TileString{TileString(m_Width, boardInitList)}
{
    std::copy(boardInitList.begin(), boardInitList.begin() + m_Size, m_Tiles.begin());
}

MineSweeper::MineSweeper(BoardWidth width, const BoardInitList& boardInitList) :
    m_Size{static_cast<BoardSize>(boardInitList.size())},
    m_Width{width},
    m_BombCount{getBombCount(boardInitList)},
    m_BoardSeed{0},
    m_RemainingTiles{m_Size},
    m_GameState{START},
    m_FlagsRemaining{static_cast<FlagsRemaining>(m_BombCount)},
    m_TileString{TileString(m_Width, boardInitList)}
{
    std::copy(boardInitList.begin(), boardInitList.begin() + m_Size, m_Tiles.begin());
}

/**
 * @brief Clicks all tiles neighboring tiles with no adjbombs
 * 
 * @param i Current tile index
 * @param size Size of board
 * @param width Width of board
 * @param outRemainingTiles Remaining tiles to be modified
 * @param outTiles Tiles to be modified
 * @param outTileString Tile String to be modified
 */
void reccursiveClick(const BoardIndex i, const BoardSize size, const BoardWidth width, BoardSize& outRemainingTiles, Tiles& outTiles, TileString& outTileString)
{
    if (outTiles[i].state & Tile::VISIBLE)
    {
        return;
    }
    outTiles[i].state = outTiles[i].state | Tile::VISIBLE;
    outTileString.set(i, tileToTileChar(outTiles[i]));
    outRemainingTiles--;
    if (outTiles[i].adjBombs)
    {
        return;
    }

    util::applyFuncToAdjObjects<Tiles, Tile>(i, width, size, outTiles, 
    [&](BoardIndex newI, Tile& tile) 
    {
        reccursiveClick(newI, size, width, outRemainingTiles, outTiles, outTileString);
    });
}

/**
 * @brief Removes bombs in area
 * 
 * @param center Where user clicked
 * @param width Width of board
 * @param size Size of board
 * @param outTiles Tiles to be modified
 * @param outBombCounts used to keep track of number of bombs removed
 * @return true 
 * @return false 
 */
inline bool removeBombsInArea(BoardIndex center, BoardWidth width, BoardSize size, Tiles& outTiles, BombCount& outBombCounts)
{
    bool bombInArea = false;
    if (outTiles[center].state & Tile::BOMB)
    {
        bombInArea = true;
        outTiles[center].state = outTiles[center].state ^ Tile::BOMB;
        outBombCounts--;
        util::applyFuncToAdjObjects<Tiles, Tile>(center, width, size, outTiles,
        [](Tile& tile)
        {
            tile.adjBombs--;
        });
    }
    util::applyFuncToAdjObjects<Tiles, Tile>(center, width, size, outTiles, 
    [&](BoardIndex j, Tile& tile)
    {
        if (tile.state & Tile::BOMB)
        {
            bombInArea = true;
            tile.state = tile.state ^ Tile::BOMB;
            outBombCounts--;
            util::applyFuncToAdjObjects<Tiles, Tile>(j, width, size, outTiles,
            [](Tile& tile)
            {
                tile.adjBombs--;
            });
        }
    });
    return bombInArea;
}

/**
 * @brief Moves bombs away from center
 * 
 * @param center Where user clicked
 * @param boardSeed Seed used to randomly place bombs
 * @param width Width of board
 * @param size Size of board
 * @param bombCount BombCount
 * @param outTiles Tiles to be modified
 */
inline void moveBombsAway(const BoardIndex center, const BoardSeed boardSeed, const BoardWidth width, const BoardSize size, const BombCount bombCount, Tiles& outTiles)
{
    BombCount currBombCount = bombCount;
    if (!removeBombsInArea(center, width, size, outTiles, currBombCount))
    {
        return;
    }
    std:: minstd_rand rand;
    rand.seed(boardSeed + 1);
    while(currBombCount != bombCount)
    {
        const BoardIndex randI = rand() % size;
        if (outTiles[randI].state & Tile::BOMB || util::isIndexNear(width, center, randI))
        {
            continue;
        }
        outTiles[randI].state = outTiles[randI].state | Tile::BOMB;
        currBombCount++;
        util::applyFuncToAdjObjects<Tiles, Tile>(randI, width, size, outTiles, 
        [](Tile& tile) 
        {
            tile.adjBombs += 1;
        });
    }
}

bool MineSweeper::click(BoardXPos x, BoardYPos y)
{
    BoardIndex i = static_cast<BoardIndex>(x) + static_cast<BoardIndex>(y)*m_Width;
    if (m_GameState & MineSweeper::START && m_Tiles[i].state & Tile::BOMB)
    {
        moveBombsAway(i, m_BoardSeed, m_Width, m_Size, m_BombCount, m_Tiles);
    }
    reccursiveClick(i, m_Size, m_Width, m_RemainingTiles, m_Tiles, m_TileString);
    if (m_Tiles[i].state & Tile::BOMB)
    {
        m_GameState = LOST;
        return true;
    }
    if (m_RemainingTiles == m_BombCount)
    {
        m_GameState = WON;
        return true;
    }
    return false;
}
bool MineSweeper::flag(BoardXPos x, BoardYPos y)
{
    BoardIndex i = static_cast<BoardIndex>(x) + static_cast<BoardIndex>(y)*m_Width;
    if (m_FlagsRemaining <= 0 && m_Tiles[i].state & Tile::FLAGGED == 0)
    {
        return false;
    }
    m_FlagsRemaining += (m_Tiles[i].state & Tile::FLAGGED ? 1 : -1);
    m_Tiles[i].state = m_Tiles[i].state ^ Tile::FLAGGED;
    m_TileString.set(i, tileToTileChar(m_Tiles[i]));

    return true;
}

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
    out << mineSweeper.tileString();
    return out;
}

} // mswp end