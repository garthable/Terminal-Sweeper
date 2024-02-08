#include "../include/mineSweeperSolutionFinder.h"

MineSweeperSolutionFinder::MineSweeperSolutionFinder()
{
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
                                uint16_t maxBombs)
{
    reset();
    getHidden(outGroupedHiddenTiles);
    getVisibles(groupedVisibleTiles);
    m_maxBombs = maxBombs;

    getSolutions();

    if (canSurpassMaxBombs())
    {
        applyProbabilitiesCombined(outGroupedHiddenTiles);
        return;
    }
    applyProbabilitiesSeperate(outGroupedHiddenTiles);
}

void MineSweeperSolutionFinder::reset()
{
    m_probabilities.clear();
    m_groupedVisibleTiles.clear();
    m_groupedIncompleteSolutions.clear();
    m_groupedCompleteSolutions.clear();
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
        SolutionSet tempSolutionSet = SolutionSet();

        for (SolverTile* hiddenTilePtr : hiddenTiles)
        {
            HiddenTile tempHiddenTile = HiddenTile(hiddenTilePtr, false);
            tempSolutionSet.hiddenTiles.push_back(tempHiddenTile);
        }

        m_groupedIncompleteSolutions.push_back(std::vector<SolutionSet>());
        m_groupedIncompleteSolutions[groupSize].push_back(tempSolutionSet);
    }
}

void MineSweeperSolutionFinder::getVisibles(const std::vector<std::vector<SolverTile*>>& groupedVisibleTiles) // MASSIVE readabilty issues here
{
    uint16_t groupSize = groupedVisibleTiles.size();
    for (int group = 0; group < groupSize; group++)
    {
        const std::vector<SolverTile*>& visibleTiles = groupedVisibleTiles[group];
        m_groupedVisibleTiles.push_back(std::vector<VisibleTile>());

        for (const SolverTile* visibleTilePtr : visibleTiles)
        {
            uint16_t effectiveBombCount = visibleTilePtr->adjBombsAmount;
            for (SolverTile* adjSolverTile : visibleTilePtr->adjSolverTiles)
            {
                effectiveBombCount -= adjSolverTile->solverTileState == flagged;
            }

            m_groupedVisibleTiles[group].push_back(VisibleTile(effectiveBombCount));

            for (SolverTile* adjHiddenTilePtr : visibleTilePtr->adjSolverTiles)
            {
                if (adjHiddenTilePtr->solverTileState != unknown) 
                {
                    continue;
                }
                
                int16_t hiddenTileIndex = searchHidden(adjHiddenTilePtr);

                if (hiddenTileIndex == -1)
                {
                    continue;
                }

                uint16_t tailIndex = m_groupedVisibleTiles[group].size() - 1;
                VisibleTile& visibleTileRef = m_groupedVisibleTiles[group][tailIndex];
                visibleTileRef.adjHiddenTiles.push_back(hiddenTileIndex);
            }
        }
    }
}

inline int16_t MineSweeperSolutionFinder::searchHidden(const SolverTile* _solverTile)
{
    for (std::vector<SolutionSet>& incompleteSolutions : m_groupedIncompleteSolutions)
    {
        uint16_t incompleteSolutionsLength = incompleteSolutions[0].hiddenTiles.size();
        for (int i = 0; i < incompleteSolutionsLength; i++)
        {
            HiddenTile& hiddenTileRef = incompleteSolutions[0].hiddenTiles[i];
            if (hiddenTileRef.originalTile == _solverTile)
            {
                return i;
            }
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
    VisibleTile& visibleTileA = visibleTiles[a];
    VisibleTile& visibleTileB = visibleTiles[b];

    visibleTiles[a] = visibleTileB;
    visibleTiles[b] = visibleTileA;
}

void MineSweeperSolutionFinder::sortVisibleTilesByCombinationSize(const uint16_t& group)
{
    SolutionSet& currSolutionSet = m_groupedIncompleteSolutions[group][0];
    std::vector<VisibleTile>& visibleTiles = m_groupedVisibleTiles[group];
    uint16_t visibleTilesSize = visibleTiles.size();
    for (int i = 0; i < visibleTilesSize; i++)
    {
        uint16_t minIndex = i;
        uint16_t minCombinationAmount = -1;
        for (int j = i; j < visibleTilesSize; j++)
        {
            VisibleTile currVisibleTile = visibleTiles[j];
            uint16_t currCombinationAmount = getCombinationSize(currVisibleTile, currSolutionSet);
            if (minCombinationAmount > currCombinationAmount)
            {
                minIndex = j;
                minCombinationAmount = currCombinationAmount;
            }
        }
        swap(visibleTiles, i, minIndex);
        claimUnclaimedAdjTiles(visibleTiles[minIndex], currSolutionSet);
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
    if (r > n)
    {
        r = n;
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
        uint16_t groupedVisibleTilesSize = m_groupedVisibleTiles[group].size();
        for (uint16_t currVisibleTileIndex = 0; currVisibleTileIndex < groupedVisibleTilesSize; currVisibleTileIndex++)
        {
            getSolutionOfGroupReccursion(group, currVisibleTileIndex, currSolutionSet);
        }
    }
}

void MineSweeperSolutionFinder::getSolutionOfGroupReccursion(const uint16_t& group, uint16_t currVisibleTileIndex, SolutionSet& currSolutionSet)
{
    if (currVisibleTileIndex == m_groupedVisibleTiles[group].size()) // Base case
    {
        if (!isValid(group, currSolutionSet))
        {
            return;
        }
        m_groupedCompleteSolutions[group].push_back(currSolutionSet);
        return;
    }
    VisibleTile& currVisibleTile = m_groupedVisibleTiles[group][currVisibleTileIndex];
    uint16_t bombCount = getEffectiveBombCount(currVisibleTile, currSolutionSet);
    uint16_t claimedTilesSize = currVisibleTile.ownedHiddenTiles.size();
    if (claimedTilesSize < bombCount)
    {
        return;
    }
    std::vector<std::vector<uint16_t>>& combinations = getHardcodedCombinations(claimedTilesSize, bombCount);

    for (std::vector<uint16_t>& combination : combinations)
    {
        m_groupedIncompleteSolutions[group].push_back(currSolutionSet);
        SolutionSet& copySolutionSet = m_groupedIncompleteSolutions[group][m_groupedIncompleteSolutions[group].size()];
        for (const uint16_t& index : combination)
        {
            copySolutionSet.hiddenTiles[index].isBomb = true;
            copySolutionSet.bombCount++;
        }
        getSolutionOfGroupReccursion(group, currVisibleTileIndex + 1, copySolutionSet);
    }
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

uint16_t findMaxBombSet(const std::vector<SolutionSet>& solutionSets)
{
    uint16_t maxBombCount = 0;
    for (const SolutionSet& currSolutionSet : solutionSets)
    {
        if (maxBombCount < currSolutionSet.bombCount)
        {
            maxBombCount = currSolutionSet.bombCount;
        }
    }
    return maxBombCount;
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

void MineSweeperSolutionFinder::applyProbabilitiesCombined(std::vector<std::vector<SolverTile*>>& outGroupedHiddenTiles)
{

}

void MineSweeperSolutionFinder::applyProbabilitiesSeperate(std::vector<std::vector<SolverTile*>>& outGroupedHiddenTiles)
{
    
}

inline uint16_t MineSweeperSolutionFinder::getEffectiveBombCount(VisibleTile& visibleTileRef, SolutionSet& solutionSetRef)
{
    uint16_t effectiveBombCount = 0;

    for (uint16_t adjIndex : visibleTileRef.adjHiddenTiles)
    {
        effectiveBombCount += solutionSetRef.hiddenTiles[adjIndex].isBomb;
    }

    return effectiveBombCount;
}