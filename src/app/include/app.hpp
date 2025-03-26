#include "mine_sweeper.hpp"

namespace app
{
    struct Input
    {
        enum Action
        {
            NONE  = 0,
            CLICK = 1,
            FLAG  = 2,
            INIT  = 3
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

    void init();
    Input pollInput(size_t rowMax, size_t colMax, Input prevInput);
    mswp::MineSweeper createBoard();
    bool manageInput(Input input, mswp::MineSweeper& outBoard);
    void displayBoard(const Input input, const mswp::MineSweeper& board);
    bool shouldReset();
} // namespace app end