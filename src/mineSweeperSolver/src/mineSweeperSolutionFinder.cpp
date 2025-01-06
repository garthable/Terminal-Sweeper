#include "mineSweeperSolutionFinder.hpp"
#include <iostream>
#include <algorithm>

inline uint8_t* getHardcodedCombinations(uint8_t r)
{
    static uint8_t hardCodedCombinations[] = {0, 1, 2, 3, 4, 5, 6, 7, 9, 1, 0, 2, 0, 2, 1, 3, 0, 3, 1, 3, 2, 4, 0, 4, 1, 4, 2, 4, 3, 5, 0, 5, 1, 5, 2, 5, 3, 5, 4, 6, 0, 6, 1, 6, 2, 6, 3, 6, 4, 6, 5, 7, 0, 7, 1, 7, 2, 7, 3, 7, 4, 7, 5, 7, 6, 9, 2, 1, 0, 3, 1, 0, 3, 2, 0, 3, 2, 1, 4, 1, 0, 4, 2, 0, 4, 2, 1, 4, 3, 0, 4, 3, 1, 4, 3, 2, 5, 1, 0, 5, 2, 0, 5, 2, 1, 5, 3, 0, 5, 3, 1, 5, 3, 2, 5, 4, 0, 5, 4, 1, 5, 4, 2, 5, 4, 3, 6, 1, 0, 6, 2, 0, 6, 2, 1, 6, 3, 0, 6, 3, 1, 6, 3, 2, 6, 4, 0, 6, 4, 1, 6, 4, 2, 6, 4, 3, 6, 5, 0, 6, 5, 1, 6, 5, 2, 6, 5, 3, 6, 5, 4, 7, 1, 0, 7, 2, 0, 7, 2, 1, 7, 3, 0, 7, 3, 1, 7, 3, 2, 7, 4, 0, 7, 4, 1, 7, 4, 2, 7, 4, 3, 7, 5, 0, 7, 5, 1, 7, 5, 2, 7, 5, 3, 7, 5, 4, 7, 6, 0, 7, 6, 1, 7, 6, 2, 7, 6, 3, 7, 6, 4, 7, 6, 5, 9, 3, 2, 1, 0, 4, 2, 1, 0, 4, 3, 1, 0, 4, 3, 2, 0, 4, 3, 2, 1, 5, 2, 1, 0, 5, 3, 1, 0, 5, 3, 2, 0, 5, 3, 2, 1, 5, 4, 1, 0, 5, 4, 2, 0, 5, 4, 2, 1, 5, 4, 3, 0, 5, 4, 3, 1, 5, 4, 3, 2, 6, 2, 1, 0, 6, 3, 1, 0, 6, 3, 2, 0, 6, 3, 2, 1, 6, 4, 1, 0, 6, 4, 2, 0, 6, 4, 2, 1, 6, 4, 3, 0, 6, 4, 3, 1, 6, 4, 3, 2, 6, 5, 1, 0, 6, 5, 2, 0, 6, 5, 2, 1, 6, 5, 3, 0, 6, 5, 3, 1, 6, 5, 3, 2, 6, 5, 4, 0, 6, 5, 4, 1, 6, 5, 4, 2, 6, 5, 4, 3, 7, 2, 1, 0, 7, 3, 1, 0, 7, 3, 2, 0, 7, 3, 2, 1, 7, 4, 1, 0, 7, 4, 2, 0, 7, 4, 2, 1, 7, 4, 3, 0, 7, 4, 3, 1, 7, 4, 3, 2, 7, 5, 1, 0, 7, 5, 2, 0, 7, 5, 2, 1, 7, 5, 3, 0, 7, 5, 3, 1, 7, 5, 3, 2, 7, 5, 4, 0, 7, 5, 4, 1, 7, 5, 4, 2, 7, 5, 4, 3, 7, 6, 1, 0, 7, 6, 2, 0, 7, 6, 2, 1, 7, 6, 3, 0, 7, 6, 3, 1, 7, 6, 3, 2, 7, 6, 4, 0, 7, 6, 4, 1, 7, 6, 4, 2, 7, 6, 4, 3, 7, 6, 5, 0, 7, 6, 5, 1, 7, 6, 5, 2, 7, 6, 5, 3, 7, 6, 5, 4, 9, 4, 3, 2, 1, 0, 5, 3, 2, 1, 0, 5, 4, 2, 1, 0, 5, 4, 3, 1, 0, 5, 4, 3, 2, 0, 5, 4, 3, 2, 1, 6, 3, 2, 1, 0, 6, 4, 2, 1, 0, 6, 4, 3, 1, 0, 6, 4, 3, 2, 0, 6, 4, 3, 2, 1, 6, 5, 2, 1, 0, 6, 5, 3, 1, 0, 6, 5, 3, 2, 0, 6, 5, 3, 2, 1, 6, 5, 4, 1, 0, 6, 5, 4, 2, 0, 6, 5, 4, 2, 1, 6, 5, 4, 3, 0, 6, 5, 4, 3, 1, 6, 5, 4, 3, 2, 7, 3, 2, 1, 0, 7, 4, 2, 1, 0, 7, 4, 3, 1, 0, 7, 4, 3, 2, 0, 7, 4, 3, 2, 1, 7, 5, 2, 1, 0, 7, 5, 3, 1, 0, 7, 5, 3, 2, 0, 7, 5, 3, 2, 1, 7, 5, 4, 1, 0, 7, 5, 4, 2, 0, 7, 5, 4, 2, 1, 7, 5, 4, 3, 0, 7, 5, 4, 3, 1, 7, 5, 4, 3, 2, 7, 6, 2, 1, 0, 7, 6, 3, 1, 0, 7, 6, 3, 2, 0, 7, 6, 3, 2, 1, 7, 6, 4, 1, 0, 7, 6, 4, 2, 0, 7, 6, 4, 2, 1, 7, 6, 4, 3, 0, 7, 6, 4, 3, 1, 7, 6, 4, 3, 2, 7, 6, 5, 1, 0, 7, 6, 5, 2, 0, 7, 6, 5, 2, 1, 7, 6, 5, 3, 0, 7, 6, 5, 3, 1, 7, 6, 5, 3, 2, 7, 6, 5, 4, 0, 7, 6, 5, 4, 1, 7, 6, 5, 4, 2, 7, 6, 5, 4, 3, 9, 5, 4, 3, 2, 1, 0, 6, 4, 3, 2, 1, 0, 6, 5, 3, 2, 1, 0, 6, 5, 4, 2, 1, 0, 6, 5, 4, 3, 1, 0, 6, 5, 4, 3, 2, 0, 6, 5, 4, 3, 2, 1, 7, 4, 3, 2, 1, 0, 7, 5, 3, 2, 1, 0, 7, 5, 4, 2, 1, 0, 7, 5, 4, 3, 1, 0, 7, 5, 4, 3, 2, 0, 7, 5, 4, 3, 2, 1, 7, 6, 3, 2, 1, 0, 7, 6, 4, 2, 1, 0, 7, 6, 4, 3, 1, 0, 7, 6, 4, 3, 2, 0, 7, 6, 4, 3, 2, 1, 7, 6, 5, 2, 1, 0, 7, 6, 5, 3, 1, 0, 7, 6, 5, 3, 2, 0, 7, 6, 5, 3, 2, 1, 7, 6, 5, 4, 1, 0, 7, 6, 5, 4, 2, 0, 7, 6, 5, 4, 2, 1, 7, 6, 5, 4, 3, 0, 7, 6, 5, 4, 3, 1, 7, 6, 5, 4, 3, 2, 9, 6, 5, 4, 3, 2, 1, 0, 7, 5, 4, 3, 2, 1, 0, 7, 6, 4, 3, 2, 1, 0, 7, 6, 5, 3, 2, 1, 0, 7, 6, 5, 4, 2, 1, 0, 7, 6, 5, 4, 3, 1, 0, 7, 6, 5, 4, 3, 2, 0, 7, 6, 5, 4, 3, 2, 1, 7, 6, 5, 4, 3, 2, 1, 0};
    static uint16_t rToIndex[] = {0, 0, 9, 66, 235, 516, 797, 966, 1022};
    return &hardCodedCombinations[rToIndex[r]];
}

inline uint8_t getHardcodedCombinationsSize(uint8_t n, uint8_t r)
{
    static uint8_t hardCodedSize[] = {1, 2, 1, 3, 3, 1, 4, 6, 4, 1, 5, 10, 10, 5, 1, 6, 15, 20, 15, 6, 1, 7, 21, 35, 35, 21, 7, 1, 8, 28, 56, 70, 56, 28, 8, 1};
    const uint8_t k = n*(n+1)/2 + r;
    return hardCodedSize[k];
}

MineSweeperSolutionFinder::MineSweeperSolutionFinder()
{
    m_averageBombsUsed = 0;
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
    
    int visibleTilesSize = visibleTiles.size();

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
    uint8_t n = 0;
    for (const uint16_t& adjIndex : currVisibleTile.adjHiddenTiles)
    {
        const HiddenTile& currHiddenTile = currSolutionSet.hiddenTiles[adjIndex];
        if (currHiddenTile.claimed)
        {
            continue;
        }
        n++;
    }
    uint8_t r = currVisibleTile.bombCount;
    if (n == 0)
    {
        return 0;
    }
    else if (r > n)
    {
        return 1;
    }
    return getHardcodedCombinationsSize(n, r);
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
    int16_t claimedTilesSize = currVisibleTile.ownedHiddenTiles.size();
    if (claimedTilesSize < bombCount)
    {
        m_groupedIncompleteSolutions[group].pop_back();
        return;
    }
    if (claimedTilesSize == 0 || bombCount == 0)
    {
        getSolutionOfGroupReccursion(group, currVisibleTileIndex + 1, m_groupedIncompleteSolutions[group].size() - 1);
        return;
    }
    uint8_t* combinations = getHardcodedCombinations(bombCount);
    while(true)
    {
        if (*combinations >= claimedTilesSize) 
        {
            break;
        }

        std::vector<SolutionSet>& incompleteSolutions = m_groupedIncompleteSolutions[group];
        incompleteSolutions.push_back(m_groupedIncompleteSolutions[group][currSolutionSetIndex]);
        SolutionSet& copySolutionSet = incompleteSolutions.back();

        for (uint8_t i = 0; i < bombCount; i++)
        {
            const uint16_t index = currVisibleTile.ownedHiddenTiles[*combinations];
            copySolutionSet.hiddenTiles[index].isBomb = true;
            copySolutionSet.bombCount++;
            combinations++;
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