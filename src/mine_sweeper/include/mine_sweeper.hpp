#pragma once

#include <array>

#include "mine_sweeper_constants.hpp"
#include "mine_sweeper_tile.hpp"
#include "tile_string.hpp"

namespace mswp
{

// Typedefs used inorder to make it easier to change sizes safely.

typedef std::array<Tile, MSWP_MAX_TILES> Tiles;

typedef int16_t BoardSize;
typedef uint8_t BoardWidth;
typedef uint8_t BoardHeight;
typedef uint8_t BombCount;
typedef uint32_t BoardSeed;
typedef int8_t FlagsRemaining;

// These ones are used for readibility

typedef BoardSize BoardIndex;
typedef BoardWidth BoardXPos;
typedef BoardHeight BoardYPos;

typedef std::initializer_list<Tile> BoardInitList;

/**
 * @brief Stores everything relating to the minesweeper game including whether the game is won, lost, or in progress.
 * 
 */
class MineSweeper
{
public:
    /**
     * @brief Tracks whether the game just started, is in progress, is won, or is loss.
     * 
     */
    enum GameState : uint8_t 
    {
        START = 1,
        IN_PROGRESS = 2,
        WON = 4,
        LOST = 8
    };
    /**
     * @brief Construct a new Mine Sweeper object
     * 
     * @param width 
     * @param height 
     * @param bombCount 
     * @param boardSeed 
     */
    MineSweeper(BoardWidth width, BoardHeight height, BombCount bombCount, BoardSeed boardSeed);
    /**
     * @brief Construct a new Mine Sweeper object
     * 
     * @param width 
     * @param boardInitList 
     */
    MineSweeper(BoardWidth width, BoardInitList&& boardInitList);
    /**
     * @brief Construct a new Mine Sweeper object
     * 
     * @param width 
     * @param boardInitList 
     */
    MineSweeper(BoardWidth width, const BoardInitList& boardInitList);

    /**
     * @brief Clicks tile, revealing whats there. Returns true when game is won or lost.
     * 
     * @param x 
     * @param y 
     * @return true 
     * @return false 
     */
    bool click(BoardXPos x, BoardYPos y);
        /**
     * @brief Clicks tile, revealing whats there. Returns true when game is won or lost.
     * 
     * @param i
     * @return true 
     * @return false 
     */
    bool click(BoardIndex i);
    /**
     * @brief Flags tile, lowers flag count. Returns true when flag successfully placed. 
     * 
     * @param x 
     * @param y 
     * @return true 
     * @return false 
     */
    bool flag(BoardXPos x, BoardYPos y);
    /**
     * @brief Flags tile, lowers flag count. Returns true when flag successfully placed. 
     * 
     * @param i
     * @return true 
     * @return false 
     */
    bool flag(BoardIndex i);

    /**
     * @brief Tiles getter
     * 
     * @return const Tiles& 
     */
    const Tiles& tiles() const; 
    /**
     * @brief Tile String getter
     * 
     * @return const TileString& 
     */
    const TileString& tileString() const;
    /**
     * @brief Size getter
     * 
     * @return BoardSize 
     */
    BoardSize size() const;
    /**
     * @brief Remaining tiles getter
     * 
     * @return BoardSize 
     */
    BoardSize remainingTile() const;
    /**
     * @brief Width getter
     * 
     * @return BoardWidth 
     */
    BoardWidth width() const;
    /**
     * @brief Game state getter
     * 
     * @return GameState 
     */
    GameState gameState() const;
    /**
     * @brief Flags remaining getter
     * 
     * @return FlagsRemaining 
     */
    FlagsRemaining flagsRemaining() const;

    /**
     * @brief Resets the grid, generates new bombs.
     * 
     */
    void reset();

    /**
     * @brief Detects if board states are equal
     * 
     * @param other 
     * @return true 
     * @return false 
     */
    bool operator==(const MineSweeper& other) const;
    /**
     * @brief DetecTs if board states are equal
     * 
     * @param other 
     * @return true 
     * @return false 
     */
    bool operator==(const BoardInitList& other) const;

    /**
     * @brief Gets tile
     * 
     * @param index 
     * @return Tile 
     */
    inline Tile operator[](BoardIndex index) const
    {
        return m_Tiles[index];
    }
    /**
     * @brief Gets tile
     * 
     * @param x 
     * @param y 
     * @return Tile 
     */
    inline Tile operator()(BoardXPos x, BoardYPos y) const
    {
        return m_Tiles[static_cast<BoardIndex>(x) + static_cast<BoardIndex>(y)*static_cast<BoardIndex>(m_Width)];
    }
    /**
     * @brief Gets tile
     * 
     * @param index 
     * @return Tile& 
     */
    inline Tile& operator[](BoardIndex index)
    {
        return m_Tiles[index];
    }
    /**
     * @brief Gets tile
     * 
     * @param x 
     * @param y 
     * @return Tile& 
     */
    inline Tile& operator()(BoardXPos x, BoardYPos y)
    {
        return m_Tiles[x + y*m_Width];
    }
    
private:
    /**
     * @brief Size of board
     * 
     */
    const BoardSize m_Size;
    /**
     * @brief Width of board
     * 
     */
    const BoardWidth m_Width;
    /**
     * @brief Amount of bombs on board
     * 
     */
    const BombCount m_BombCount;
    /**
     * @brief Seed of Board
     * 
     */
    const BoardSeed m_BoardSeed;
    
    /**
     * @brief Number of tiles that haven't been revealed
     * 
     */
    BoardSize m_RemainingTiles;
    /**
     * @brief Stores whether game has just started, is in progress, has been lost, or has been won.
     * 
     */
    GameState m_GameState;
    /**
     * @brief Stores how many flags are left to be used.
     * 
     */
    FlagsRemaining m_FlagsRemaining;

    /**
     * @brief Array of Tiles
     * 
     */
    Tiles m_Tiles;
    /**
     * @brief Tile String for printing
     * 
     */
    TileString m_TileString;
};

/**
 * @brief Allows board to be printed out
 * 
 * @param out 
 * @param mineSweeper 
 * @return std::ostream& 
 */
std::ostream& operator<<(std::ostream &out, const MineSweeper& mineSweeper);

} // mswp end