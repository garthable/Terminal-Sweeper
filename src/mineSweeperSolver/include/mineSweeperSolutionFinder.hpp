#ifndef MINESWEEPERSOLUTIONFINDER
#define MINESWEEPERSOLUTIONFINDER

#include <vector>
#include <iterator>
#include <stdint.h>
#include <string>
#include <iostream>

#include "solverTile.hpp"

struct HiddenTile
{
    SolverTile* originalTile;
    bool isBomb;
    bool claimed;

    HiddenTile(SolverTile* originalTile)
    {
        this->originalTile = originalTile;
        isBomb = false;
        claimed = false;
    }

    HiddenTile(SolverTile* originalTile, bool isBomb)
    {
        this->originalTile = originalTile;
        this->isBomb = isBomb;
        claimed = false;
    }

    HiddenTile(const HiddenTile& other)
    {
        this->originalTile = other.originalTile;
        this->claimed = other.claimed;
        this->isBomb = other.isBomb;
    }
};

struct VisibleTile
{
    svec::SVector<uint16_t, 8> adjHiddenTiles;
    svec::SVector<uint16_t, 8> ownedHiddenTiles;
    uint16_t bombCount;

    VisibleTile()
    {

    }

    VisibleTile(uint16_t bombCount)
    {
        this->bombCount = bombCount;
    }

    VisibleTile(const VisibleTile& other)
    {
        this->bombCount = other.bombCount;
        this->ownedHiddenTiles = other.ownedHiddenTiles;
        this->adjHiddenTiles = other.adjHiddenTiles;
    }
};

struct SolutionSet
{
    std::vector<HiddenTile> hiddenTiles;
    uint16_t bombCount;

    void reset()
    {
        for (HiddenTile& hiddenTileRef : hiddenTiles)
        {
            hiddenTileRef.isBomb = false;
        }
    }

    SolutionSet()
    {
        bombCount = 0;
    }
    SolutionSet(const SolutionSet& other)
    {
        this->bombCount = other.bombCount;
        this->hiddenTiles = other.hiddenTiles;
    }
};

struct BombCountFrequency
{
    uint32_t bombCount;
    uint32_t frequencyInGroup;
    uint64_t frequencyInCombinations;
    BombCountFrequency(uint32_t bombCount, uint64_t frequencyInGroup)
    {
        this->bombCount = bombCount;
        this->frequencyInGroup = frequencyInGroup;
        frequencyInCombinations = 0;
    }
};

// Parameters:
// The size of the adjacents list
// The number of bombs in the adjacents list
//
// Returns:
// Index of set of combinations in hardCodedCombinations
inline uint8_t* getHardcodedCombinations(uint8_t r);

// Parameters:
// The size of the adjacents list
// The number of bombs in the adjacents list
//
// Returns:
// Index of set of combinations in hardCodedCombinations
inline uint8_t getHardcodedCombinationsSize(uint8_t n, uint8_t r);

// MineSweeperSolutionFinder();

// Parameters:
// Grouped Visible Tiles
// Out grouped Hidden Tiles
// Max amount of bombs
//
// Purpose:
// Gathers data for future calculations, applies probability of being a bomb to all hiddenTiles passed.
void applyProbabilities(const GroupedSolverTiles& groupedVisibleTiles,
                        GroupedSolverTiles& outGroupedHiddenTiles,
                        uint16_t maxBombs, uint16_t minBombs, 
                        double& averageBombsUsedOut);
        
// Parameters:
// Grouped hidden tiles
// 
// Purpose:
// Converts hidden tiles into format used by class
void getHidden(const GroupedSolverTiles& groupedHiddenTiles, svec::SVector<SolutionSet, MAX_AMOUNT_OF_GROUPS>& incompleteSolutionsOut);

// Parameters:
// Grouped visible tiles
// 
// Purpose:
// Converts visible tiles into format used by class
void getVisibles(const GroupedSolverTiles& groupedVisibleTiles, const svec::SVector<SolutionSet, MAX_AMOUNT_OF_GROUPS>& incompleteSolutions, svec::SVector<std::vector<VisibleTile>, MAX_AMOUNT_OF_GROUPS>& groupedVisibleTilesOut);

inline int16_t searchHidden(const SolverTile* solverTile, const uint16_t& group, const svec::SVector<SolutionSet, MAX_AMOUNT_OF_GROUPS>& incompleteSolutions);

// Parameters:
// List of visibleTiles:
//
// Purpose:
// Sorts tiles in order from least to greatest combinations inorder to optimize the program.
void sortVisibleTilesByCombinationSize(const uint16_t& group, svec::SVector<SolutionSet, MAX_AMOUNT_OF_GROUPS>& incompleteSolutionsOut, svec::SVector<std::vector<VisibleTile>, MAX_AMOUNT_OF_GROUPS>& groupedVisibleTilesOut);

// Parameters:
// Out visible tile
// Out solution set
//
// Purpose:
// Any tile that has not been claimed by some other visible tile will be claimed by this one
void claimUnclaimedAdjTiles(VisibleTile& outCurrVisibleTile, SolutionSet& outCurrSolutionSet);

// Parameters:
// Visible Tile
// Solution Set
//
// Returns:
// The combination size of the number of ways the inputed visible tile can arrange its adjacent bombs
uint16_t getCombinationSize(const VisibleTile& currVisibleTile, const SolutionSet& currSolutionSet);

// Purpose:
// Runs getSolutionOfGroupReccursion for each group.
void getSolutions(svec::SVector<SolutionSet, MAX_AMOUNT_OF_GROUPS>& incompleteSolutionsOut, svec::SVector<std::vector<VisibleTile>, MAX_AMOUNT_OF_GROUPS>& groupedVisibleTilesOut, svec::SVector<std::vector<SolutionSet>, MAX_AMOUNT_OF_GROUPS>& groupedCompleteSolutionsOut);

// Parameters:
// Group number
// Current visibleTileIndex
// Current solution set
//
// Purpose:
// Finds all possible solutions.
void getSolutionOfGroupReccursion(const uint16_t& group, uint16_t currVisibleTileIndex, SolutionSet& solutionSet, svec::SVector<std::vector<VisibleTile>, MAX_AMOUNT_OF_GROUPS>& groupedVisibleTilesOut, svec::SVector<std::vector<SolutionSet>, MAX_AMOUNT_OF_GROUPS>& groupedCompleteSolutionsOut);

// Parameters:
// Group number
// Current solution set
//
// Returns:
// If this is a valid configuration.
bool isValid(const uint16_t& group, const SolutionSet& currSolutionSet, svec::SVector<std::vector<VisibleTile>, MAX_AMOUNT_OF_GROUPS>& groupedVisibleTilesOut);

// Parameters:
// Vector of solution sets
//
// Returns:
// The number of bombs in the solutionSet with the highest amount of bombs.
uint16_t findMaxBombSet(const std::vector<SolutionSet>& solutionSets);

// Parameters:
// Vector of solution sets
//
// Returns:
// The number of bombs in the solutionSet with the lowest amount of bombs.
uint16_t findMinBombSet(const std::vector<SolutionSet>& solutionSets);

// Returns:
// Whether its possible to exceed to max bomb count specified.
bool canSurpassMaxBombs(uint16_t maxBombs, const svec::SVector<std::vector<SolutionSet>, MAX_AMOUNT_OF_GROUPS>& groupedCompleteSolutions);

// Returns:
// Whether its possible to go below the min bomb count specified.
bool canUndercutMinBombs();

// Purpose:
// If its possible to surpass the max bomb count combine all solution sets such that they dont surpass the
// max bomb count and use that to get probability. After this apply this to all tiles.
void applyProbabilitiesCombined();

// Parameters:
// Current index of SizeFrequencies
// Current group of SizeFrequencies
//
// Returns:
// Frequency for valid bombCout combinations.
//
// Purpose:
// Find how many different valid ways each bombCount of solutionGroup can be combined.
uint32_t getBombCountFrequenciesReccursive(const uint32_t& index, const uint32_t& group, uint32_t bombCount, uint64_t combinationCount, uint64_t& totalCombinations);

// Purpose:
// Find the probabilty that each tile is a bomb based off the solutions set
void applyProbabilitiesSeperate();

// Parameters:
// Visible tile reference
// Solution set reference
//
// Returns:
// The bombcount - the amount of bombs in domain.
inline uint16_t getEffectiveBombCount(VisibleTile& visibleTileRef, SolutionSet& solutionSetRef);

#endif
