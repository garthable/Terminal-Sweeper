#include <vector>
#include <iterator>
#include <stdint.h>
#include <string>

#ifndef MINESWEEPERSOLUTIONFINDER
#define MINESWEEPERSOLUTIONFINDER

#include "mineSweeperSolver.h"

struct solverTile;

struct hiddenTile
{
    solverTile* originalTile;
    bool isBomb;
    bool claimed;

    hiddenTile(solverTile* originalTile)
    {
        this->originalTile = originalTile;
        isBomb = false;
        claimed = false;
    }

    hiddenTile(solverTile* originalTile, bool isBomb)
    {
        this->originalTile = originalTile;
        this->isBomb = isBomb;
        claimed = false;
    }
};

struct visibleTile
{
    std::vector<uint16_t> adjHiddenTiles;
    std::vector<uint16_t> ownedHiddenTiles;
    uint16_t bombCount;

    visibleTile(uint16_t bombCount)
    {
        this->bombCount = bombCount;
    }
};

struct solutionSet
{
    std::vector<hiddenTile> hiddenTiles;
    uint16_t bombCount;

    void reset()
    {
        for (hiddenTile& hiddenTileRef : hiddenTiles)
        {
            hiddenTileRef.isBomb = false;
        }
    }

    solutionSet()
    {
        bombCount = 0;
    }
};

class mineSweeperSolutionFinder
{
    public:
        mineSweeperSolutionFinder();

        // Parameters:
        // Grouped Visible Tiles
        // Out grouped Hidden Tiles
        // Max amount of bombs
        //
        // Purpose:
        // Gathers data for future calculations, applies probability of being a bomb to all hiddenTiles passed.
        void applyProbabilities(const std::vector<std::vector<solverTile*>>& groupedVisibleTiles,
                                std::vector<std::vector<solverTile*>>& outGroupedHiddenTiles,
                                uint16_t maxBombs);
        
        // Purpose:
        // Resets all member values.
        void reset();
    private:
        // Parameters:
        // Grouped hidden tiles
        // 
        // Purpose:
        // Converts hidden tiles into format used by class
        void getHidden(const std::vector<std::vector<solverTile*>>& groupedHiddenTiles);

        // Parameters:
        // Grouped visible tiles
        // 
        // Purpose:
        // Converts visible tiles into format used by class
        void getVisibles(const std::vector<std::vector<solverTile*>>& groupedVisibleTiles);

        inline int16_t searchHidden(const solverTile* _solverTile);

        // Parameters:
        // The size of the adjacents list
        // The number of bombs in the adjacents list
        //
        // Returns:
        // Index of set of combinations in hardCodedCombinations
        inline std::vector<std::vector<uint16_t>>& getHardcodedCombinations(uint16_t n, uint16_t r);

        // Parameters:
        // List of visibleTiles:
        //
        // Purpose:
        // Sorts tiles in order from least to greatest combinations inorder to optimize the program.
        void sortVisibleTilesByCombinationSize(const uint16_t& group);

        void claimUnclaimedAdjTiles(visibleTile& currVisibleTile, solutionSet& currSolutionSet);

        uint16_t getCombinationSize(visibleTile& currVisibleTile, solutionSet& currSolutionSet);

        // Purpose:
        // Runs getSolutionOfGroupReccursion for each group.
        void getSolutions();

        // Parameters:
        // Group number
        // Current visibleTileIndex
        // Current solution set
        //
        // Purpose:
        // Finds all possible solutions.
        void getSolutionOfGroupReccursion(const uint16_t& group, uint16_t currVisibleTileIndex, solutionSet& currSolutionSet);

        // Parameters:
        // Group number
        // Current solution set
        //
        // Returns:
        // If this is a valid configuration.
        bool isValid(const uint16_t& group, const solutionSet& currSolutionSet);

        uint16_t findMaxBombSet(const std::vector<solutionSet>& solutionSets);

        // Returns:
        // Whether its possible to exceed to max bomb count specified.
        bool canSurpassMaxBombs();

        // Parameters:
        // Out to grouped hiddenTiles
        //
        // Purpose:
        // If its possible to surpass the max bomb count combine all solution sets such that they dont surpass the
        // max bomb count and use that to get probability. After this apply this to all tiles.
        void applyProbabilitiesCombined(std::vector<std::vector<solverTile*>>& outGroupedHiddenTiles);

        // Parameters:
        // Out to grouped hiddenTiles
        //
        // Purpose:
        // Find the probabilty that each tile is a bomb based off the solutions set
        void applyProbabilitiesSeperate(std::vector<std::vector<solverTile*>>& outGroupedHiddenTiles);

        // Parameters:
        // Visible tile reference
        // Solution set reference
        //
        // Returns:
        // The bombcount - the amount of bombs in domain.
        inline uint16_t getEffectiveBombCount(visibleTile& visibleTileRef, solutionSet& solutionSetRef);
    private:
        enum solverTileStates
        {
            unknown = 0u,
            visible = 1u,
            flagged = 2u,
            clicked = 4u
        };
        uint16_t m_maxBombs;

        std::vector<std::vector<visibleTile>> m_groupedVisibleTiles; // Redo with singular vector OR figure out how to implement without deleting less vectors
        std::vector<std::vector<solutionSet>> m_groupedIncompleteSolutions; // Redo with singular vector
        std::vector<std::vector<solutionSet>> m_groupedCompleteSolutions;
        std::vector<float> m_probabilities;

        std::vector<std::vector<std::vector<uint16_t>>> m_hardcodedCombinations;
};

#endif
