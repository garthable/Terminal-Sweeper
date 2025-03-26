#include "app.hpp"
#include "log.hpp"

int main(int argc, char** argv)
{
    // Initializes terminal
    app::init();

    // Main game loop
    do
    {
        // Initialize board
        mswp::MineSweeper board = app::createBoard();

        mswp::BoardWidth width = board.width();
        mswp::BoardHeight height = board.size() / width;
        
        // Play game
        app::Input input =
        {
            .col = 0,
            .row = 0,
            .action = app::Input::Action::NONE
        };
        LOG_INFO("HELLO");
        while(true)
        {
            app::displayBoard(input, board);
            input = app::pollInput(height, width, input);
            if (!app::manageInput(input, board))
            {
                break;
            }
        }
        
        // Check for whether player won or lost
        app::displayBoard(input, board);
        if (board.gameState() == mswp::MineSweeper::WON)
        {
            std::cout << "WON (press any button to continue)\n";
        }
        else
        {
            std::cout << "LOST (press any button to continue)\n";
        }
        app::pollInput(height, width, input);
    } 
    while(!app::shouldReset());
}