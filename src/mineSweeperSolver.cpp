#include "../include/mineSweeperSolver.h"
#include <iostream>

//
// Public
//

mineSweeperSolver::mineSweeperSolver(const uint16_t& sizeX, const uint16_t& sizeY, const uint16_t& bombCount)
{
    m_sizeX = sizeX;
    m_sizeY = sizeY;
    m_bombCount = bombCount;

    generateSolverTiles();
}

void mineSweeperSolver::update(const std::string& mineSweeperMap)
{
    if (hasReccomendedSolverTiles())
    {
        return;
    }
    readMineMap(mineSweeperMap);

    fastBombFinder();

    if (hasReccomendedSolverTiles())
    {
        return;
    }

    patternBombFinder();

    if (hasReccomendedSolverTiles())
    {
        return;
    }

    // exit(-1);
}

std::string mineSweeperSolver::getSolverMap()
{
    std::string output = "";
    for (const solverTile& _solverTile : m_solverTiles)
    {
        switch (_solverTile.solverTileState)
        {
        case visible:
        output += '0' + _solverTile.adjBombsAmount;
            break;
        case unknown:
            output += '#';
            break;
        case flagged:
            output += '@';
            break;
        default:
            output += '-';
            break;
        }
        if (_solverTile.x == m_sizeX - 1)
        {
            output += '\n';
        }
    }
    return output;
}

void mineSweeperSolver::reset()
{

}

coordinate mineSweeperSolver::getReccomendedClick()
{
    coordinate reccomendedClick = coordinate(UINT16_MAX, UINT16_MAX);

    if (!m_reccomendedClicks.empty())
    {
        solverTile* solverTilePtr = m_reccomendedClicks[m_reccomendedClicks.size() - 1];
        reccomendedClick = coordinate(solverTilePtr->x, solverTilePtr->y);
        m_reccomendedClicks.erase(m_reccomendedClicks.begin() + (m_reccomendedClicks.size() - 1));
    }

    return reccomendedClick;
}

coordinate mineSweeperSolver::getReccomendedFlag()
{
    coordinate reccomendedFlag = coordinate(UINT16_MAX, UINT16_MAX);

    if (!m_reccomendedFlags.empty())
    {
        solverTile* solverTilePtr = m_reccomendedFlags[m_reccomendedFlags.size() - 1];
        reccomendedFlag = coordinate(solverTilePtr->x, solverTilePtr->y);
        m_reccomendedFlags.erase(m_reccomendedFlags.begin() + (m_reccomendedFlags.size() - 1));
    }

    return reccomendedFlag;
}

//
// Private
//

inline solverTile* mineSweeperSolver::searchSolverTile(const uint16_t& x, const uint16_t& y)
{
    if (x >= m_sizeX || y >= m_sizeY)
    {
        return nullptr;
    }
    return &m_solverTiles[x + y*m_sizeX];
}

inline solverTile* mineSweeperSolver::searchSolverTile(const uint16_t& index)
{
    return &m_solverTiles[index];
}

inline uint16_t mineSweeperSolver::getSolverTileIndex(solverTile* solverTilePtr)
{
    return solverTilePtr->x + solverTilePtr->y*m_sizeX;
}

inline bool mineSweeperSolver::hasReccomendedSolverTiles()
{
    return !m_reccomendedClicks.empty() || !m_reccomendedFlags.empty();
}

inline void mineSweeperSolver::flagSolverTile(solverTile& solverTileOut)
{
    solverTileOut.solverTileState = flagged;
    m_reccomendedFlags.push_back(&solverTileOut);
}

inline void mineSweeperSolver::clickSolverTile(solverTile& solverTileOut)
{
    solverTileOut.solverTileState = clicked;
    m_reccomendedClicks.push_back(&solverTileOut);
}

void mineSweeperSolver::generateSolverTiles()
{
    for (uint16_t y = 0; y < m_sizeY; y++)
    {
        for (uint16_t x = 0; x < m_sizeX; x++)
        {
            m_solverTiles.push_back(solverTile(x, y));
        }
    }

    int16_t offsets[8][2] = {{-1,  1}, {0,  1}, {1,  1}, 
                             {-1,  0},          {1,  0}, 
                             {-1, -1}, {0, -1}, {1, -1}};

    for (solverTile& refSolverTile : m_solverTiles)
    {
        const uint16_t& x = refSolverTile.x;
        const uint16_t& y = refSolverTile.y;
        for (uint16_t i = 0u; i < 8u; i++)
        {
            solverTile* adjSolverTile = searchSolverTile(x+offsets[i][0], y+offsets[i][1]);
            if (!adjSolverTile)
            {
                continue;
            }
            refSolverTile.adjSolverTiles.push_back(adjSolverTile);
        }
    }
}

void mineSweeperSolver::readMineMap(const std::string& mineSweeperMap)
{
    uint16_t index = 0;
    for (const char& character : mineSweeperMap)
    {
        switch (character)
        {
        case '\n':
            break;
        case '#':
            m_solverTiles[index].solverTileState = unknown;
            index++;
            break;
        case '@':
            m_solverTiles[index].solverTileState = flagged;
            index++;
            break;
        case ' ':
            m_solverTiles[index].solverTileState = visible;
            m_solverTiles[index].adjBombsAmount = 0;
            index++;
            break;
        default:
            m_solverTiles[index].solverTileState = visible;
            m_solverTiles[index].adjBombsAmount = character - '0';
            index++;
            break;
        }
    }
}

inline uint16_t mineSweeperSolver::getEffectiveBombCount(const solverTile& solverTilePtr)
{
    uint16_t effectiveBombCount = solverTilePtr.adjBombsAmount;
    for (solverTile* adjSolverTile : solverTilePtr.adjSolverTiles)
    {
        effectiveBombCount -= adjSolverTile->solverTileState == flagged;
    }
    return effectiveBombCount;
}

inline uint16_t mineSweeperSolver::getAdjUnknownCount(const solverTile& solverTilePtr)
{
    uint16_t getAdjUnknownCount = 0;
    for (solverTile* adjSolverTile : solverTilePtr.adjSolverTiles)
    {
        getAdjUnknownCount += adjSolverTile->solverTileState == unknown;
    }
    return getAdjUnknownCount;
}

void mineSweeperSolver::fastBombFinder()
{
    for (solverTile& solverTileRef : m_solverTiles)
    {
        if (solverTileRef.solverTileState != visible)
        {
            continue;
        }
        if (getAdjUnknownCount(solverTileRef) == getEffectiveBombCount(solverTileRef))
        {
            for (solverTile* adjSolverTile : solverTileRef.adjSolverTiles)
            {
                if (adjSolverTile->solverTileState != unknown)
                {
                    continue;
                }
                flagSolverTile(*adjSolverTile);
            }
        }
    }

    for (solverTile& solverTileRef : m_solverTiles)
    {
        if (solverTileRef.solverTileState != visible)
        {
            continue;
        }
        if (getEffectiveBombCount(solverTileRef) == 0)
        {
            for (solverTile* adjSolverTile : solverTileRef.adjSolverTiles)
            {
                if (adjSolverTile->solverTileState != unknown)
                {
                    continue;
                }
                clickSolverTile(*adjSolverTile);
            }
        }
    }
}

uint16_t mineSweeperSolver::getIntersectionSizeBetweenTileUnknownAdjs(const solverTile* solverTilePtrA, const solverTile* solverTilePtrB)
{
    uint16_t intersectionSizeBetweenTileUnknownAdjs = 0;

    for (solverTile* adjSolverTileA : solverTilePtrA->adjSolverTiles)
    {
        if (adjSolverTileA->solverTileState != unknown)
        {
            continue;
        }
        for (solverTile* adjSolverTileB : solverTilePtrB->adjSolverTiles)
        {
            if (adjSolverTileB->solverTileState != unknown)
            {
                continue;
            }
            if (adjSolverTileA == adjSolverTileB)
            {
                intersectionSizeBetweenTileUnknownAdjs++;
                break;
            }
        }
    }

    return intersectionSizeBetweenTileUnknownAdjs;
}

void mineSweeperSolver::clickTilesInAMinusBSet(solverTile* solverTilePtrA, solverTile* solverTilePtrB)
{
    for (solverTile* adjSolverTileA : solverTilePtrA->adjSolverTiles)
    {
        if (adjSolverTileA->solverTileState != unknown)
        {
            continue;
        }
        bool inBSet = false;
        for (solverTile* adjSolverTileB : solverTilePtrB->adjSolverTiles)
        {
            if (adjSolverTileB->solverTileState != unknown)
            {
                continue;
            }
            if (adjSolverTileA == adjSolverTileB)
            {
                inBSet = true;
                break;
            }
        }
        if (inBSet)
        {
            continue;
        }
        clickSolverTile(*adjSolverTileA);
    }
}

void mineSweeperSolver::flagTilesInAMinusBSet(solverTile* solverTilePtrA, solverTile* solverTilePtrB)
{
    for (solverTile* adjSolverTileA : solverTilePtrA->adjSolverTiles)
    {
        if (adjSolverTileA->solverTileState != unknown)
        {
            continue;
        }
        bool inBSet = false;
        for (solverTile* adjSolverTileB : solverTilePtrB->adjSolverTiles)
        {
            if (adjSolverTileB->solverTileState != unknown)
            {
                continue;
            }
            if (adjSolverTileA == adjSolverTileB)
            {
                inBSet = true;
                break;
            }
        }
        if (inBSet)
        {
            continue;
        }
        flagSolverTile(*adjSolverTileA);
    }
}

void mineSweeperSolver::flagTilesInAIntersectBSet(solverTile* solverTilePtrA, solverTile* solverTilePtrB)
{
    for (solverTile* adjSolverTileA : solverTilePtrA->adjSolverTiles)
    {
        if (adjSolverTileA->solverTileState != unknown)
        {
            continue;
        }
        for (solverTile* adjSolverTileB : solverTilePtrB->adjSolverTiles)
        {
            if (adjSolverTileB->solverTileState != unknown)
            {
                continue;
            }
            if (adjSolverTileA == adjSolverTileB)
            {
                flagSolverTile(*adjSolverTileA);
                break;
            }
        }
    }
}

void mineSweeperSolver::patternBombFinder()
{
    for (solverTile& solverTileRef : m_solverTiles)
    {
        if (solverTileRef.solverTileState != visible)
        {
            continue;
        }
        int16_t tileSetSize = getAdjUnknownCount(solverTileRef);
        int16_t tileBombCount = getEffectiveBombCount(solverTileRef);
        for (solverTile* adjSolverTile : solverTileRef.adjSolverTiles)
        {
            if (adjSolverTile->solverTileState != visible)
            {
                continue;
            }

            int16_t adjBombCount = getEffectiveBombCount(*adjSolverTile);
            int16_t adjSetSize = getAdjUnknownCount(*adjSolverTile);

            int16_t intersectionSizeBetweenTileUnknownAdjs = getIntersectionSizeBetweenTileUnknownAdjs(&solverTileRef, adjSolverTile);

            int16_t tileMinusAdjSetSize = tileSetSize - intersectionSizeBetweenTileUnknownAdjs;
            int16_t adjMinusTileSetSize = adjSetSize - intersectionSizeBetweenTileUnknownAdjs;
            int16_t minBombsInIntersection = tileBombCount - tileMinusAdjSetSize;

            if (adjBombCount == minBombsInIntersection)
            {
                clickTilesInAMinusBSet(adjSolverTile, &solverTileRef);

                if (intersectionSizeBetweenTileUnknownAdjs == minBombsInIntersection)
                {
                    flagTilesInAIntersectBSet(&solverTileRef, adjSolverTile);
                }

                if (adjMinusTileSetSize == tileBombCount - minBombsInIntersection)
                {
                    flagTilesInAMinusBSet(&solverTileRef, adjSolverTile);
                }
            }
        }
    }
}

void mineSweeperSolver::groupTiles()
{
    uint16_t currGroup = 0u;
    uint16_t groupCount = m_unknownGroupedSolverTiles.size();
    for (int group = 0; group < groupCount; group++)
    {
        m_unknownGroupedSolverTiles[group].clear();
        m_visibleGroupedSolverTiles[group].clear();
    }
    for (solverTile& solverTileRef : m_solverTiles)
    {
        solverTileRef.visited = false;
    }
    for (solverTile& solverTileRef : m_solverTiles)
    {
        if (solverTileRef.solverTileState != visible || solverTileRef.visited)
        {
            continue;
        }

        bool hasUnknownAdj = false;

        for (solverTile* adjSolverTile : solverTileRef.adjSolverTiles)
        {
            if (adjSolverTile->solverTileState == unknown)
            {
                hasUnknownAdj = true;
                break;
            }
        }

        if (!hasUnknownAdj)
        {
            continue;
        }

        if (currGroup == groupCount)
        {
            m_unknownGroupedSolverTiles.push_back(std::vector<solverTile*>());
            m_visibleGroupedSolverTiles.push_back(std::vector<solverTile*>());
            groupCount++;
        }

        groupTilesReccursion(&solverTileRef, currGroup);
        currGroup++;
    }
}

void mineSweeperSolver::groupTilesReccursion(solverTile* currTilePtr, const uint16_t& group)
{
    currTilePtr->visited = true;
    if (currTilePtr->solverTileState == visible)
    {
        m_visibleGroupedSolverTiles[group].push_back(currTilePtr);
    }
    else
    {
        m_unknownGroupedSolverTiles[group].push_back(currTilePtr);
    }

    for (solverTile* adjTile : currTilePtr->adjSolverTiles)
    {
        if (adjTile->visited || adjTile->solverTileState == flagged || (adjTile->solverTileState == visible && adjTile->adjBombsAmount == 0) ||
           (currTilePtr->solverTileState == unknown && adjTile->solverTileState == unknown && !shareSameNumbered(currTilePtr, adjTile)))
        {
            continue;
        }

        groupTilesReccursion(adjTile, group);
    }
}

bool mineSweeperSolver::shareSameNumbered(const solverTile* solverTilePtrA, const solverTile* solverTilePtrB)
{
    for (solverTile* adjSolverTileA : solverTilePtrA->adjSolverTiles)
    {
        if (adjSolverTileA->solverTileState != visible)
        {
            continue;
        }
        for (solverTile* adjSolverTileB : solverTilePtrB->adjSolverTiles)
        {
            if (adjSolverTileB->solverTileState != visible)
            {
                continue;
            }

            if (adjSolverTileA == adjSolverTileB)
            {
                return true;
            }
        }
    }
    return false;
}

void mineSweeperSolver::getAllSolutions()
{

}