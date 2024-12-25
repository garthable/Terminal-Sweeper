#include <random>
#include <cmath>
#include <iostream>
#include <fstream>
#include "src/mineSweeper/mineSweeper.hpp"

//
// Public
//

MineSweeper::MineSweeper(const uint16_t& sizeX, const uint16_t& sizeY, const uint16_t& bombCount)
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

void MineSweeper::generateBombs(const uint16_t& innitClickX, const uint16_t& innitClickY, const unsigned int& seed)
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
        uint16_t index = static_cast<uint16_t>(rand() % static_cast<int>(m_sizeX*m_sizeY));
        Tile& curr = m_tiles[index];

        if (curr.tileState & bomb ||
            (curr.x >= safeSquareTopLeftX && curr.x <= safeSquareBottomRightX &&
            curr.y >= safeSquareTopLeftY && curr.y <= safeSquareBottomRightY))
        {
            continue;
        }

        currBombCount++;
        curr.tileState |= bomb;

        for (Tile* adjTile : curr.adjTiles)
        {
            adjTile->adjBombs++;
        }
    }
}

void MineSweeper::generateTilesFromMap(std::string fileName)
{
    m_tiles.clear();
    std::fstream file(fileName);
    if (!file.is_open())
    {
        throw std::runtime_error("Mine sweeper map file failed to open!");
    }
    std::string line = "";
    uint16_t i = 0;
    uint16_t x = 0;
    uint16_t y = 0;
    m_bombCount = 0;
    m_sizeX = UINT16_MAX;
    m_sizeY = 0;
    m_outputMineSweeperMap = "";
    m_isLost = false;
    while (getline(file, line))
    {
        x = 0;
        i = 0;
        for (const char& character : line)
        {
            if (character == '$')
            {
                x = UINT16_MAX;
                break;
            }
            else if (i % 2 == 1 && character == ' ')
            {
                i++;
                continue;
            }
            m_tiles.push_back(Tile(x, y));
            switch(character)
            {
                case '@':
                    m_tiles.back().tileState = bomb;
                    m_bombCount++;
                break;
                default:
                    m_tiles.back().tileState = 0u;
                break;
            }
            i++;
            x++;
        }
        if (x == UINT16_MAX)
        {
            continue;
        }
        else if (m_sizeX == UINT16_MAX)
        {
            m_sizeX = x;
        }
        else if (m_sizeX != x)
        {
            throw std::runtime_error(fileName + " is in an invalid format!");
        }
        y++;
    }
    m_sizeY = y;
    m_nonBombTilesRemaining = m_sizeX*m_sizeY - m_bombCount;
    m_flagsRemaining = m_bombCount;
    int16_t offsets[8][2] = {{-1,  1}, {0,  1}, {1,  1}, 
                             {-1,  0},          {1,  0}, 
                             {-1, -1}, {0, -1}, {1, -1}};

    for (Tile& tile : m_tiles)
    { 
        const uint16_t& x = tile.x;
        const uint16_t& y = tile.y;
        for (uint16_t i = 0u; i < 8u; i++)
        {
            Tile* adjTile = searchTile(x+offsets[i][0], y+offsets[i][1]);
            if (!adjTile)
            {
                continue;
            }
            tile.adjTiles.push_back(adjTile);
        }
    }

    for (Tile& tile : m_tiles)
    {
        if (tile.tileState != bomb)
        {
            continue;
        }
        for (Tile* adjTile : tile.adjTiles)
        {
            adjTile->adjBombs++;
        }
    }
    initializeOutputMineSweeperMap();
}

void MineSweeper::clickTile(const uint16_t& clickX, const uint16_t& clickY)
{
    Tile* tilePtr = searchTile(clickX, clickY);

    if (!tilePtr || tilePtr->tileState & visible)
    {
        return;
    }

    cascadeReveal(tilePtr);
}

void MineSweeper::flagTile(const uint16_t& flagX, const uint16_t& flagY)
{
    Tile* tilePtr = searchTile(flagX, flagY);

    if (!tilePtr || tilePtr->tileState & visible)
    {
        return;
    }

    if (!(tilePtr->tileState & bomb))
    {
        throw std::runtime_error("Flagged Non Bomb at: " + std::to_string(flagX) + " " + std::to_string(flagY));
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

bool MineSweeper::isWon()
{
    return (m_nonBombTilesRemaining == 0);
}

bool MineSweeper::isLost()
{
    return m_isLost;
}

std::string MineSweeper::getOutputMineSweeperMap()
{
    return m_outputMineSweeperMap;
}

int16_t MineSweeper::getFlagsRemaining()
{
    return m_flagsRemaining;
}

uint16_t MineSweeper::getSizeX()
{
    return m_sizeX;
}

uint16_t MineSweeper::getSizeY()
{
    return m_sizeY;
}

uint16_t MineSweeper::getBombCount()
{
    return m_bombCount;
}

//
// Private
//

void MineSweeper::generateMap()
{
    for (uint16_t y = 0u; y < m_sizeY; y++)
    {
        for (uint16_t x = 0u; x < m_sizeX; x++)
        {
            m_tiles.push_back(Tile(x, y));
        }
    }

    int16_t offsets[8][2] = {{-1,  1}, {0,  1}, {1,  1}, 
                             {-1,  0},          {1,  0}, 
                             {-1, -1}, {0, -1}, {1, -1}};

    for (Tile& refTile : m_tiles)
    {
        const uint16_t& x = refTile.x;
        const uint16_t& y = refTile.y;
        for (uint16_t i = 0u; i < 8u; i++)
        {
            Tile* adjTile = searchTile(x+offsets[i][0], y+offsets[i][1]);
            if (!adjTile)
            {
                continue;
            }
            refTile.adjTiles.push_back(adjTile);
        }
    }
}

void MineSweeper::reset()
{
    m_isLost = false;
    m_outputMineSweeperMap = "";
    m_flagsRemaining = m_bombCount;
    m_nonBombTilesRemaining = m_sizeX*m_sizeY - m_bombCount;
    initializeOutputMineSweeperMap();
    for (Tile& writeTile : m_tiles)
    {
        writeTile.adjBombs = 0u;
        writeTile.tileState = 0u;
    }
}

inline Tile* MineSweeper::searchTile(uint16_t x, uint16_t y)
{
    if (x >= m_sizeX || y >= m_sizeY)
    {
        return nullptr;
    }
    return &m_tiles[x + y*m_sizeX];
}

void MineSweeper::initializeOutputMineSweeperMap()
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

inline void MineSweeper::setOutputMineSweeperMapChar(const uint16_t& x, const uint16_t& y, const char& newChar)
{
    uint16_t charIndex = x + y*(m_sizeX + 1);
    m_outputMineSweeperMap[charIndex] = newChar;
}

void MineSweeper::cascadeReveal(Tile* curr)
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

    for (Tile* adjTile : curr->adjTiles)
    {
        if (adjTile->tileState & visible)
        {
            continue;
        }
        cascadeReveal(adjTile);
    }
}