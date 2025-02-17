#include <iostream>
#include <fstream>
#include <filesystem>
#include <chrono>

#include "app.hpp"
#include "mineSweeper.hpp"
#include "mineSweeperSolver.hpp"

App::App()
{
    m_makeSeedEqualToTime = false;
    m_sizeX = 0;
    m_sizeY = 0;
    m_bombCount = 0;
    m_seed = 0;
}

// Purpose:
// Spaces out string to make it more readable
std::string spaceOutString(std::string inputString)
{
    std::string outputString = "";

    for (const char& character : inputString)
    {
        outputString += character;

        if (character == '\n')
        {
            continue;
        }

        outputString += ' ';
    }

    return outputString;
}

void App::run()
{
    while (true)
    {
        #if defined(__APPLE__) || defined(__linux__) 
            system("clear");
        #endif
        #ifdef __WIN32__
            system("cls");
        #endif
        std::string input = "";

        std::cout << 
        "Type 'p' to play minesweeper.\nType 'w' to watch minesweeper solver.\nType 't' to test minesweeper solver performance.\nType 'r' to run tests on minesweeper solver\nType 'q' to quit\n";

        getline(std::cin, input);

        if (input == "")
        {
            continue;
        }
        
        char firstLetterInInput = input[0];

        switch (firstLetterInInput)
        {
            case 'p':
                readSettings();
                playMineSweeper();
                break;
            case 'w':
                readSettings();
                watchMineSweeperSolver();
                break;
            case 't':
                readSettings();
                testMineSweeperSolver();
                break;
            case 'r':
                readSettings();
                debugTestMineSweeperSolver();
                break;
            case 'q':
                return;
                break;
            default:
                break;
        }
    }
}

void App::readSettings()
{
    std::string line = "";
    std::fstream settingsFileRead = std::fstream(SETTINGSFILE);

    if (!settingsFileRead.is_open())
    {
        std::string report = "Failed to open: " + std::string(SETTINGSFILE);
        throw std::runtime_error(report);
    }

    while (getline(settingsFileRead, line))
    {
        std::string tempString = "";
        for (const char& character : line)
        {
            tempString += character;
            if (tempString == "#")
            {
                continue;
            }
            else if (tempString == "difficulty: ")
            {
                std::string setting = line.substr(tempString.size(), line.size());
                if (setting == "baby")
                {
                    m_sizeX = 4;
                    m_sizeY = 4;
                    m_bombCount = 2;
                }
                else if (setting == "beginner")
                {
                    m_sizeX = 9;
                    m_sizeY = 9;
                    m_bombCount = 10;
                }
                else if (setting == "intermediate")
                {
                    m_sizeX = 16;
                    m_sizeY = 16;
                    m_bombCount = 40;
                }
                else if (setting == "expert")
                {
                    m_sizeX = 30;
                    m_sizeY = 16;
                    m_bombCount = 99;
                }
            }
            else if (tempString == "seed: ")
            {
                std::string setting = line.substr(tempString.size(), line.size());

                if (setting == "")
                {
                    continue;
                }
                else if (setting[0] == 't') // For the seeds setting typing 't' means to make the seed equal the time.
                {
                    m_makeSeedEqualToTime = true;
                    m_seed = 0;
                }
                else
                {
                    m_makeSeedEqualToTime = false;
                    m_seed = std::stoi(setting);
                }
            }
        }
    }
}

struct ParsedInput
{
    bool isFlag;
    uint8_t x;
    uint8_t y;
    ParsedInput(const bool& _isFlag, const uint8_t& _x, const uint8_t& _y)
    {
        isFlag = _isFlag;
        x = _x;
        y = _y;
    }
};

// Purpose:
// Temporary Parser used to get inputs
ParsedInput parser(std::string input)
{
    bool isFlag = false;
    uint8_t x = 80;
    uint8_t y = 80;

    uint8_t state = 0;

    std::string tempString = "";

    for (const char& character : input)
    {
        if (character != ' ')
        {
            tempString += character;
            continue;
        }
        else if (state == 0)
        {
            if (tempString == "f")
                isFlag = true;
        }
        else
        {
            x = std::stoi(tempString);
        }

        tempString = "";
        state++;
    }

    y = std::stoi(tempString);

    return ParsedInput(isFlag, x, y);
}

void App::playMineSweeper()
{
    MineSweeper _mineSweeper = MineSweeper(m_sizeX, m_sizeY, m_bombCount);
    bool isFirstMove = true;
    bool isFlag = false;
    uint8_t clickX = 0;
    uint8_t clickY = 0;

    if (m_makeSeedEqualToTime)
    {
        m_seed = time(0);
    }
    while (true)
    {
    #if defined(__APPLE__) || defined(__linux__) 
        system("clear");
    #endif
    #ifdef __WIN32__
        system("cls");
    #endif

        // Get Output:
        std::cout << "Flags: " << _mineSweeper.getFlagsRemaining() << '\n'
        << spaceOutString(_mineSweeper.getOutputMineSweeperMap()) << '\n';

        // Win loss detection:
        if (_mineSweeper.isLost())
        {
            std::cout << "KABOOM\n";
            break;
        }
        else if (_mineSweeper.isWon())
        {
            std::cout << "VICTORY\n";
            break;
        }

        // Get Input: NOT SAFE
        std::string input = "";
        getline(std::cin, input);

        ParsedInput p = parser(input);
        clickX = p.x;
        clickY = p.y;
        isFlag = p.isFlag;

        if (clickX >= m_sizeX || clickY >= m_sizeY)
        {
            continue;
        }

        // Use Input:
        if (isFirstMove && !isFlag)
        {
            isFirstMove = false;
            _mineSweeper.generateBombs(clickX, clickY, m_seed);
        }

        if (isFlag)
        {
            _mineSweeper.flagTile(clickX, clickY);
        }
        else
        {
            _mineSweeper.clickTile(clickX, clickY);
        }
    }
}

void App::watchMineSweeperSolver()
{
    MineSweeper _mineSweeper = MineSweeper(m_sizeX, m_sizeY, m_bombCount);
    MineSweeperSolver _mineSweeperSolver = MineSweeperSolver(m_sizeX, m_sizeY, m_bombCount);
    bool isFirstMove = true;
    bool isFlag = false;
    uint16_t clickX = 0;
    uint16_t clickY = 0;

    if (m_makeSeedEqualToTime)
    {
        m_seed = time(0);
    }
    _mineSweeper.generateBombs(1, 1, m_seed);
    _mineSweeper.clickTile(1, 1);
    while (true)
    {
        // Get Output:
        std::cout << "Flags: " << _mineSweeper.getFlagsRemaining() << '\n'
        << spaceOutString(_mineSweeper.getOutputMineSweeperMap()) << '\n';

        // Win loss detection:
        if (_mineSweeper.isLost())
        {
            std::cout << "KABOOM" << '\n';
            std::cin.get();
            break;
        }
        else if (_mineSweeper.isWon())
        {
            std::cout << "VICTORY" << '\n';
            std::cin.get();
            break;
        }

        // Get Input:
        _mineSweeperSolver.update(_mineSweeper.getOutputMineSweeperMap());
        isFlag = false;
        Coordinate coord = _mineSweeperSolver.getReccomendedClick();
        if (coord.x == UINT16_MAX)
        {
            isFlag = true;
            coord = _mineSweeperSolver.getReccomendedFlag();
        }
        clickX = coord.x;
        clickY = coord.y;
        
        if (clickX == UINT16_MAX)
        {
            std::cout << "Unable" << '\n';
            std::cin.get();
            break;
        }

        if (isFlag)
        {
            _mineSweeper.flagTile(clickX, clickY);
        }
        else
        {
            _mineSweeper.clickTile(clickX, clickY);
        }
    }
}

void App::testMineSweeperSolver()
{
    const uint16_t totalGames = 10000;
    MineSweeper _mineSweeper = MineSweeper(m_sizeX, m_sizeY, m_bombCount);
    MineSweeperSolver _mineSweeperSolver = MineSweeperSolver(m_sizeX, m_sizeY, m_bombCount);
    bool isFlag = false;
    uint16_t clickX = 0;
    uint16_t clickY = 0;

    _mineSweeper.generateBombs(1, 1, 0);
    _mineSweeper.clickTile(1, 1);
    uint16_t wins = 0;
    uint16_t loses = 0;
    auto startTime = std::chrono::high_resolution_clock::now();
    while (true)
    {
        if (wins + loses >= totalGames)
        {
            break;
        }

        // Win loss detection:
        if (_mineSweeper.isLost())
        {
            loses++;
            #if defined(__APPLE__) || defined(__linux__) 
                system("clear");
            #endif
            #ifdef __WIN32__
                system("cls");
            #endif
            std::cout << wins + loses << '\n';
            _mineSweeperSolver.reset(m_bombCount);
            _mineSweeper.generateBombs(1, 1, wins+loses);
            _mineSweeper.clickTile(1, 1);
            continue;
        }
        else if (_mineSweeper.isWon())
        {
            wins++;
            #if defined(__APPLE__) || defined(__linux__) 
                system("clear");
            #endif
            #ifdef __WIN32__
                system("cls");
            #endif
            std::cout << wins + loses << '\n';
            _mineSweeperSolver.reset(m_bombCount);
            _mineSweeper.generateBombs(1, 1, wins+loses);
            _mineSweeper.clickTile(1, 1);
            continue;
        }

        // Get Input:
        _mineSweeperSolver.update(_mineSweeper.getOutputMineSweeperMap());
        isFlag = false;
        Coordinate coord = _mineSweeperSolver.getReccomendedClick();
        if (coord.x == UINT16_MAX)
        {
            isFlag = true;
            coord = _mineSweeperSolver.getReccomendedFlag();
        }
        clickX = coord.x;
        clickY = coord.y;
        
        if (clickX == UINT16_MAX)
        {
            std::cout << "Unable" << '\n';
            std::cin.get();
            break;
        }

        if (isFlag)
        {
            _mineSweeper.flagTile(clickX, clickY);
        }
        else
        {
            _mineSweeper.clickTile(clickX, clickY);
        }
    }
    #if defined(__APPLE__) || defined(__linux__) 
        system("clear");
    #endif
    #ifdef __WIN32__
        system("cls");
    #endif
    auto endTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> timeMs = endTime - startTime;
    std::cout 
        << "######################################################" << "\n"
        << "Total Games: " << totalGames << "\n\n"
        << "Wins:        " << wins << "\n" 
        << "Loses:       " << loses << "\n\n" 
        << "Win Rate:    " << (static_cast<double>(wins)/totalGames)*100 << "%\n"
        << "######################################################" << "\n"
        << "Time Taken:         " << timeMs.count() / 1000 << " secs\n"
        << "Time Taken Per Run: " << timeMs.count() / totalGames << " millisecs per run\n\n"
        << "######################################################\n";
    std::cin.get();
}

void App::debugTestMineSweeperSolver()
{
    MineSweeper mineSweeper = MineSweeper(0, 0, 0);
    bool display = false;
    for (const auto& entry : std::filesystem::directory_iterator(TESTDIRECTORY))
    {
        START:
        mineSweeper.generateTilesFromMap(entry.path().string());
        mineSweeper.clickTile(1, 1);
        MineSweeperSolver mineSweeperSolver = MineSweeperSolver(mineSweeper.getSizeX(), mineSweeper.getSizeY(), mineSweeper.getBombCount());
        bool isFlag = false;
        uint16_t clickX = 1;
        uint16_t clickY = 1;
        while (true)
        {
            if (display)
            {
                std::cout << "Flags: " << mineSweeper.getFlagsRemaining() << '\n'
                << spaceOutString(mineSweeper.getOutputMineSweeperMap()) << '\n';
            }
            // Win loss detection:
            if (mineSweeper.isLost())
            {
                if (display)
                {
                    display = false;
                    std::cout << "Lost: " << entry.path() << '\n';
                    std::cin.get();
                }
                else
                {
                    display = true;
                    goto START;
                }
                break;
            }
            else if (mineSweeper.isWon())
            {
                std::cout << "Won: " << entry.path() << '\n';
                break;
            }

            // Get Input:
            mineSweeperSolver.update(mineSweeper.getOutputMineSweeperMap());
            isFlag = false;
            Coordinate coord = mineSweeperSolver.getReccomendedClick();
            if (coord.x == UINT16_MAX)
            {
                isFlag = true;
                coord = mineSweeperSolver.getReccomendedFlag();
            }
            clickX = coord.x;
            clickY = coord.y;
            
            if (clickX == UINT16_MAX)
            {
                std::cout << "Unable" << '\n';
                std::cin.get();
                break;
            }

            if (isFlag)
            {
                mineSweeper.flagTile(clickX, clickY);
            }
            else
            {
                mineSweeper.clickTile(clickX, clickY);
            }
        }
    }
    std::cout << "DONE!\n";
    std::cin.get();
}