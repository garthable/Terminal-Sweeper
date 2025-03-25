#include "mine_sweeper.hpp"

namespace app
{
    struct Input
    {
        enum Action
        {
            CLICK,
            FLAG,
            NONE
        };
        size_t col;
        size_t row;
        Action action;

        bool operator==(const Input& other) const
        {
            return col==other.col && row==other.row && action==other.action;
        }
    };

    enum class Difficulty : uint8_t
    {
        BEGINNER,
        INTERMEDIATE,
        EXPERT
    };

    Input pollInput(size_t rowMax, size_t colMax);
    mswp::MineSweeper createBoard();
    bool manageInput(Input input, mswp::MineSweeper& outBoard);
    void displayBoard(const Input input, const mswp::MineSweeper& board);
    bool shouldReset();
} // namespace app end