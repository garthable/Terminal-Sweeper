#include "mine_sweeper.hpp"
#include "mine_sweeper_constants.hpp"
#include "util.hpp"

#include "app.hpp"

namespace app
{

void runInOpenGl()
{

}

void getWidthHeightBombCountTerminal(mswp::BoardWidth& outWidth, mswp::BoardHeight& outHeight, mswp::BombCount& outBombCount)
{
    while(true)
    {
        std::cout << "Select Difficulty: \
            \n\t1: Beginner \
            \n\t2: Intermediate \
            \n\t3: Expert\n";
        
        std::string input;
        getline(std::cin, input);
        uint8_t difficulty = std::stoi(input);

        switch (difficulty)
        {
        case 1:
            outWidth = MSWP_BEGINNER_WIDTH;
            outHeight = MSWP_BEGINNER_HEIGHT;
            outBombCount = MSWP_BEGINNER_BOMB_COUNT;
            return;
        case 2:
            outWidth = MSWP_INTERMEDIATE_WIDTH;
            outHeight = MSWP_INTERMEDIATE_HEIGHT;
            outBombCount = MSWP_INTERMEDIATE_BOMB_COUNT;
            return;
        case 3:
            outWidth = MSWP_EXPERT_WIDTH;
            outHeight = MSWP_EXPERT_HEIGHT;
            outBombCount = MSWP_EXPERT_BOMB_COUNT;
            return;
        
        default:
            break;
        }
        std::cout << "\"" << input << "\" is not a valid input!\n";
    }
}
struct Action
{
    enum Actions : uint8_t
    {
        FLAG,
        CLICK
    };
};
void getActionAndPositionTerminal(mswp::BoardWidth width, mswp::BoardHeight height, mswp::BoardXPos& xPos, mswp::BoardYPos& yPos, Action::Actions& action)
{

}
bool getShouldExitTerminal()
{

}
void runInTerminal()
{
    do
    {
        mswp::BoardWidth width;
        mswp::BoardHeight height;
        mswp::BombCount bombCount;
        getWidthHeightBombCountTerminal(width, height, bombCount);
    
        mswp::MineSweeper board(MSWP_EXPERT_WIDTH, MSWP_EXPERT_HEIGHT, MSWP_EXPERT_BOMB_COUNT, time(0));
    
        while(true)
        {
            std::cout << board;

            mswp::BoardXPos xPos;
            mswp::BoardYPos yPos;
            Action::Actions action;
            getActionAndPositionTerminal(width, height, xPos, yPos, action);

            if (action == Action::CLICK)
            {
                bool res = board.click(xPos, yPos);
                if (res)
                {
                    break;
                }
            }
            else
            {
                bool res = board.flag(xPos, yPos);
                if (res)
                {
                    break;
                }
            }
        }
    } while(getShouldExitTerminal());
}
void runBenchmark()
{

}

} // app end