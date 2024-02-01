#include <random>
#include <cmath>
#include "../include/mineSweeper.h"

//
// Public
//

mineSweeper::mineSweeper(const uint16_t& sizeX, const uint16_t& sizeY, const uint16_t& bombCount)
{
    m_sizeX = sizeX;
    m_sizeY = sizeY;
    m_bombCount = bombCount;
    m_flagsRemaining = bombCount;

    m_outputMineSweeperMap = "";
    m_nonBombTilesRemaining = m_sizeX*m_sizeY - m_bombCount;
    m_isLost = false;

    generateMap();
    initializeOutputMineSweeperMap();
}

void mineSweeper::generateBombs(const uint16_t& innitClickX, const uint16_t& innitClickY, const unsigned int& seed)
{
    reset();
    srand(seed);
    m_nonBombTilesRemaining = m_sizeX*m_sizeY - m_bombCount;
    
    uint16_t safeSquareTopLeftX = innitClickX - 1u;
    uint16_t safeSquareTopLeftY = innitClickY - 1u;

    // Overflow management for case where innitClickX = 0 and or innitClickY = 0
    if (safeSquareTopLeftX == UINT16_MAX)
    {
        safeSquareTopLeftX = 0u;
    }
    if (safeSquareTopLeftY == UINT16_MAX)
    {
        safeSquareTopLeftY = 0u;
    }

    uint16_t safeSquareBottomRightX = innitClickX + 1u;
    uint16_t safeSquareBottomRightY = innitClickY + 1u;

    uint16_t currBombCount = 0;

    while (currBombCount != m_bombCount)
    {
        uint16_t index = arc4random_uniform(m_sizeX*m_sizeY);
        tile& curr = m_tiles[index];

        if (curr.tileState & bomb ||
            (curr.x >= safeSquareTopLeftX && curr.x <= safeSquareBottomRightX &&
            curr.y >= safeSquareTopLeftY && curr.y <= safeSquareBottomRightY))
        {
            continue;
        }

        currBombCount++;
        curr.tileState |= bomb;

        for (tile* adjTile : curr.adjTiles)
        {
            adjTile->adjBombs++;
        }
    }
}

void mineSweeper::clickTile(const uint16_t& clickX, const uint16_t& clickY)
{
    tile* tilePtr = searchTile(clickX, clickY);

    if (!tilePtr || tilePtr->tileState & visible)
    {
        return;
    }

    cascadeReveal(tilePtr);
}

void mineSweeper::flagTile(const uint16_t& flagX, const uint16_t& flagY)
{
    tile* tilePtr = searchTile(flagX, flagY);

    if (!tilePtr || tilePtr->tileState & visible)
    {
        return;
    }
    
    if (tilePtr->tileState & flagged)
    {
        m_flagsRemaining++;
        setOutputMineSweeperMapChar(flagX, flagY, '#');
    }
    else
    {
        m_flagsRemaining--;
        setOutputMineSweeperMapChar(flagX, flagY, '@');
    }

    tilePtr->tileState ^= flagged;
}

bool mineSweeper::isWon()
{
    return (m_nonBombTilesRemaining == 0);
}

bool mineSweeper::isLost()
{
    return m_isLost;
}

std::string mineSweeper::getOutputMineSweeperMap()
{
    return m_outputMineSweeperMap;
}

int16_t mineSweeper::getFlagsRemaining()
{
    return m_flagsRemaining;
}

//
// Private
//

void mineSweeper::generateMap()
{
    for (uint16_t y = 0u; y < m_sizeY; y++)
    {
        for (uint16_t x = 0u; x < m_sizeX; x++)
        {
            m_tiles.push_back(tile(x, y));
        }
    }

    int16_t offsets[8][2] = {{-1,  1}, {0,  1}, {1,  1}, 
                             {-1,  0},          {1,  0}, 
                             {-1, -1}, {0, -1}, {1, -1}};

    for (tile& refTile : m_tiles)
    {
        const uint16_t& x = refTile.x;
        const uint16_t& y = refTile.y;
        for (uint16_t i = 0u; i < 8u; i++)
        {
            tile* adjTile = searchTile(x+offsets[i][0], y+offsets[i][1]);
            if (!adjTile)
            {
                continue;
            }
            refTile.adjTiles.push_back(adjTile);
        }
    }
}

void mineSweeper::reset()
{
    for (tile& writeTile : m_tiles)
    {
        writeTile.adjBombs = 0u;
        writeTile.tileState = 0u;
    }
}

inline tile* mineSweeper::searchTile(uint16_t x, uint16_t y)
{
    if (x >= m_sizeX || y >= m_sizeY)
    {
        return nullptr;
    }
    return &m_tiles[x + y*m_sizeX];
}

void mineSweeper::initializeOutputMineSweeperMap()
{
    m_outputMineSweeperMap = "";
    for (uint16_t y = 0u; y < m_sizeY; y++)
    {
        for (uint16_t x = 0u; x < m_sizeX; x++)
        {
            m_outputMineSweeperMap += '#';
        }
        m_outputMineSweeperMap += '\n';
    }
}

inline void mineSweeper::setOutputMineSweeperMapChar(const uint16_t& x, const uint16_t& y, const char& newChar)
{
    uint16_t charIndex = x + y*(m_sizeX + 1);
    m_outputMineSweeperMap[charIndex] = newChar;
}

void mineSweeper::cascadeReveal(tile* curr)
{
    curr->tileState |= visible;
    m_nonBombTilesRemaining--;

    if (curr->tileState & bomb)
    {
        setOutputMineSweeperMapChar(curr->x, curr->y, 'X');
        m_isLost = true;
        return;
    }

    if (curr->adjBombs != 0u)
    {
        setOutputMineSweeperMapChar(curr->x, curr->y, '0' + curr->adjBombs);
        return;
    }

    setOutputMineSweeperMapChar(curr->x, curr->y, ' ');

    for (tile* adjTile : curr->adjTiles)
    {
        if (adjTile->tileState & visible)
        {
            continue;
        }
        cascadeReveal(adjTile);
    }
}