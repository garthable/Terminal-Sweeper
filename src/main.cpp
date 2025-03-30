#include "app.hpp"
#include "log.hpp"

int main(int argc, char** argv)
{
    // Initializes terminal
    app::init();

    bool assist = false;

    // Main game loop
    do
    {
        // Initialize board
        mswp::MineSweeper board = app::createBoard();
        // Initialize Solver
        slvr::MineSweeperSolver solver(board);

        mswp::BoardWidth width = board.width();
        mswp::BoardHeight height = board.size() / width;

        slvr::ActionArray recommendedClicks;
        slvr::ActionArray recommendedFlags;
        
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
            if (assist)
            {
                solver.update(board.tileString());
                slvr::getRecommendedActions(solver, recommendedClicks, recommendedFlags);
                recommendedClicks.update(board.tileString());
                recommendedFlags.update(board.tileString());
            }
            app::displayBoard(input, board, assist, recommendedClicks, recommendedFlags);
            input = app::pollInput(height, width, input);
            if (!app::manageInput(input, board, assist))
            {
                break;
            }
        }
        
        // Check for whether player won or lost
        app::displayBoard(input, board, assist, recommendedClicks, recommendedFlags);
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