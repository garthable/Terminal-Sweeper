#include "mine_sweeper.hpp"
#include "mine_sweeper_solver_functions.hpp"

namespace app
{
    /**
     * @brief Struct containing information about what the player has pressed with their keyboard and where the cursor is.
     * 
     */
    struct Input
    {
        /**
         * @brief Enum that tracks info about what the player has pressed.
         * 
         */
        enum Action
        {
            NONE   = 0,
            CLICK  = 1,
            FLAG   = 2,
            ASSIST = 3
        };
        /**
         * @brief Column that cursor is currently on
         * 
         */
        size_t col;
        /**
         * @brief Row that cursor is current on
         * 
         */
        size_t row;
        /**
         * @brief Action player has taken.
         * 
         */
        Action action;
    };

    /**
     * @brief Initializes game by setting up terminal such that its able to receive inputs.
     * 
     */
    void init();
    /**
     * @brief Tracks cursor and input of player.
     * 
     * @param rowMax Row bound of cursor [0, rowMax)
     * @param colMax Column bound of cursor [0, colMax)
     * @param prevInput Previous input performed by player.
     * @return Input 
     */
    Input pollInput(size_t rowMax, size_t colMax, Input prevInput);

    /**
     * @brief Asks player for preferred difficulty, then constructs Minesweeper board of said difficulty.
     * 
     * @return mswp::MineSweeper 
     */
    mswp::MineSweeper createBoard();

    /**
     * @brief Uses input to play game, returns true if game is still active, returns false if game is no longer active.
     * 
     * @param input Input retreived by pollInput.
     * @param[out] outBoard Minesweeper board output.
     * @return true 
     * @return false 
     */
    bool manageInput(Input input, mswp::MineSweeper& outBoard, bool& outAssist);

    /**
     * @brief Displays minesweeper board with cursor. 
     * 
     * @param input Last input taken by player. 
     * @param board Minesweeper board.
     */
    void displayBoard(const Input input, const mswp::MineSweeper& board, const bool assist, const slvr::ActionArray& reccomendedClicks, const slvr::ActionArray& reccomendedFlags);
    /**
     * @brief Prompts user if they want to reset to play again or if they want to quit.
     * 
     * @return true 
     * @return false 
     */
    bool shouldReset();
} // namespace app end
