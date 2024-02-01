#include <stdint.h>
#include <string>
#include <array>
#include <vector>

#ifndef MINESWEEPERSOLVER
#define MINESWEEPERSOLVER

#include "mineSweeperSolutionFinder.h"

struct coordinate
{
    uint16_t x;
    uint16_t y;

    coordinate(uint16_t _x, uint16_t _y)
    {
        x = _x;
        y = _y;
    }
};

// Runs the mine sweeper solving algorithm
// Optimized to be able to solve multiple games back to back of the same difficulty running.
// Receives input of map via update
// Gives output of next click via getReccomendedClick
class mineSweeperSolver
{
    public:
        // Parameters:
        // The length of the mine sweeper map
        // The height of the mine sweeper map
        // The number of bombs in the mine sweeper map
        mineSweeperSolver(const uint16_t& sizeX, const uint16_t& sizeY, const uint16_t& bombCount);

        // Parameters:
        // The current mine sweeper map output
        //
        // Purpose:
        // Runs logic to find probability of nodes
        void update(const std::string& mineSweeperMap);

        // Returns:
        // Returns what the solver sees for bug testing.
        std::string getSolverMap();

        // Purpose:
        // Resets solver for new game
        void reset();

        // Returns:
        // A location with one of the lowest probabilities of being a bomb
        coordinate getReccomendedClick();

        // Returns:
        // A location that has a 100% chance of being a bomb
        coordinate getReccomendedFlag();

    private:
        // Parameters:
        // The x coordinate of a potential solver tile location
        // The y coordinate of a potential solver tile location
        //
        // Returns:
        // A pointer to the solver tile with coordinates (x, y)
        // If a solver tile with said coords does not exist it returns the null pointer
        inline solverTile* searchSolverTile(const uint16_t& x, const uint16_t& y);

        // Parameters:
        // The index of a solverTile
        //
        // Returns:
        // A pointer to the solver tile with coordinates (x, y)
        // If a solver tile with said coords does not exist it returns the null pointer
        inline solverTile* searchSolverTile(const uint16_t& index);

        // Parameters:
        // Pointer to solver tile
        //
        // Returns:
        // Index of solverTile in solverTiles
        inline uint16_t getSolverTileIndex(solverTile* solverTilePtr);

        // Returns:
        // Whether reccomendedFlags and reccomendedClicks are empty
        inline bool hasReccomendedSolverTiles();

        // Parameters:
        // out Solvertile to be flagged
        //
        // Outs:
        // Sets inputed tile to a flag and adds it to reccomended flags
        inline void flagSolverTile(solverTile& solverTileOut);

        // Parameters:
        // out Solvertile to be clicked
        //
        // Outs:
        // Sets inputed tile to clicked and adds it to reccomended clicks
        inline void clickSolverTile(solverTile& solverTileOut);

        // Purpose:
        // Generates the tiles and adds the pointers between them.
        void generateSolverTiles();

        // Parameters:
        // The current mine sweeper map output
        //
        // Purpose:
        // Parses input from mineSweeper class to derive current game state
        void readMineMap(const std::string& mineSweeperMap);

        // Parameters:
        // solverTilePtr
        //
        // Returns:
        // Number of non flagged bombs
        inline uint16_t getEffectiveBombCount(const solverTile& solverTilePtr);

        // Parameters:
        // solverTilePtr
        //
        // Returns:
        // Number of unkown adjacent tiles
        inline uint16_t getAdjUnknownCount(const solverTile& solverTilePtr);

        // Purpose:
        // Preforms checks that are in p time.
        void fastBombFinder();

        // Parameters:
        // Two solver tiles
        //
        // Returns:
        // The number of common unknown adjacents
        uint16_t getIntersectionSizeBetweenTileUnknownAdjs(const solverTile* solverTilePtrA, const solverTile* solverTilePtrB);

        // Parameters:
        // Two solver tiles
        //
        // Purpose:
        // Clicks all unknown tiles of A that are not shared by B
        void clickTilesInAMinusBSet(solverTile* solverTilePtrA, solverTile* solverTilePtrB);

        // Parameters:
        // Two solver tiles
        //
        // Purpose:
        // Flags all unknown tiles of A that are not shared by B
        void flagTilesInAMinusBSet(solverTile* solverTilePtrA, solverTile* solverTilePtrB);

        // Parameters:
        // Two solver tiles
        //
        // Purpose:
        // Flags all unknown tiles of A that are shared by B
        void flagTilesInAIntersectBSet(solverTile* solverTilePtrA, solverTile* solverTilePtrB);

        // Purpose:
        // Finds 1 2 x pattern
        // Finds 1 1 x pattern
        void patternBombFinder();

        // Purpose:
        // Reduces the amount of tiles in getAllSolutions function which is NP by grouping tiles.
        void groupTiles();

        // Parameters:
        // Next solvertile
        // 
        // Purpose:
        // Preforms DFS to group tiles together
        void groupTilesReccursion(solverTile* currTilePtr, const uint16_t& group);

        // Parameters:
        // Two unknown/not visible tiles
        //
        // Purpose:
        // Makes sure both tiles have a numbered tile in common.
        bool shareSameNumbered(const solverTile* tileA, const solverTile* tileB);

        // Purpose:
        // Gets every possible arrangement of mines.
        void getAllSolutions();

        // Purpose:
        // Calculates probability of tile being a bomb, and probability of bomb having an n number of adjacent bombs.
        void calculateProbabilities();
    private:
        enum solverTileStates
        {
            unknown = 0u,
            visible = 1u,
            flagged = 2u,
            clicked = 4u
        };

        uint16_t m_sizeX;
        uint16_t m_sizeY;
        uint16_t m_bombCount;

        std::vector<solverTile> m_solverTiles;

        std::vector<solverTile*> m_reccomendedClicks;
        std::vector<solverTile*> m_reccomendedFlags;

        std::vector<std::vector<solverTile*>> m_visibleGroupedSolverTiles;
        std::vector<std::vector<solverTile*>> m_unknownGroupedSolverTiles;

        std::vector<uint16_t> m_bombCounts;

        std::vector<uint16_t> m_tempIds;
};

#endif