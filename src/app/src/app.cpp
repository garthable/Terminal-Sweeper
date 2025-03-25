#include "mine_sweeper.hpp"
#include "mine_sweeper_constants.hpp"
#include "util.hpp"
#include "log.hpp"
#include "app.hpp"

#include "cpp-terminal/input.hpp"
#include "cpp-terminal/screen.hpp"
#include "cpp-terminal/color.hpp"
#include <cpp-terminal/style.hpp>
#include <cpp-terminal/iostream.hpp>

#include "cpp-terminal/private/unicode.hpp"

namespace app
{

Input pollInput(size_t rowMax, size_t colMax)
{
    static size_t currRow = 0;
    static size_t currCol = 0;

    Input input =
    {
        .col = 0,
        .row = 0,
        .action = Input::NONE
    };
    Term::Event event = Term::read_event();
    if (event.type() == Term::Event::Type::Key)
    {
        Term::Key key(event);
        switch (key)
        {
        // Movement
        case Term::Key::ArrowDown:
            UTIL_WRAP_ONE_ADD(currRow, rowMax);
            break;
        case Term::Key::ArrowUp:
            UTIL_WRAP_ONE_SUB(currRow, rowMax);
            break;
        case Term::Key::ArrowRight:
            UTIL_WRAP_ONE_ADD(currCol, colMax);
            break;
        case Term::Key::ArrowLeft:
            UTIL_WRAP_ONE_SUB(currCol, colMax);
            break;

        case Term::Key::s:
            UTIL_WRAP_ONE_ADD(currRow, rowMax);
            break;
        case Term::Key::w:
            UTIL_WRAP_ONE_SUB(currRow, rowMax);
            break;
        case Term::Key::d:
            UTIL_WRAP_ONE_ADD(currCol, colMax);
            break;
        case Term::Key::a:
            UTIL_WRAP_ONE_SUB(currCol, colMax);
            break;

        case Term::Key::S:
            UTIL_WRAP_ONE_ADD(currRow, rowMax);
            break;
        case Term::Key::W:
            UTIL_WRAP_ONE_SUB(currRow, rowMax);
            break;
        case Term::Key::D:
            UTIL_WRAP_ONE_ADD(currCol, colMax);
            break;
        case Term::Key::A:
            UTIL_WRAP_ONE_SUB(currCol, colMax);
            break;

        // Flag and click
        case Term::Key::q:
            input.action = Input::FLAG;
            break;
        case Term::Key::e:
            input.action = Input::CLICK;
            break;

        case Term::Key::Q:
            input.action = Input::FLAG;
            break;
        case Term::Key::E:
            input.action = Input::CLICK;
            break;
        
        default:
            break;
        }
    }

    input.col = currCol;
    input.row = currRow;

    return input;
}
mswp::MineSweeper createBoard()
{
    while (true)
    {
        Input input = pollInput(1u, 3u);
        if (input.action == Input::CLICK)
        {
            switch (input.col)
            {
            case 0: // Beginer
                return mswp::MineSweeper(MSWP_BEGINNER_WIDTH, MSWP_BEGINNER_HEIGHT, MSWP_BEGINNER_BOMB_COUNT, time(0));
            case 1: // Intermediate
                return mswp::MineSweeper(MSWP_INTERMEDIATE_WIDTH, MSWP_INTERMEDIATE_HEIGHT, MSWP_INTERMEDIATE_BOMB_COUNT, time(0));
            case 2: // Expert
                return mswp::MineSweeper(MSWP_EXPERT_WIDTH, MSWP_EXPERT_HEIGHT, MSWP_EXPERT_BOMB_COUNT, time(0));
            
            default:
                break;
            }
        }
    }
}
bool manageInput(Input input, mswp::MineSweeper& outBoard)
{
    if (input.action == Input::NONE)
    {
        return true;
    }

    if (input.action == Input::CLICK)
    {
        return !outBoard.click(input.col, input.row);
    }
    else
    {
        outBoard.flag(input.col, input.row);
        return true;
    }
}
void displayBoard(const Input input, const mswp::MineSweeper& board)
{
    auto& out = std::cout;
    const mswp::TileString& tileString = board.tileString();
    
    out << "Board:\n";
    mswp::TileStringWidth yMax = tileString.size() / tileString.width();

    for (mswp::TileStringIndex i = 0; i < tileString.size(); i++)
    {
        mswp::TileStringWidth x = i % tileString.width();
        mswp::TileStringWidth y = i / tileString.width();
        if (x == input.col && y == input.row)
        {
            out << Term::Style::Reversed << color_fg(Term::Color::Name::Red) << tileCharToChar(tileString[i]) << Term::Style::ResetReversed << color_fg(Term::Color::Name::Default) << ' ';
        }
        else
        {
            out << tileCharToChar(tileString[i]) << ' ';
        }
        if (x == tileString.width() - 1)
        {
            out << '\n';
            if (y + 1 == yMax)
            {
                continue;
            }
        }
    }
}
bool shouldReset()
{
    Input input = pollInput(1u, 2u);
    while (true)
    {
        Input input = pollInput(1u, 3u);
        if (input.action == Input::CLICK)
        {
            switch (input.col)
            {
            case 0: // Play Again
                return false;
            case 1: // Reset
                return true;
            
            default:
                break;
            }
        }
    }
}

} // app end