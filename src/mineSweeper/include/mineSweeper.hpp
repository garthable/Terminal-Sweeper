#ifndef MINESWEEPER
#define MINESWEEPER

#include <vector>
#include <string>
#include <cstdint>

#include "sVector.hpp"

#define MAX_X_SIZE 30
#define MAX_Y_SIZE 18
#define MAX_BOMB_COUNT 99
#define MAX_TILE_COUNT MAX_X_SIZE*MAX_Y_SIZE

struct Tile
{
    svec::SVector<Tile*, 8> adjTiles;

    uint16_t x;
    uint16_t y;

    uint8_t adjBombs;
    uint8_t tileState;

    Tile()
    {

    }

    Tile(Tile&& tile) :
        adjTiles{std::move(tile.adjTiles)},
        x{std::move(tile.x)},
        y{std::move(tile.y)},
        adjBombs{std::move(tile.adjBombs)},
        tileState{std::move(tile.tileState)}
    {

    }

    Tile(const uint16_t& _x, const uint16_t& _y)
    {
        x = _x;
        y = _y;

        adjBombs = 0u;
        tileState = 0u;
    }

    void operator=(const Tile& tile)
    {
        adjTiles = tile.adjTiles;
        x = tile.x;
        y = tile.y;
        adjBombs = tile.adjBombs;
        tileState = tile.tileState;
    }
};

// Runs the actual game of minesweeper.
// Optimized to run different seeds of the same difficulty
// Accepts inputs from player via 'clickTile(x, y)' and 'flagTile(x, y)'
// The outputs are given from 'getMineSweeperMap()' and 'getFlagsRemaining()'
class MineSweeper
{
    public:
        // Parameters:
        // The length of the mine sweeper map
        // The height of the mine sweeper map
        // The number of bombs in the mine sweeper map
        MineSweeper(const uint16_t& sizeX, const uint16_t& sizeY, const uint16_t& bombCount);

        // Parameters:
        // Filename of test map
        //
        // Purpose:
        // Used in testing.
        MineSweeper(const std::string& fileName);

        // Parameters:
        // The x coordinate of the first click,
        // The y coordinate of the first click,
        // The chebyshev radius around the first click that is guaranteed to not have a bomb next to it,
        // The number of bombs to be spawned,
        // The seed which determines the layout of bombs.
        //
        // Purpose:
        // Sets all tiles in m_tiles to not be bombs and then sets a random selection of n tiles to be bombs.
        void generateBombs(const uint16_t& innitClickX, const uint16_t& innitClickY, const unsigned int& seed);

        // Parameters:
        // Name of file countaining data for function to generate map off of.
        //
        // Purpose:
        // Generates customly made map for testing.
        void generateTilesFromMap(std::string fileName);

        // Parameters:
        // The x coordinate of the click
        // The y coordinate of the click
        //
        // Purpose:
        // Clicks a tile, if the tile is a bomb it explodes ending the game, if it is not a bomb it reveals the tile.
        void clickTile(const uint16_t& clickX, const uint16_t& clickY);

        // Parameters:
        // The x coordinate of the flag
        // The y coordinate of the flag
        //
        // Purpose:
        // Flags a tile as a potential bomb. If the tile is already flagged it unflags the tile.
        void flagTile(const uint16_t& flagX, const uint16_t& flagY);

        // Returns:
        // True if the game is won
        // False if the game has not been won
        bool isWon();

        // Returns:
        // True if the game is lost
        // False if the game has not been lost
        bool isLost();

        // Returns:
        // The data about the current state of the minesweeper game. 
        // Below is a ledger showing how the data about the game is shown.
        // Tile that has not been revealed: '#'
        // Tile that has not been revealed and is flagged: '@'
        // Tile with no adjacent bombs: ' '
        // Tile with n amount of adjacent bombs: 'n'
        // Tile that is a bomb: 'X'
        //
        // Purpose:
        // Used by the App to display the current grid and used by the solver to read what the current grid is.
        std::string getOutputMineSweeperMap();

        // Returns:
        // The number of flags remaining
        //
        // Purpose:
        // Used by the app inform the player of how many flags have been used.
        int16_t getFlagsRemaining();

        // Returns:
        // m_sizeX
        //
        // Purpose:
        // Used by testing
        uint16_t getSizeX();
        
        // Returns:
        // m_sizeY
        //
        // Purpose:
        // Used by testing
        uint16_t getSizeY();

        // Returns:
        // Bombcount
        //
        // Purpose:
        // Used by testing
        uint16_t getBombCount();

    private:
        // Parameters:
        // The x coordinate of a potential location of a tile
        // The y coordinate of a potential location of a tile
        //
        // Returns:
        // A pointer to the tile with coordinates (x, y)
        // If a tile with said coords does not exist it returns the null pointer
        inline Tile* searchTile(uint16_t x, uint16_t y);

        // Parameters:
        // x coordinate of char in outputMineSweeperMap
        // y coordinate of char in outputMineSweeperMap
        // Char to overwrite prior char
        inline void setOutputMineSweeperMapChar(const uint16_t& x, const uint16_t& y, const char& newChar);

        // Purpose:
        // A function called at construction that generates the grid of tiles used by the mineMap.
        void generateMap();

        // Purpose:
        // Initializes output map to all hidden
        void initializeOutputMineSweeperMap();

        // Purpose:
        // Sets all of the tiles in m_tiles to not be bombs, to be hidden, and to have no adjacent bombs. Used exclusivley by generateBombs.
        void reset();

        // Parameters:
        // Some starting tile
        //
        // Purpose:
        // A reccursive function used to reveal all tiles with zero adjacent bombs and their surroundings. Used exclusivley by the click function.
        void cascadeReveal(Tile* curr);

    private:
        enum tileStates
        {
            visible = 1u,
            flagged = 2u,
            bomb = 4u
        };

        svec::SVector<Tile, MAX_TILE_COUNT> m_tiles;
        std::string m_outputMineSweeperMap;
        uint16_t m_sizeX;
        uint16_t m_sizeY;
        uint16_t m_bombCount;
        int16_t m_flagsRemaining;

        int16_t m_nonBombTilesRemaining; // Used by isWon function to see if the tiles remaining is equal to 
        bool m_isLost;
};

#endif