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
    while (true)
    {
        std::cout << "Enter Action and Position: (c/f) <row> <col>\n";
        std::string line;

        getline(std::cin, line);
        if (line.size() != 5)
        {
            std::cout << "Input is incorrect size!\n";
        }

        xPos = util::letterToUI8(line[4]);
        if (xPos == 255)
        {
            std::cout << "\'" << line[4] << "\' is invalid!\n";
        }
        if (xPos >= width)
        {
            std::cout << "\'" << static_cast<int>(xPos) << "\' is larger than width!\n";
        }

        yPos = util::letterToUI8(line[2]);
        if (yPos == 255)
        {
            std::cout << "\'" << line[2] << "\' is invalid!\n";
        }
        if (yPos >= height)
        {
            std::cout << "\'" << static_cast<int>(yPos) << "\' is larger than height!\n";
        }

        action = line[0] == 'c' ? Action::CLICK : Action::FLAG;
        break;
    }
}
bool shouldExitTerminal()
{
    while (true)
    {
        std::cout << "Play another game? (Y/n)\n";
        std::string input;
        getline(std::cin, input);
    
        char firstLetter = tolower(input[0]);
        if (firstLetter == 'y')
        {
            return true;
        }
        else if (firstLetter == 'n')
        {
            return false;
        }
        std::cout << "\"" << input << "\"" << " is an invalid input!\n";
    }
}
void runInTerminal()
{
    do
    {
        mswp::BoardWidth width;
        mswp::BoardHeight height;
        mswp::BombCount bombCount;
        getWidthHeightBombCountTerminal(width, height, bombCount);
    
        mswp::MineSweeper board(width, height, bombCount, time(0));
    
        while(true)
        {
            std::cout << "Flags: " << static_cast<int>(board.flagsRemaining()) << "\n";
            std::cout << "Remaining Tiles: " << static_cast<int>(board.remainingTile()) << "\n";
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
            }
        }
        
        std::cout << "Flags: " << static_cast<int>(board.flagsRemaining()) << "\n";
        std::cout << "Remaining Tiles: " << static_cast<int>(board.remainingTile()) << "\n";
        std::cout << board;
        if (board.gameState() == mswp::MineSweeper::WON)
        {
            std::cout << "WON\n";
        }
        else
        {
            std::cout << "LOST\n";
        }
    } while(shouldExitTerminal());
}

} // app end