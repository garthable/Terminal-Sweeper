#include "mineSweeperSolver.hpp"
#include <iostream>

#define print(input) std::cout << input << std::endl

//
// Public
//

MineSweeperSolver::MineSweeperSolver(const uint16_t& sizeX, const uint16_t& sizeY, const uint16_t& bombCount)
{
    m_unknownTileCount = 0;
    m_sizeX = sizeX;
    m_sizeY = sizeY;
    m_bombCount = bombCount;

    generateSolverTiles();
}

void MineSweeperSolver::update(const std::string& mineSweeperMap)
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

    getAllSolutions();

    if (hasReccomendedSolverTiles())
    {
        return;
    }

    clickLowestProb();
}

std::string MineSweeperSolver::getSolverMap()
{
    std::string output = "";
    for (const SolverTile& _solverTile : m_solverTiles)
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

void MineSweeperSolver::reset(const uint16_t& bombCount)
{
    m_bombCount = bombCount;
    m_unknownTileCount = 0;
    m_reccomendedClicks.clear();
    m_reccomendedFlags.clear();
    for (SolverTile& solverTile : m_solverTiles)
    {
        solverTile.visited = false;
        solverTile.adjBombsAmount = 0;
        solverTile.solverTileState = unknown;
        solverTile.bombProbability = 0.0f;
    }

}

Coordinate MineSweeperSolver::getReccomendedClick()
{
    Coordinate reccomendedClick = Coordinate(UINT16_MAX, UINT16_MAX);

    if (!m_reccomendedClicks.empty())
    {
        SolverTile* solverTilePtr = m_reccomendedClicks.back();
        reccomendedClick = Coordinate(solverTilePtr->x, solverTilePtr->y);
        m_reccomendedClicks.popBack();
    }

    return reccomendedClick;
}

Coordinate MineSweeperSolver::getReccomendedFlag()
{
    Coordinate reccomendedFlag = Coordinate(UINT16_MAX, UINT16_MAX);

    if (!m_reccomendedFlags.empty())
    {
        SolverTile* solverTilePtr = m_reccomendedFlags.back();
        reccomendedFlag = Coordinate(solverTilePtr->x, solverTilePtr->y);
        m_reccomendedFlags.popBack();
    }

    return reccomendedFlag;
}

//
// Private
//

inline SolverTile* MineSweeperSolver::searchSolverTile(const uint16_t& x, const uint16_t& y)
{
    if (x >= m_sizeX || y >= m_sizeY)
    {
        return nullptr;
    }
    return &m_solverTiles[x + y*m_sizeX];
}

inline SolverTile* MineSweeperSolver::searchSolverTile(const uint16_t& index)
{
    return &m_solverTiles[index];
}

inline uint16_t MineSweeperSolver::getSolverTileIndex(SolverTile* solverTilePtr)
{
    return solverTilePtr->x + solverTilePtr->y*m_sizeX;
}

inline bool MineSweeperSolver::hasReccomendedSolverTiles()
{
    return !m_reccomendedClicks.empty() || !m_reccomendedFlags.empty();
}

inline void MineSweeperSolver::flagSolverTile(SolverTile& solverTileOut)
{
    if (solverTileOut.solverTileState == flagged)
    {
        return;
    }
    m_bombCount--;
    solverTileOut.solverTileState = flagged;
    m_reccomendedFlags.pushBack(&solverTileOut);
}

inline void MineSweeperSolver::clickSolverTile(SolverTile& solverTileOut)
{
    if (solverTileOut.solverTileState == clicked || solverTileOut.solverTileState == visible)
    {
        return;
    }
    solverTileOut.solverTileState = clicked;
    m_reccomendedClicks.pushBack(&solverTileOut);
}

void MineSweeperSolver::generateSolverTiles()
{
    for (uint16_t y = 0; y < m_sizeY; y++)
    {
        for (uint16_t x = 0; x < m_sizeX; x++)
        {
            m_solverTiles.emplaceBack(x, y);
        }
    }

    int16_t offsets[8][2] = {{-1,  1}, {0,  1}, {1,  1}, 
                             {-1,  0},          {1,  0}, 
                             {-1, -1}, {0, -1}, {1, -1}};

    for (SolverTile& refSolverTile : m_solverTiles)
    {
        const uint16_t& x = refSolverTile.x;
        const uint16_t& y = refSolverTile.y;
        for (uint16_t i = 0u; i < 8u; i++)
        {
            SolverTile* adjSolverTile = searchSolverTile(x+offsets[i][0], y+offsets[i][1]);
            if (!adjSolverTile)
            {
                continue;
            }
            refSolverTile.adjSolverTiles.pushBack(adjSolverTile);
        }
    }
}

void MineSweeperSolver::readMineMap(const std::string& mineSweeperMap)
{
    uint16_t index = 0;
    m_unknownTileCount = 0;
    for (const char& character : mineSweeperMap)
    {
        switch (character)
        {
        case '\n':
            break;
        case '#':
            m_solverTiles[index].solverTileState = unknown;
            index++;
            m_unknownTileCount++;
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

inline uint16_t MineSweeperSolver::getEffectiveBombCount(const SolverTile& solverTilePtr)
{
    uint16_t effectiveBombCount = solverTilePtr.adjBombsAmount;
    for (SolverTile* adjSolverTile : solverTilePtr.adjSolverTiles)
    {
        effectiveBombCount -= adjSolverTile->solverTileState == flagged;
    }
    return effectiveBombCount;
}

inline uint16_t MineSweeperSolver::getAdjUnknownCount(const SolverTile& solverTilePtr)
{
    uint16_t getAdjUnknownCount = 0;
    for (SolverTile* adjSolverTile : solverTilePtr.adjSolverTiles)
    {
        getAdjUnknownCount += adjSolverTile->solverTileState == unknown;
    }
    return getAdjUnknownCount;
}

void MineSweeperSolver::fastBombFinder()
{
    for (SolverTile& solverTileRef : m_solverTiles)
    {
        if (solverTileRef.solverTileState != visible)
        {
            continue;
        }
        if (getAdjUnknownCount(solverTileRef) == getEffectiveBombCount(solverTileRef))
        {
            for (SolverTile* adjSolverTile : solverTileRef.adjSolverTiles)
            {
                if (adjSolverTile->solverTileState != unknown)
                {
                    continue;
                }
                flagSolverTile(*adjSolverTile);
            }
        }
    }

    for (SolverTile& solverTileRef : m_solverTiles)
    {
        if (solverTileRef.solverTileState != visible)
        {
            continue;
        }
        if (getEffectiveBombCount(solverTileRef) == 0)
        {
            for (SolverTile* adjSolverTile : solverTileRef.adjSolverTiles)
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

uint16_t MineSweeperSolver::getIntersectionSizeBetweenTileUnknownAdjs(const SolverTile* solverTilePtrA, const SolverTile* solverTilePtrB)
{
    uint16_t intersectionSizeBetweenTileUnknownAdjs = 0;

    for (SolverTile* adjSolverTileA : solverTilePtrA->adjSolverTiles)
    {
        if (adjSolverTileA->solverTileState != unknown)
        {
            continue;
        }
        for (SolverTile* adjSolverTileB : solverTilePtrB->adjSolverTiles)
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

void MineSweeperSolver::clickTilesInAMinusBSet(SolverTile* solverTilePtrA, SolverTile* solverTilePtrB)
{
    for (SolverTile* adjSolverTileA : solverTilePtrA->adjSolverTiles)
    {
        if (adjSolverTileA->solverTileState != unknown)
        {
            continue;
        }
        bool inBSet = false;
        for (SolverTile* adjSolverTileB : solverTilePtrB->adjSolverTiles)
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

void MineSweeperSolver::flagTilesInAMinusBSet(SolverTile* solverTilePtrA, SolverTile* solverTilePtrB)
{
    for (SolverTile* adjSolverTileA : solverTilePtrA->adjSolverTiles)
    {
        if (adjSolverTileA->solverTileState != unknown)
        {
            continue;
        }
        bool inBSet = false;
        for (SolverTile* adjSolverTileB : solverTilePtrB->adjSolverTiles)
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

void MineSweeperSolver::flagTilesInAIntersectBSet(SolverTile* solverTilePtrA, SolverTile* solverTilePtrB)
{
    for (SolverTile* adjSolverTileA : solverTilePtrA->adjSolverTiles)
    {
        if (adjSolverTileA->solverTileState != unknown)
        {
            continue;
        }
        for (SolverTile* adjSolverTileB : solverTilePtrB->adjSolverTiles)
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

void MineSweeperSolver::patternBombFinder()
{
    for (SolverTile& solverTileRef : m_solverTiles)
    {
        if (solverTileRef.solverTileState != visible)
        {
            continue;
        }
        int16_t tileSetSize = getAdjUnknownCount(solverTileRef);
        int16_t tileBombCount = getEffectiveBombCount(solverTileRef);
        for (SolverTile* adjSolverTile : solverTileRef.adjSolverTiles)
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

void MineSweeperSolver::groupTiles()
{
    uint16_t groupCount = m_groupedHiddenSolverTiles.size();
    for (int group = 0; group < groupCount; group++)
    {
        m_groupedHiddenSolverTiles[group].clear();
        m_groupedVisibleSolverTiles[group].clear();
    }
    for (SolverTile& solverTileRef : m_solverTiles)
    {
        solverTileRef.visited = false;
    }
    uint16_t currGroup = 0u;
    for (SolverTile& solverTileRef : m_solverTiles)
    {
        if (solverTileRef.solverTileState != visible || solverTileRef.visited)
        {
            continue;
        }

        bool hasUnknownAdj = false;

        for (SolverTile* adjSolverTile : solverTileRef.adjSolverTiles)
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
            m_groupedHiddenSolverTiles.emplaceBack();
            m_groupedVisibleSolverTiles.emplaceBack();
            groupCount++;
        }

        groupTilesReccursion(&solverTileRef, currGroup);
        currGroup++;
    }
}

void MineSweeperSolver::groupTilesReccursion(SolverTile* currTilePtr, const uint16_t& group)
{
    currTilePtr->visited = true;
    if (currTilePtr->solverTileState == visible)
    {
        m_groupedVisibleSolverTiles[group].pushBack(currTilePtr);
    }
    else
    {
        m_groupedHiddenSolverTiles[group].pushBack(currTilePtr);
    }

    for (SolverTile* adjTile : currTilePtr->adjSolverTiles)
    {
        if (adjTile->visited || adjTile->solverTileState == flagged || 
        (adjTile->solverTileState == visible && getEffectiveBombCount(*adjTile) == 0) ||
        (currTilePtr->solverTileState == unknown && adjTile->solverTileState == unknown && !shareSameNumbered(currTilePtr, adjTile)))
        {
            continue;
        }

        groupTilesReccursion(adjTile, group);
    }
}

bool MineSweeperSolver::shareSameNumbered(const SolverTile* solverTilePtrA, const SolverTile* solverTilePtrB)
{
    for (SolverTile* adjSolverTileA : solverTilePtrA->adjSolverTiles)
    {
        if (adjSolverTileA->solverTileState != visible)
        {
            continue;
        }
        for (SolverTile* adjSolverTileB : solverTilePtrB->adjSolverTiles)
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

void MineSweeperSolver::getAllSolutions()
{
    groupTiles();
    double unknownIsolatedTiles = static_cast<double>(m_unknownTileCount);
    for (auto hiddenSolverTiles : m_groupedHiddenSolverTiles)
    {
        unknownIsolatedTiles -= static_cast<double>(hiddenSolverTiles.size());
    }
    int16_t minBombCount = m_bombCount - static_cast<uint16_t>(unknownIsolatedTiles);
    if (minBombCount < 0)
    {
        minBombCount = 0;
    }
    for (SolverTile& solverTile : m_solverTiles)
    {
        solverTile.bombProbability = -1;
    }
    double bombsRemaining;
    applyProbabilities(m_groupedVisibleSolverTiles, m_groupedHiddenSolverTiles, m_bombCount, minBombCount, bombsRemaining);
    double isolatedTileBombProb = bombsRemaining/unknownIsolatedTiles;
    for (SolverTile& solverTile : m_solverTiles)
    {
        if (solverTile.solverTileState != unknown)
        {
            continue;
        }
        else if (solverTile.bombProbability == -1)
        {
            solverTile.bombProbability = isolatedTileBombProb;
        }
    }
    for (SolverTile& solverTile : m_solverTiles)
    {
        if (solverTile.solverTileState != unknown)
        {
            continue;
        }
        else if (solverTile.bombProbability == 0)
        {
            clickSolverTile(solverTile);
        }
        else if (solverTile.bombProbability == 1)
        {
            flagSolverTile(solverTile);
        }
    }
}

double MineSweeperSolver::getProbOfHavingNoAdjBombs(const SolverTile& solverTile)
{
    double probability = 1;
    for (const SolverTile* adjSolverTile : solverTile.adjSolverTiles)
    {
        if (adjSolverTile->solverTileState == flagged)
        {
            return 0;
        }
        else if (adjSolverTile->solverTileState == visible)
        {
            continue;
        }
        probability *= (1.0f - adjSolverTile->bombProbability);
    }
    return probability;
}

void MineSweeperSolver::clickLowestProb()
{
    int16_t lowestIndex = -1;
    double lowestProbability = 1.0f;
    double lowestZeroProb = 0.0f;
    uint16_t size = m_solverTiles.size();
    uint16_t amountCheck = 0;
    for (int16_t i = 0; i < size; i++)
    {
        SolverTile& solverTile = m_solverTiles[i];
        if (solverTile.solverTileState != unknown)
        {
            continue;
        }
        else if (solverTile.bombProbability < lowestProbability)
        {
            lowestIndex = i;
            lowestProbability = solverTile.bombProbability;
            lowestZeroProb = getProbOfHavingNoAdjBombs(solverTile);
        }
        else if (solverTile.bombProbability == lowestProbability)
        {
            double otherZeroProb = getProbOfHavingNoAdjBombs(solverTile);
            if (otherZeroProb > lowestZeroProb)
            {
                lowestIndex = i;
                lowestProbability = solverTile.bombProbability;
                lowestZeroProb = otherZeroProb;
            }
        }
        else if (lowestIndex == -1)
        {
            lowestIndex = i;
            lowestProbability = solverTile.bombProbability;
            lowestZeroProb = getProbOfHavingNoAdjBombs(solverTile);
        }
    }
    if (lowestIndex != -1)
    {
        clickSolverTile(m_solverTiles[lowestIndex]);
        return;
    }
    throw std::runtime_error("Guess could not find anything! " + std::to_string(amountCheck));
}