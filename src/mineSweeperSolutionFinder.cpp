#include "../include/mineSweeperSolutionFinder.h"
#include <iostream>

MineSweeperSolutionFinder::MineSweeperSolutionFinder()
{
    m_averageBombsUsed = 0;
    m_hardcodedCombinations = 
    {
        {{0}},
        {{0}, {1}},
        {{0, 1}},
        {{0}, {1}, {2}},
        {{0, 1}, {0, 2}, {1, 2}},
        {{0, 1, 2}},
        {{0}, {1}, {2}, {3}}, 
        {{0, 1}, {0, 2}, {0, 3}, {1, 2}, {1, 3}, {2, 3}}, 
        {{0, 1, 2}, {0, 1, 3}, {0, 2, 3}, {1, 2, 3}}, 
        {{0, 1, 2, 3}}, 
        {{0}, {1}, {2}, {3}, {4}}, 
        {{0, 1}, {0, 2}, {0, 3}, {0, 4}, {1, 2}, {1, 3}, {1, 4}, {2, 3}, {2, 4}, {3, 4}}, 
        {{0, 1, 2}, {0, 1, 3}, {0, 1, 4}, {0, 2, 3}, {0, 2, 4}, {0, 3, 4}, {1, 2, 3}, {1, 2, 4}, {1, 3, 4}, {2, 3, 4}}, 
        {{0, 1, 2, 3}, {0, 1, 2, 4}, {0, 1, 3, 4}, {0, 2, 3, 4}, {1, 2, 3, 4}}, 
        {{0, 1, 2, 3, 4}}, 
        {{0}, {1}, {2}, {3}, {4}, {5}}, 
        {{0, 1}, {0, 2}, {0, 3}, {0, 4}, {0, 5}, {1, 2}, {1, 3}, {1, 4}, {1, 5}, {2, 3}, {2, 4}, {2, 5}, {3, 4}, {3, 5}, {4, 5}}, 
        {{0, 1, 2}, {0, 1, 3}, {0, 1, 4}, {0, 1, 5}, {0, 2, 3}, {0, 2, 4}, {0, 2, 5}, {0, 3, 4}, {0, 3, 5}, {0, 4, 5}, {1, 2, 3}, {1, 2, 4}, {1, 2, 5}, {1, 3, 4}, {1, 3, 5}, {1, 4, 5}, {2, 3, 4}, {2, 3, 5}, {2, 4, 5}, {3, 4, 5}}, 
        {{0, 1, 2, 3}, {0, 1, 2, 4}, {0, 1, 2, 5}, {0, 1, 3, 4}, {0, 1, 3, 5}, {0, 1, 4, 5}, {0, 2, 3, 4}, {0, 2, 3, 5}, {0, 2, 4, 5}, {0, 3, 4, 5}, {1, 2, 3, 4}, {1, 2, 3, 5}, {1, 2, 4, 5}, {1, 3, 4, 5}, {2, 3, 4, 5}}, 
        {{0, 1, 2, 3, 4}, {0, 1, 2, 3, 5}, {0, 1, 2, 4, 5}, {0, 1, 3, 4, 5}, {0, 2, 3, 4, 5}, {1, 2, 3, 4, 5}}, 
        {{0, 1, 2, 3, 4, 5}}, 
        {{0}, {1}, {2}, {3}, {4}, {5}, {6}}, 
        {{0, 1}, {0, 2}, {0, 3}, {0, 4}, {0, 5}, {0, 6}, {1, 2}, {1, 3}, {1, 4}, {1, 5}, {1, 6}, {2, 3}, {2, 4}, {2, 5}, {2, 6}, {3, 4}, {3, 5}, {3, 6}, {4, 5}, {4, 6}, {5, 6}}, 
        {{0, 1, 2}, {0, 1, 3}, {0, 1, 4}, {0, 1, 5}, {0, 1, 6}, {0, 2, 3}, {0, 2, 4}, {0, 2, 5}, {0, 2, 6}, {0, 3, 4}, {0, 3, 5}, {0, 3, 6}, {0, 4, 5}, {0, 4, 6}, {0, 5, 6}, {1, 2, 3}, {1, 2, 4}, {1, 2, 5}, {1, 2, 6}, {1, 3, 4}, {1, 3, 5}, {1, 3, 6}, {1, 4, 5}, {1, 4, 6}, {1, 5, 6}, {2, 3, 4}, {2, 3, 5}, {2, 3, 6}, {2, 4, 5}, {2, 4, 6}, {2, 5, 6}, {3, 4, 5}, {3, 4, 6}, {3, 5, 6}, {4, 5, 6}}, 
        {{0, 1, 2, 3}, {0, 1, 2, 4}, {0, 1, 2, 5}, {0, 1, 2, 6}, {0, 1, 3, 4}, {0, 1, 3, 5}, {0, 1, 3, 6}, {0, 1, 4, 5}, {0, 1, 4, 6}, {0, 1, 5, 6}, {0, 2, 3, 4}, {0, 2, 3, 5}, {0, 2, 3, 6}, {0, 2, 4, 5}, {0, 2, 4, 6}, {0, 2, 5, 6}, {0, 3, 4, 5}, {0, 3, 4, 6}, {0, 3, 5, 6}, {0, 4, 5, 6}, {1, 2, 3, 4}, {1, 2, 3, 5}, {1, 2, 3, 6}, {1, 2, 4, 5}, {1, 2, 4, 6}, {1, 2, 5, 6}, {1, 3, 4, 5}, {1, 3, 4, 6}, {1, 3, 5, 6}, {1, 4, 5, 6}, {2, 3, 4, 5}, {2, 3, 4, 6}, {2, 3, 5, 6}, {2, 4, 5, 6}, {3, 4, 5, 6}}, 
        {{0, 1, 2, 3, 4}, {0, 1, 2, 3, 5}, {0, 1, 2, 3, 6}, {0, 1, 2, 4, 5}, {0, 1, 2, 4, 6}, {0, 1, 2, 5, 6}, {0, 1, 3, 4, 5}, {0, 1, 3, 4, 6}, {0, 1, 3, 5, 6}, {0, 1, 4, 5, 6}, {0, 2, 3, 4, 5}, {0, 2, 3, 4, 6}, {0, 2, 3, 5, 6}, {0, 2, 4, 5, 6}, {0, 3, 4, 5, 6}, {1, 2, 3, 4, 5}, {1, 2, 3, 4, 6}, {1, 2, 3, 5, 6}, {1, 2, 4, 5, 6}, {1, 3, 4, 5, 6}, {2, 3, 4, 5, 6}}, 
        {{0, 1, 2, 3, 4, 5}, {0, 1, 2, 3, 4, 6}, {0, 1, 2, 3, 5, 6}, {0, 1, 2, 4, 5, 6}, {0, 1, 3, 4, 5, 6}, {0, 2, 3, 4, 5, 6}, {1, 2, 3, 4, 5, 6}}, 
        {{0, 1, 2, 3, 4, 5, 6}}, 
        {{0}, {1}, {2}, {3}, {4}, {5}, {6}, {7}}, 
        {{0, 1}, {0, 2}, {0, 3}, {0, 4}, {0, 5}, {0, 6}, {0, 7}, {1, 2}, {1, 3}, {1, 4}, {1, 5}, {1, 6}, {1, 7}, {2, 3}, {2, 4}, {2, 5}, {2, 6}, {2, 7}, {3, 4}, {3, 5}, {3, 6}, {3, 7}, {4, 5}, {4, 6}, {4, 7}, {5, 6}, {5, 7}, {6, 7}}, 
        {{0, 1, 2}, {0, 1, 3}, {0, 1, 4}, {0, 1, 5}, {0, 1, 6}, {0, 1, 7}, {0, 2, 3}, {0, 2, 4}, {0, 2, 5}, {0, 2, 6}, {0, 2, 7}, {0, 3, 4}, {0, 3, 5}, {0, 3, 6}, {0, 3, 7}, {0, 4, 5}, {0, 4, 6}, {0, 4, 7}, {0, 5, 6}, {0, 5, 7}, {0, 6, 7}, {1, 2, 3}, {1, 2, 4}, {1, 2, 5}, {1, 2, 6}, {1, 2, 7}, {1, 3, 4}, {1, 3, 5}, {1, 3, 6}, {1, 3, 7}, {1, 4, 5}, {1, 4, 6}, {1, 4, 7}, {1, 5, 6}, {1, 5, 7}, {1, 6, 7}, {2, 3, 4}, {2, 3, 5}, {2, 3, 6}, {2, 3, 7}, {2, 4, 5}, {2, 4, 6}, {2, 4, 7}, {2, 5, 6}, {2, 5, 7}, {2, 6, 7}, {3, 4, 5}, {3, 4, 6}, {3, 4, 7}, {3, 5, 6}, {3, 5, 7}, {3, 6, 7}, {4, 5, 6}, {4, 5, 7}, {4, 6, 7}, {5, 6, 7}}, 
        {{0, 1, 2, 3}, {0, 1, 2, 4}, {0, 1, 2, 5}, {0, 1, 2, 6}, {0, 1, 2, 7}, {0, 1, 3, 4}, {0, 1, 3, 5}, {0, 1, 3, 6}, {0, 1, 3, 7}, {0, 1, 4, 5}, {0, 1, 4, 6}, {0, 1, 4, 7}, {0, 1, 5, 6}, {0, 1, 5, 7}, {0, 1, 6, 7}, {0, 2, 3, 4}, {0, 2, 3, 5}, {0, 2, 3, 6}, {0, 2, 3, 7}, {0, 2, 4, 5}, {0, 2, 4, 6}, {0, 2, 4, 7}, {0, 2, 5, 6}, {0, 2, 5, 7}, {0, 2, 6, 7}, {0, 3, 4, 5}, {0, 3, 4, 6}, {0, 3, 4, 7}, {0, 3, 5, 6}, {0, 3, 5, 7}, {0, 3, 6, 7}, {0, 4, 5, 6}, {0, 4, 5, 7}, {0, 4, 6, 7}, {0, 5, 6, 7}, {1, 2, 3, 4}, {1, 2, 3, 5}, {1, 2, 3, 6}, {1, 2, 3, 7}, {1, 2, 4, 5}, {1, 2, 4, 6}, {1, 2, 4, 7}, {1, 2, 5, 6}, {1, 2, 5, 7}, {1, 2, 6, 7}, {1, 3, 4, 5}, {1, 3, 4, 6}, {1, 3, 4, 7}, {1, 3, 5, 6}, {1, 3, 5, 7}, {1, 3, 6, 7}, {1, 4, 5, 6}, {1, 4, 5, 7}, {1, 4, 6, 7}, {1, 5, 6, 7}, {2, 3, 4, 5}, {2, 3, 4, 6}, {2, 3, 4, 7}, {2, 3, 5, 6}, {2, 3, 5, 7}, {2, 3, 6, 7}, {2, 4, 5, 6}, {2, 4, 5, 7}, {2, 4, 6, 7}, {2, 5, 6, 7}, {3, 4, 5, 6}, {3, 4, 5, 7}, {3, 4, 6, 7}, {3, 5, 6, 7}, {4, 5, 6, 7}}, 
        {{0, 1, 2, 3, 4}, {0, 1, 2, 3, 5}, {0, 1, 2, 3, 6}, {0, 1, 2, 3, 7}, {0, 1, 2, 4, 5}, {0, 1, 2, 4, 6}, {0, 1, 2, 4, 7}, {0, 1, 2, 5, 6}, {0, 1, 2, 5, 7}, {0, 1, 2, 6, 7}, {0, 1, 3, 4, 5}, {0, 1, 3, 4, 6}, {0, 1, 3, 4, 7}, {0, 1, 3, 5, 6}, {0, 1, 3, 5, 7}, {0, 1, 3, 6, 7}, {0, 1, 4, 5, 6}, {0, 1, 4, 5, 7}, {0, 1, 4, 6, 7}, {0, 1, 5, 6, 7}, {0, 2, 3, 4, 5}, {0, 2, 3, 4, 6}, {0, 2, 3, 4, 7}, {0, 2, 3, 5, 6}, {0, 2, 3, 5, 7}, {0, 2, 3, 6, 7}, {0, 2, 4, 5, 6}, {0, 2, 4, 5, 7}, {0, 2, 4, 6, 7}, {0, 2, 5, 6, 7}, {0, 3, 4, 5, 6}, {0, 3, 4, 5, 7}, {0, 3, 4, 6, 7}, {0, 3, 5, 6, 7}, {0, 4, 5, 6, 7}, {1, 2, 3, 4, 5}, {1, 2, 3, 4, 6}, {1, 2, 3, 4, 7}, {1, 2, 3, 5, 6}, {1, 2, 3, 5, 7}, {1, 2, 3, 6, 7}, {1, 2, 4, 5, 6}, {1, 2, 4, 5, 7}, {1, 2, 4, 6, 7}, {1, 2, 5, 6, 7}, {1, 3, 4, 5, 6}, {1, 3, 4, 5, 7}, {1, 3, 4, 6, 7}, {1, 3, 5, 6, 7}, {1, 4, 5, 6, 7}, {2, 3, 4, 5, 6}, {2, 3, 4, 5, 7}, {2, 3, 4, 6, 7}, {2, 3, 5, 6, 7}, {2, 4, 5, 6, 7}, {3, 4, 5, 6, 7}}, 
        {{0, 1, 2, 3, 4, 5}, {0, 1, 2, 3, 4, 6}, {0, 1, 2, 3, 4, 7}, {0, 1, 2, 3, 5, 6}, {0, 1, 2, 3, 5, 7}, {0, 1, 2, 3, 6, 7}, {0, 1, 2, 4, 5, 6}, {0, 1, 2, 4, 5, 7}, {0, 1, 2, 4, 6, 7}, {0, 1, 2, 5, 6, 7}, {0, 1, 3, 4, 5, 6}, {0, 1, 3, 4, 5, 7}, {0, 1, 3, 4, 6, 7}, {0, 1, 3, 5, 6, 7}, {0, 1, 4, 5, 6, 7}, {0, 2, 3, 4, 5, 6}, {0, 2, 3, 4, 5, 7}, {0, 2, 3, 4, 6, 7}, {0, 2, 3, 5, 6, 7}, {0, 2, 4, 5, 6, 7}, {0, 3, 4, 5, 6, 7}, {1, 2, 3, 4, 5, 6}, {1, 2, 3, 4, 5, 7}, {1, 2, 3, 4, 6, 7}, {1, 2, 3, 5, 6, 7}, {1, 2, 4, 5, 6, 7}, {1, 3, 4, 5, 6, 7}, {2, 3, 4, 5, 6, 7}}, 
        {{0, 1, 2, 3, 4, 5, 6}, {0, 1, 2, 3, 4, 5, 7}, {0, 1, 2, 3, 4, 6, 7}, {0, 1, 2, 3, 5, 6, 7}, {0, 1, 2, 4, 5, 6, 7}, {0, 1, 3, 4, 5, 6, 7}, {0, 2, 3, 4, 5, 6, 7}, {1, 2, 3, 4, 5, 6, 7}}, 
        {{0, 1, 2, 3, 4, 5, 6, 7}},
        {{}}
    };
}

void MineSweeperSolutionFinder::applyProbabilities(const std::vector<std::vector<SolverTile*>>& groupedVisibleTiles,
                                std::vector<std::vector<SolverTile*>>& outGroupedHiddenTiles,
                                uint16_t maxBombs, uint16_t minBombs)
{
    if (groupedVisibleTiles.size() != outGroupedHiddenTiles.size())
    {
        throw std::runtime_error("Visible and hidden are not the same size!");
    }
    reset();
    getHidden(outGroupedHiddenTiles);
    getVisibles(groupedVisibleTiles);
    m_maxBombs = maxBombs;
    m_minBombs = minBombs;

    getSolutions();

    if (canSurpassMaxBombs() || canUndercutMinBombs())
    {
        applyProbabilitiesCombined();
        return;
    }
    applyProbabilitiesSeperate();
}

void MineSweeperSolutionFinder::reset()
{
    m_maxBombs = 0;
    m_averageBombsUsed = 0;
    m_groupedVisibleTiles.clear();
    m_groupedIncompleteSolutions.clear();
    m_groupedCompleteSolutions.clear();
}

double MineSweeperSolutionFinder::getAverageBombsUsed()
{
    return m_averageBombsUsed;
}

//
// Private:
//

void MineSweeperSolutionFinder::getHidden(const std::vector<std::vector<SolverTile*>>& groupedHiddenTiles)
{
    uint16_t groupSize = groupedHiddenTiles.size();
    for (int group = 0; group < groupSize; group++)
    {
        const std::vector<SolverTile*>& hiddenTiles = groupedHiddenTiles[group];
        if (hiddenTiles.size() == 0)
        {
            continue;
        }
        SolutionSet tempSolutionSet = SolutionSet();

        for (SolverTile* hiddenTilePtr : hiddenTiles)
        {
            HiddenTile hiddenTile = HiddenTile(hiddenTilePtr, false);
            tempSolutionSet.hiddenTiles.push_back(hiddenTile);
        }

        m_groupedIncompleteSolutions.push_back(std::vector<SolutionSet>());
        m_groupedIncompleteSolutions[group].push_back(tempSolutionSet);
    }
}

void MineSweeperSolutionFinder::getVisibles(const std::vector<std::vector<SolverTile*>>& groupedVisibleTiles) // MASSIVE readabilty issues here
{
    uint16_t groupSize = groupedVisibleTiles.size();
    for (int group = 0; group < groupSize; group++)
    {
        const std::vector<SolverTile*>& visibleTiles = groupedVisibleTiles[group];
        if (visibleTiles.size() == 0)
        {
            continue;
        }
        m_groupedVisibleTiles.push_back(std::vector<VisibleTile>());
        for (const SolverTile* visibleTilePtr : visibleTiles)
        {
            uint16_t effectiveBombCount = visibleTilePtr->adjBombsAmount;
            for (SolverTile* adjSolverTile : visibleTilePtr->adjSolverTiles)
            {
                effectiveBombCount -= (adjSolverTile->solverTileState == flagged);
            }
            m_groupedVisibleTiles[group].push_back(VisibleTile(effectiveBombCount));
            VisibleTile& mostRecentlyAddedVisibleTile = m_groupedVisibleTiles[group].back();

            for (SolverTile* adjHiddenTilePtr : visibleTilePtr->adjSolverTiles)
            {
                if (adjHiddenTilePtr->solverTileState != unknown) 
                {
                    continue;
                }
                
                int16_t hiddenTileIndex = searchHidden(adjHiddenTilePtr, group);

                if (hiddenTileIndex == -1)
                {
                    continue;
                }
                mostRecentlyAddedVisibleTile.adjHiddenTiles.push_back(hiddenTileIndex);
            }
        }
    }
}

inline int16_t MineSweeperSolutionFinder::searchHidden(const SolverTile* solverTile, const uint16_t& group)
{
    const std::vector<SolutionSet>& incompleteSolutions = m_groupedIncompleteSolutions[group];
    uint16_t incompleteSolutionsLength = incompleteSolutions[0].hiddenTiles.size();
    for (int i = 0; i < incompleteSolutionsLength; i++)
    {
        const HiddenTile& hiddenTile = incompleteSolutions[0].hiddenTiles[i];
        if (hiddenTile.originalTile == solverTile)
        {
            return i;
        }
    }
    return -1;
}

inline std::vector<std::vector<uint16_t>>& MineSweeperSolutionFinder::getHardcodedCombinations(uint16_t n, uint16_t r)
{
    if (n == 0 || r == 0 || r > n)
    {
        return m_hardcodedCombinations[36];
    }
    n--;
    uint16_t colomn = (n*(n+1))/2;
    uint16_t row = r - 1;

    return m_hardcodedCombinations[colomn + row];
}

void swap(std::vector<VisibleTile>& visibleTiles, uint16_t a, uint16_t b)
{
    VisibleTile visibleTileA = visibleTiles[a];
    VisibleTile visibleTileB = visibleTiles[b];

    visibleTiles[a] = visibleTileB;
    visibleTiles[b] = visibleTileA;
}

void MineSweeperSolutionFinder::sortVisibleTilesByCombinationSize(const uint16_t& group)
{
    SolutionSet& currSolutionSet = m_groupedIncompleteSolutions[group][0];
    currSolutionSet.reset();
    std::vector<VisibleTile>& visibleTiles = m_groupedVisibleTiles[group];
    uint16_t visibleTilesSize = visibleTiles.size();

    for (int i = 0; i < visibleTilesSize; i++)
    {
        uint16_t minIndex = i;
        uint16_t minCombinationAmount = getCombinationSize(visibleTiles[i], currSolutionSet);
        for (int j = i; j < visibleTilesSize; j++)
        {
            const VisibleTile& currVisibleTile = visibleTiles[j];
            const uint16_t currCombinationAmount = getCombinationSize(currVisibleTile, currSolutionSet);
            if (minCombinationAmount > currCombinationAmount)
            {
                minIndex = j;
                minCombinationAmount = currCombinationAmount;
            }
        }
        claimUnclaimedAdjTiles(visibleTiles[minIndex], currSolutionSet);
        swap(visibleTiles, i, minIndex);
    }
}

uint16_t MineSweeperSolutionFinder::getCombinationSize(const VisibleTile& currVisibleTile, const SolutionSet& currSolutionSet)
{
    uint16_t n = 0;
    for (const uint16_t& adjIndex : currVisibleTile.adjHiddenTiles)
    {
        const HiddenTile& currHiddenTile = currSolutionSet.hiddenTiles[adjIndex];
        if (currHiddenTile.claimed)
        {
            continue;
        }
        n++;
    }
    uint16_t r = currVisibleTile.bombCount;
    if (n == 0)
    {
        return 0;
    }
    else if (r > n)
    {
        return 1;
    }
    return getHardcodedCombinations(n, r).size();
}

void MineSweeperSolutionFinder::claimUnclaimedAdjTiles(VisibleTile& outCurrVisibleTile, SolutionSet& outCurrSolutionSet)
{
    for (const uint16_t& adjIndex : outCurrVisibleTile.adjHiddenTiles)
    {
        HiddenTile& outCurrHiddenTile = outCurrSolutionSet.hiddenTiles[adjIndex];
        if (outCurrHiddenTile.claimed)
        {
            continue;
        }
        outCurrHiddenTile.claimed = true;
        outCurrVisibleTile.ownedHiddenTiles.push_back(adjIndex);
    }
}

void MineSweeperSolutionFinder::getSolutions()
{
    for (int group = 0; group < m_groupedVisibleTiles.size(); group++)
    {
        SolutionSet& currSolutionSet = m_groupedIncompleteSolutions[group][0];
        for (HiddenTile& hiddenTileRef : currSolutionSet.hiddenTiles)
        {
            hiddenTileRef.claimed = false;
        }
        sortVisibleTilesByCombinationSize(group);
        getSolutionOfGroupReccursion(group, 0, 0);
    }
}

void MineSweeperSolutionFinder::getSolutionOfGroupReccursion(const uint16_t& group, uint16_t currVisibleTileIndex, const uint16_t currSolutionSetIndex)
{
    if (currVisibleTileIndex == m_groupedVisibleTiles[group].size()) // Base case
    {
        while (m_groupedCompleteSolutions.size() < group + 1)
        {
            m_groupedCompleteSolutions.push_back(std::vector<SolutionSet>());
        }
        m_groupedCompleteSolutions[group].push_back(m_groupedIncompleteSolutions[group][currSolutionSetIndex]);
        m_groupedIncompleteSolutions[group].pop_back();
        return;
    }
    VisibleTile& currVisibleTile = m_groupedVisibleTiles[group][currVisibleTileIndex];
    uint16_t bombCount = getEffectiveBombCount(currVisibleTile, m_groupedIncompleteSolutions[group][currSolutionSetIndex]);
    uint16_t claimedTilesSize = currVisibleTile.ownedHiddenTiles.size();
    if (claimedTilesSize < bombCount)
    {
        m_groupedIncompleteSolutions[group].pop_back();
        return;
    }
    std::vector<std::vector<uint16_t>>& combinations = getHardcodedCombinations(claimedTilesSize, bombCount);
    for (const std::vector<uint16_t>& combination : combinations)
    {
        std::vector<SolutionSet>& incompleteSolutions = m_groupedIncompleteSolutions[group];
        incompleteSolutions.push_back(m_groupedIncompleteSolutions[group][currSolutionSetIndex]);
        SolutionSet& copySolutionSet = incompleteSolutions.back();

        for (const uint16_t& combinationIndex : combination)
        {
            const uint16_t index = currVisibleTile.ownedHiddenTiles[combinationIndex];
            copySolutionSet.hiddenTiles[index].isBomb = true;
            copySolutionSet.bombCount++;
        }
        getSolutionOfGroupReccursion(group, currVisibleTileIndex + 1, m_groupedIncompleteSolutions[group].size() - 1);
    }
    if (m_groupedIncompleteSolutions[group].size() == 0)
    {
        throw std::runtime_error("Empty incomplete group end iteration " + std::to_string(currVisibleTileIndex));
    }
    m_groupedIncompleteSolutions[group].pop_back();
}

bool MineSweeperSolutionFinder::isValid(const uint16_t& group, const SolutionSet& currSolutionSet)
{
    for (const VisibleTile& visibleTileRef : m_groupedVisibleTiles[group])
    {
        uint16_t bombCount = 0;
        for (const uint16_t& adjIndex : visibleTileRef.adjHiddenTiles)
        {
            bombCount += currSolutionSet.hiddenTiles[adjIndex].isBomb;
        }
        if (bombCount != visibleTileRef.bombCount)
        {
            return false;
        }
    }
    return true;
}


bool MineSweeperSolutionFinder::canSurpassMaxBombs()
{
    uint16_t maxBombs = 0;
    for (const std::vector<SolutionSet>& solutionSets : m_groupedCompleteSolutions)
    {
        maxBombs += findMaxBombSet(solutionSets);
    }
    return maxBombs > m_maxBombs;
}

bool MineSweeperSolutionFinder::canUndercutMinBombs()
{
    uint16_t minBombs = 0;
    for (const std::vector<SolutionSet>& solutionSets : m_groupedCompleteSolutions)
    {
        minBombs += findMinBombSet(solutionSets);
    }
    return minBombs < m_minBombs;
}

uint16_t MineSweeperSolutionFinder::findMaxBombSet(const std::vector<SolutionSet>& solutionSets)
{
    uint16_t maxAmountOfBombs = 0;
    for (const SolutionSet& currSolutionSet : solutionSets)
    {
        if (currSolutionSet.bombCount > maxAmountOfBombs)
        {
            maxAmountOfBombs = currSolutionSet.bombCount;
        }
    }
    return maxAmountOfBombs;
}   

uint16_t MineSweeperSolutionFinder::findMinBombSet(const std::vector<SolutionSet>& solutionSets)
{
    uint16_t minBombCount = UINT16_MAX;
    for (const SolutionSet& currSolutionSet : solutionSets)
    {
        if (minBombCount > currSolutionSet.bombCount)
        {
            minBombCount = currSolutionSet.bombCount;
        }
    }
    return minBombCount;
}

void MineSweeperSolutionFinder::applyProbabilitiesCombined()
{
    for (std::vector<SolutionSet>& solutionSets : m_groupedCompleteSolutions)
    {
        for (HiddenTile& hiddenTile : solutionSets[0].hiddenTiles)
        {
            hiddenTile.originalTile->bombProbability = 0;
        }
    }
    m_groupedBombCountFrequencies.clear();
    for (uint16_t group = 0; group < m_groupedCompleteSolutions.size(); group++)
    {
        m_groupedBombCountFrequencies.push_back(std::vector<BombCountFrequency>());
        std::vector<BombCountFrequency>& bombCountFrequencies = m_groupedBombCountFrequencies.back();
        std::vector<SolutionSet>& solutionSets = m_groupedCompleteSolutions[group];
        for (SolutionSet& solutionSet : solutionSets)
        {
            bool foundBombCountFrequency = false;
            for (BombCountFrequency& bombCountFrequency : bombCountFrequencies)
            {
                if (solutionSet.bombCount == bombCountFrequency.bombCount)
                {
                    foundBombCountFrequency = true;
                    bombCountFrequency.frequencyInGroup++;
                    break;
                }
            }
            if (!foundBombCountFrequency)
            {
                bombCountFrequencies.push_back(BombCountFrequency(solutionSet.bombCount, 1));
            }
        }
    }

    uint32_t firstGroupSize = m_groupedBombCountFrequencies[0].size();
    uint64_t amountOfCombinations = 0;
    for (uint32_t index = 0; index < firstGroupSize; index++)
    {
        getBombCountFrequenciesReccursive(index, 0, 0, 1, amountOfCombinations);
    }
    m_averageBombsUsed = 0;
    for (uint16_t group = 0; group < m_groupedCompleteSolutions.size(); group++)
    {
        std::vector<BombCountFrequency>& bombCountFrequencies = m_groupedBombCountFrequencies[group];
        std::vector<SolutionSet>& solutionSets = m_groupedCompleteSolutions[group];
        for (SolutionSet& solutionSet : solutionSets)
        {
            for (BombCountFrequency& bombCountFrequency : bombCountFrequencies)
            {
                if (solutionSet.bombCount == bombCountFrequency.bombCount)
                {
                    double frequency = static_cast<double>(bombCountFrequency.frequencyInCombinations)
                                      /static_cast<double>(bombCountFrequency.frequencyInGroup);
                    for (HiddenTile& hiddenTile : solutionSet.hiddenTiles)
                    {
                        double frequencyOfBomb = hiddenTile.isBomb*frequency;
                        m_averageBombsUsed += frequencyOfBomb;
                        hiddenTile.originalTile->bombProbability += frequencyOfBomb;
                    }
                }
            }
        }
    }
    double totalProb = 0;
    m_averageBombsUsed /= static_cast<double>(amountOfCombinations);
    for (uint16_t group = 0; group < m_groupedCompleteSolutions.size(); group++)
    {
        SolutionSet& solutionSet = m_groupedCompleteSolutions[group][0];
        for (HiddenTile& hiddenTile : solutionSet.hiddenTiles)
        {
            hiddenTile.originalTile->bombProbability /= static_cast<double>(amountOfCombinations);
            totalProb += hiddenTile.originalTile->bombProbability;
        }
    }
}

uint32_t MineSweeperSolutionFinder::getBombCountFrequenciesReccursive(const uint32_t& index, const uint32_t& group, uint32_t bombCount, uint64_t combinationCount, uint64_t& totalCombinations)
{
    BombCountFrequency& currBombCountFrequency = m_groupedBombCountFrequencies[group][index];
    bombCount += currBombCountFrequency.bombCount;
    combinationCount *= currBombCountFrequency.frequencyInGroup;
    if (group + 1 == m_groupedBombCountFrequencies.size())
    {
        if (bombCount < m_minBombs)
        {
            return 0;
        }
        currBombCountFrequency.frequencyInCombinations += combinationCount;
        totalCombinations += combinationCount;
        return combinationCount;
    }
    uint32_t nextGroupSize = m_groupedBombCountFrequencies[group+1].size();
    uint32_t combinationSum = 0;
    for (uint32_t nextIndex = 0; nextIndex < nextGroupSize; nextIndex++)
    {
        if (bombCount > m_maxBombs)
        {
            return 0;
        }
        combinationSum += getBombCountFrequenciesReccursive(nextIndex, group+1, bombCount, combinationCount, totalCombinations);
    }
    currBombCountFrequency.frequencyInCombinations += combinationSum;
    return combinationSum;
}

void MineSweeperSolutionFinder::applyProbabilitiesSeperate()
{
    m_averageBombsUsed = 0;
    for (std::vector<SolutionSet>& solutionSets : m_groupedCompleteSolutions)
    {
        double bombsInGroup = 0;
        for (HiddenTile& hiddenTile : solutionSets[0].hiddenTiles)
        {
            hiddenTile.originalTile->bombProbability = 0;
        }

        for (SolutionSet& solutionSet : solutionSets)
        {
            bombsInGroup += static_cast<double>(solutionSet.bombCount);
            for (HiddenTile& hiddenTile : solutionSet.hiddenTiles)
            {
                hiddenTile.originalTile->bombProbability += hiddenTile.isBomb;
            }
        }

        if (solutionSets.size() != 0)
        {
            m_averageBombsUsed += (bombsInGroup/static_cast<double>(solutionSets.size()));
        }
        
        for (HiddenTile& hiddenTile : solutionSets[0].hiddenTiles)
        {
            hiddenTile.originalTile->bombProbability /= solutionSets.size();
        }  
    }
    uint16_t totalTiles = 0;
    for (std::vector<SolutionSet>& solutionSets : m_groupedCompleteSolutions)
    {
        totalTiles += solutionSets[0].hiddenTiles.size();
    }
}

inline uint16_t MineSweeperSolutionFinder::getEffectiveBombCount(VisibleTile& visibleTileRef, SolutionSet& solutionSetRef)
{
    uint16_t effectiveBombCount = visibleTileRef.bombCount;

    for (uint16_t adjIndex : visibleTileRef.adjHiddenTiles)
    {
        if (adjIndex >= solutionSetRef.hiddenTiles.size())
        {
            throw std::runtime_error("adjIndex too big!");
        }
        effectiveBombCount -= solutionSetRef.hiddenTiles[adjIndex].isBomb;
    }

    return effectiveBombCount;
}