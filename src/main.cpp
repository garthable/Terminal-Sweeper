#include "app.hpp"

#include "cpp-terminal/terminal.hpp"
#include "cpp-terminal/exception.hpp"
#include "cpp-terminal/tty.hpp"

int main(int argc, char** argv)
{
    // Initialize Terminal Input
    Term::terminal.setOptions(Term::Option::ClearScreen, Term::Option::SignalKeys, Term::Option::Cursor, Term::Option::Raw);
    if (!Term::is_stdin_a_tty()) 
    { 
        throw Term::Exception("The terminal is not attached to a TTY and therefore can't catch user input. Exiting..."); 
    }

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
        while(true)
        {
            app::Input newInput = app::pollInput(height, width);
            if (input == newInput)
            {
                continue;
            }
            input = newInput;
            if (!app::manageInput(input, board))
            {
                break;
            }
            app::displayBoard(input, board);
        }
        
        // Check for whether player won or lost
        app::displayBoard(input, board);
        if (board.gameState() == mswp::MineSweeper::WON)
        {
            std::cout << "WON\n";
        }
        else
        {
            std::cout << "LOST\n";
        }
    } 
    while(!app::shouldReset());
}