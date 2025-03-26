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

#include "cpp-terminal/terminal.hpp"
#include "cpp-terminal/exception.hpp"
#include "cpp-terminal/tty.hpp"

namespace app
{

void init()
{
    // Initialize Terminal Input
    Term::terminal.setOptions(Term::Option::ClearScreen, Term::Option::SignalKeys, Term::Option::Cursor, Term::Option::Raw);
    if (!Term::is_stdin_a_tty()) 
    { 
        throw Term::Exception("The terminal is not attached to a TTY and therefore can't catch user input. Exiting..."); 
    }
}

Input pollInput(size_t rowMax, size_t colMax, Input prevInput)
{
    size_t currRow = prevInput.row;
    size_t currCol = prevInput.col;
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
void drawOptions(std::array<const char*, 3> strings, uint8_t highlightIndex)
{
    auto& out = std::cout;
    for (uint8_t i = 0; i < 3; i++)
    {
        const char* str = strings[i];
        if (i == highlightIndex)
        {
            out << Term::Style::Reversed << str << Term::Style::ResetReversed << '\t';
        }
        else
        {
            out << str << '\t';
        }
    }
    out << '\n';
}
mswp::MineSweeper createBoard()
{
    app::Input input =
    {
        .col = 0,
        .row = 0,
        .action = app::Input::Action::INIT
    };
    while (true)
    {
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
        std::cout << Term::clear_screen() << "Please select a difficulty.\n";
        drawOptions({"Beginner", "Intermediate", "Expert"}, input.col);
        input = pollInput(1u, 3u, input);
    }
}
bool manageInput(Input input, mswp::MineSweeper& outBoard)
{
    if (input.action == Input::NONE || input.action == Input::INIT)
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

Term::Color getColor(const mswp::TileChar::TileCharEnum tileChar)
{
    switch (tileChar)
    {
    case mswp::TileChar::VISIBLE_1:
        return Term::Color::Name::BrightBlue;
    case mswp::TileChar::VISIBLE_2:
        return Term::Color::Name::BrightGreen;
    case mswp::TileChar::VISIBLE_3:
        return Term::Color::Name::BrightRed;
    case mswp::TileChar::VISIBLE_4:
        return Term::Color::Name::Blue;
    case mswp::TileChar::VISIBLE_5:
        return Term::Color::Name::Red;
    case mswp::TileChar::VISIBLE_6:
        return Term::Color::Name::Cyan;
    case mswp::TileChar::VISIBLE_7:
        return Term::Color::Name::Green;
    case mswp::TileChar::VISIBLE_8:
        return Term::Color::Name::Yellow;
    case mswp::TileChar::FLAGGED:
        return Term::Color::Name::Red;
    case mswp::TileChar::HIDDEN:
        return Term::Color::Name::Gray;
    
    default:
        return Term::Color::Name::Default;
    }
}

void displayBoard(const Input input, const mswp::MineSweeper& board)
{
    auto& out = std::cout;
    out << Term::clear_screen();
    const mswp::TileString& tileString = board.tileString();
    
    out << "Flags Remaining: " << static_cast<int>(board.flagsRemaining()) << '\n';
    mswp::TileStringWidth yMax = tileString.size() / tileString.width();

    for (mswp::TileStringIndex i = 0; i < tileString.size(); i++)
    {
        mswp::TileStringWidth x = i % tileString.width();
        mswp::TileStringWidth y = i / tileString.width();
        if (x == input.col && y == input.row)
        {
            Term::Color color = getColor(tileString[i]);
            out << 
                Term::Style::Reversed << 
                    color_fg(color) << 
                        tileCharToChar(tileString[i]) << 
                    color_fg(Term::Color::Name::Default) << 
                Term::Style::ResetReversed << 
            ' ';
        }
        else
        {
            Term::Color color = getColor(tileString[i]);
            out << 
                Term::color_fg(color) << 
                    tileCharToChar(tileString[i]) << 
                Term::color_fg(Term::Color::Name::Default) << 
            ' ';
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
    app::Input input =
    {
        .col = 0,
        .row = 0,
        .action = app::Input::Action::INIT
    };
    while (true)
    {
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
        std::cout << Term::clear_screen() << "Would you like to play another round?\n";
        drawOptions({"Yes", "No", ""}, input.col);
        input = pollInput(1u, 2u, input);
    }
}

} // app end