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

void applyProbabilities(const GroupedSolverTiles& groupedSolverTiles,
                        GroupedSolverTiles& outGroupedHiddenTiles,
                        uint16_t maxBombs, uint16_t minBombs, 
                        double& averageBombsUsedOut)
{
    if (groupedSolverTiles.size() != outGroupedHiddenTiles.size())
    {
        throw std::runtime_error("Visible and hidden are not the same size!");
    }
    static svec::SVector<std::vector<VisibleTile>, MAX_AMOUNT_OF_GROUPS> groupedVisibleTiles;
    static svec::SVector<SolutionSet, MAX_AMOUNT_OF_GROUPS> incompleteSolutions;
    static svec::SVector<std::vector<SolutionSet>, MAX_AMOUNT_OF_GROUPS> groupedCompleteSolutions;
    static svec::SVector<std::vector<BombCountFrequency>, MAX_AMOUNT_OF_GROUPS> groupedBombCountFrequencies;
    
    incompleteSolutions.clear();
    groupedVisibleTiles.clear();
    groupedCompleteSolutions.clear();
    groupedBombCountFrequencies.clear();

    double averageBombsUsed = 0;

    getHidden(outGroupedHiddenTiles, incompleteSolutions);
    getVisibles(groupedSolverTiles, incompleteSolutions, groupedVisibleTiles);

    getSolutions(incompleteSolutions, groupedVisibleTiles, groupedCompleteSolutions);

    if (canSurpassMaxBombs(maxBombs, groupedCompleteSolutions) || canUndercutMinBombs(minBombs, groupedCompleteSolutions))
    {
        applyProbabilitiesCombined(minBombs, maxBombs, groupedCompleteSolutions, groupedBombCountFrequencies, averageBombsUsed);
        return;
    }
    applyProbabilitiesSeperate(groupedCompleteSolutions, averageBombsUsed);
}

void getHidden(const GroupedSolverTiles& groupedHiddenTiles, svec::SVector<SolutionSet, MAX_AMOUNT_OF_GROUPS>& incompleteSolutionsOut)
{
    uint16_t groupSize = groupedHiddenTiles.size();
    for (int group = 0; group < groupSize; group++)
    {
        const auto& hiddenTiles = groupedHiddenTiles[group];
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

        incompleteSolutionsOut.pushBack(tempSolutionSet);
    }
}

void getVisibles(const GroupedSolverTiles& groupedVisibleTiles, const svec::SVector<SolutionSet, MAX_AMOUNT_OF_GROUPS>& incompleteSolutions, svec::SVector<std::vector<VisibleTile>, MAX_AMOUNT_OF_GROUPS>& groupedVisibleTilesOut)
{
    uint16_t groupSize = groupedVisibleTiles.size();
    for (int group = 0; group < groupSize; group++)
    {
        const auto& visibleTiles = groupedVisibleTiles[group];
        if (visibleTiles.size() == 0)
        {
            continue;
        }
        groupedVisibleTilesOut.emplaceBack();
        for (const SolverTile* visibleTilePtr : visibleTiles)
        {
            uint16_t effectiveBombCount = visibleTilePtr->adjBombsAmount;
            for (SolverTile* adjSolverTile : visibleTilePtr->adjSolverTiles)
            {
                effectiveBombCount -= (adjSolverTile->solverTileState == SolverTile::flagged);
            }
            groupedVisibleTilesOut[group].push_back(VisibleTile(effectiveBombCount));
            VisibleTile& mostRecentlyAddedVisibleTile = groupedVisibleTilesOut[group].back();

            for (SolverTile* adjHiddenTilePtr : visibleTilePtr->adjSolverTiles)
            {
                if (adjHiddenTilePtr->solverTileState != SolverTile::unknown) 
                {
                    continue;
                }
                
                int16_t hiddenTileIndex = searchHidden(adjHiddenTilePtr, group, incompleteSolutions);

                if (hiddenTileIndex == -1)
                {
                    continue;
                }
                mostRecentlyAddedVisibleTile.adjHiddenTiles.pushBack(hiddenTileIndex);
            }
        }
    }
}

inline int16_t searchHidden(const SolverTile* solverTile, const uint16_t& group, const svec::SVector<SolutionSet, MAX_AMOUNT_OF_GROUPS>& incompleteSolutions)
{
    const SolutionSet& incompleteSolution = incompleteSolutions[group];
    uint16_t incompleteSolutionsLength = incompleteSolution.hiddenTiles.size();
    for (int i = 0; i < incompleteSolutionsLength; i++)
    {
        const HiddenTile& hiddenTile = incompleteSolution.hiddenTiles[i];
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

void sortVisibleTilesByCombinationSize(const uint16_t& group, svec::SVector<SolutionSet, MAX_AMOUNT_OF_GROUPS>& incompleteSolutionsOut, svec::SVector<std::vector<VisibleTile>, MAX_AMOUNT_OF_GROUPS>& groupedVisibleTilesOut)
{
    SolutionSet& currSolutionSet = incompleteSolutionsOut[group];
    currSolutionSet.reset();
    std::vector<VisibleTile>& visibleTiles = groupedVisibleTilesOut[group];
    
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

uint16_t getCombinationSize(const VisibleTile& currVisibleTile, const SolutionSet& currSolutionSet)
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

void claimUnclaimedAdjTiles(VisibleTile& outCurrVisibleTile, SolutionSet& outCurrSolutionSet)
{
    for (const uint16_t& adjIndex : outCurrVisibleTile.adjHiddenTiles)
    {
        HiddenTile& outCurrHiddenTile = outCurrSolutionSet.hiddenTiles[adjIndex];
        if (outCurrHiddenTile.claimed)
        {
            continue;
        }
        outCurrHiddenTile.claimed = true;
        outCurrVisibleTile.ownedHiddenTiles.pushBack(adjIndex);
    }
}

void getSolutions(svec::SVector<SolutionSet, MAX_AMOUNT_OF_GROUPS>& incompleteSolutionsOut, svec::SVector<std::vector<VisibleTile>, MAX_AMOUNT_OF_GROUPS>& groupedVisibleTilesOut, svec::SVector<std::vector<SolutionSet>, MAX_AMOUNT_OF_GROUPS>& groupedCompleteSolutionsOut)
{
    for (int group = 0; group < groupedVisibleTilesOut.size(); group++)
    {
        SolutionSet& currSolutionSet = incompleteSolutionsOut[group];
        for (HiddenTile& hiddenTileRef : currSolutionSet.hiddenTiles)
        {
            hiddenTileRef.claimed = false;
        }
        sortVisibleTilesByCombinationSize(group, incompleteSolutionsOut, groupedVisibleTilesOut);
        getSolutionOfGroupReccursion(group, 0, currSolutionSet, groupedVisibleTilesOut, groupedCompleteSolutionsOut);
    }
}

void getSolutionOfGroupReccursion(const uint16_t& group, uint16_t currVisibleTileIndex, SolutionSet& solutionSet, svec::SVector<std::vector<VisibleTile>, MAX_AMOUNT_OF_GROUPS>& groupedVisibleTilesOut, svec::SVector<std::vector<SolutionSet>, MAX_AMOUNT_OF_GROUPS>& groupedCompleteSolutionsOut)
{
    if (currVisibleTileIndex == groupedVisibleTilesOut[group].size()) // Base case
    {
        while (groupedCompleteSolutionsOut.size() < group + 1)
        {
            groupedCompleteSolutionsOut.emplaceBack();
        }
        groupedCompleteSolutionsOut[group].push_back(solutionSet);
        return;
    }
    VisibleTile& currVisibleTile = groupedVisibleTilesOut[group][currVisibleTileIndex];
    uint16_t bombCount = getEffectiveBombCount(currVisibleTile, solutionSet);
    int16_t claimedTilesSize = currVisibleTile.ownedHiddenTiles.size();
    if (claimedTilesSize < bombCount)
    {
        return;
    }
    if (claimedTilesSize == 0 || bombCount == 0)
    {
        getSolutionOfGroupReccursion(group, currVisibleTileIndex + 1, solutionSet, groupedVisibleTilesOut, groupedCompleteSolutionsOut);
        return;
    }
    uint8_t* combinations = getHardcodedCombinations(bombCount);
    while(true)
    {
        if (*combinations >= claimedTilesSize) 
        {
            break;
        }

        uint8_t* combinationsStart = combinations;
        // Apply solution
        for (uint8_t i = 0; i < bombCount; i++)
        {
            const uint16_t index = currVisibleTile.ownedHiddenTiles[*combinations];
            solutionSet.hiddenTiles[index].isBomb = true;
            combinations++;
        }
        solutionSet.bombCount += bombCount;
        getSolutionOfGroupReccursion(group, currVisibleTileIndex + 1, solutionSet, groupedVisibleTilesOut, groupedCompleteSolutionsOut);
        // Remove solution
        for (uint8_t i = 0; i < bombCount; i++)
        {
            const uint16_t index = currVisibleTile.ownedHiddenTiles[*combinationsStart];
            solutionSet.hiddenTiles[index].isBomb = false;
            combinationsStart++;
        }
        solutionSet.bombCount -= bombCount;
    }
}

bool isValid(const uint16_t& group, const SolutionSet& currSolutionSet, svec::SVector<std::vector<VisibleTile>, MAX_AMOUNT_OF_GROUPS>& groupedVisibleTilesOut)
{
    for (const VisibleTile& visibleTileRef : groupedVisibleTilesOut[group])
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


bool canSurpassMaxBombs(uint16_t maxBombs, const svec::SVector<std::vector<SolutionSet>, MAX_AMOUNT_OF_GROUPS>& groupedCompleteSolutions)
{
    uint16_t bombs = 0;
    for (const std::vector<SolutionSet>& solutionSets : groupedCompleteSolutions)
    {
        bombs += findMaxBombSet(solutionSets);
    }
    return bombs > maxBombs;
}

bool canUndercutMinBombs(uint16_t minBombs, const svec::SVector<std::vector<SolutionSet>, MAX_AMOUNT_OF_GROUPS>& groupedCompleteSolutions)
{
    uint16_t bombs = 0;
    for (const std::vector<SolutionSet>& solutionSets : groupedCompleteSolutions)
    {
        bombs += findMinBombSet(solutionSets);
    }
    return bombs < minBombs;
}

uint16_t findMaxBombSet(const std::vector<SolutionSet>& solutionSets)
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

uint16_t findMinBombSet(const std::vector<SolutionSet>& solutionSets)
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

void resetSolutionSets(svec::SVector<std::vector<SolutionSet>, MAX_AMOUNT_OF_GROUPS>& groupedCompleteSolutionsOut)
{
    for (std::vector<SolutionSet>& solutionSets : groupedCompleteSolutionsOut)
    {
        for (HiddenTile& hiddenTile : solutionSets[0].hiddenTiles)
        {
            hiddenTile.originalTile->bombProbability = 0;
        }
    }
}

void applyProbabilitiesCombined(uint32_t minBombs, uint32_t maxBombs, svec::SVector<std::vector<SolutionSet>, MAX_AMOUNT_OF_GROUPS>& groupedCompleteSolutionsOut, svec::SVector<std::vector<BombCountFrequency>, MAX_AMOUNT_OF_GROUPS>& groupedBombCountFrequenciesOut, double& averageBombsUsedOut)
{
    resetSolutionSets(groupedCompleteSolutionsOut);
    groupedBombCountFrequenciesOut.clear();
    for (uint16_t group = 0; group < groupedCompleteSolutionsOut.size(); group++)
    {
        groupedBombCountFrequenciesOut.emplaceBack();
        std::vector<BombCountFrequency>& bombCountFrequencies = groupedBombCountFrequenciesOut.back();
        std::vector<SolutionSet>& solutionSets = groupedCompleteSolutionsOut[group];
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
    uint32_t firstGroupSize = groupedBombCountFrequenciesOut[0].size();
    uint64_t amountOfCombinations = 0;
    for (uint32_t index = 0; index < firstGroupSize; index++)
    {
        getBombCountFrequenciesReccursive(index, 0, 0, 1, minBombs, maxBombs, groupedBombCountFrequenciesOut, amountOfCombinations);
    }
    averageBombsUsedOut = 0;
    for (uint16_t group = 0; group < groupedCompleteSolutionsOut.size(); group++)
    {
        std::vector<BombCountFrequency>& bombCountFrequencies = groupedBombCountFrequenciesOut[group];
        std::vector<SolutionSet>& solutionSets = groupedCompleteSolutionsOut[group];
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
                        averageBombsUsedOut += frequencyOfBomb;
                        hiddenTile.originalTile->bombProbability += frequencyOfBomb;
                    }
                }
            }
        }
    }
    double totalProb = 0;
    averageBombsUsedOut /= static_cast<double>(amountOfCombinations);
    for (uint16_t group = 0; group < groupedCompleteSolutionsOut.size(); group++)
    {
        SolutionSet& solutionSet = groupedCompleteSolutionsOut[group][0];
        for (HiddenTile& hiddenTile : solutionSet.hiddenTiles)
        {
            hiddenTile.originalTile->bombProbability /= static_cast<double>(amountOfCombinations);
            totalProb += hiddenTile.originalTile->bombProbability;
        }
    }
}

uint32_t getBombCountFrequenciesReccursive(uint32_t index, uint32_t group, uint32_t bombCount, uint32_t minBombs, uint32_t maxBombs, uint64_t combinationCount, svec::SVector<std::vector<BombCountFrequency>, MAX_AMOUNT_OF_GROUPS>& groupedBombCountFrequencyOut, uint64_t& totalCombinationsOut)
{
    BombCountFrequency& currBombCountFrequency = groupedBombCountFrequencyOut[group][index];
    bombCount += currBombCountFrequency.bombCount;
    combinationCount *= currBombCountFrequency.frequencyInGroup;
    if (group + 1 == groupedBombCountFrequencyOut.size())
    {
        if (bombCount < minBombs)
        {
            return 0;
        }
        currBombCountFrequency.frequencyInCombinations += combinationCount;
        totalCombinationsOut += combinationCount;
        return combinationCount;
    }
    uint32_t nextGroupSize = groupedBombCountFrequencyOut[group+1].size();
    uint32_t combinationSum = 0;
    for (uint32_t nextIndex = 0; nextIndex < nextGroupSize; nextIndex++)
    {
        if (bombCount > maxBombs)
        {
            return 0;
        }
        combinationSum += getBombCountFrequenciesReccursive(nextIndex, group+1, bombCount, minBombs, maxBombs, combinationCount, groupedBombCountFrequencyOut, totalCombinationsOut);
    }
    currBombCountFrequency.frequencyInCombinations += combinationSum;
    return combinationSum;
}

void applyProbabilitiesSeperate(svec::SVector<std::vector<SolutionSet>, MAX_AMOUNT_OF_GROUPS>& groupedCompleteSolutionsOut, double& averageBombsUsedOut)
{
    averageBombsUsedOut = 0;
    for (std::vector<SolutionSet>& solutionSets : groupedCompleteSolutionsOut)
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
            averageBombsUsedOut += (bombsInGroup/static_cast<double>(solutionSets.size()));
        }
        
        for (HiddenTile& hiddenTile : solutionSets[0].hiddenTiles)
        {
            hiddenTile.originalTile->bombProbability /= solutionSets.size();
        }  
    }
    uint16_t totalTiles = 0;
    for (std::vector<SolutionSet>& solutionSets : groupedCompleteSolutionsOut)
    {
        totalTiles += solutionSets[0].hiddenTiles.size();
    }
}

inline uint16_t getEffectiveBombCount(VisibleTile& visibleTileRef, SolutionSet& solutionSetRef)
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