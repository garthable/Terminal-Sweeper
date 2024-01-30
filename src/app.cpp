#include "../include/app.h"

void app::run()
{
    while (true)
    {
        system("clear");
        // std::cout << "Type \"p\" to play minesweeper" << std::endl;
        std::cout << "Type \"w\" to watch minesweeper algorithm" << std::endl;
        std::cout << "Type \"t\" to test minesweeper algorithm" << std::endl;
        std::cout << "Type \"q\" to quit" << std::endl;

        std::string input;
        getline(std::cin, input);

        if (input == "")
            continue;
        char c = input[0];
        switch (c)
        {
        // case 'p':
        //     readSettings();
        //     play();
        //     break;
        case 'w':
            readSettings();
            watch();
            break;
        case 't':
            readSettings();
            massTests();
            break;
        case 'q':
            exit(0);
            break;
        
        default:
            break;
        }
    }
}

app::app()
{
    readSettings();
}

void app::play()
{

}

void app::massTests()
{
    mineMap map = mineMap(0, m_safeRadius, m_difficulty);
    solver s = solver(map.sizeX, map.sizeY, m_safeRadius);

    int iteration = 0;
    int wins = 0;
    int losses = 0;
    
    bool generated = false;

    time_t start;
    time_t end;

    time(&start);

    while (m_runAmount > wins + losses)
    {
        iteration++;

        if (!generated)
        {
            map.generateBombs(s.getClickX(), s.getClickY());
            generated = true;
        }
        if (!map.click(s.getClickX(), s.getClickY()))
        {
            generated = false;

            map.reset();
            s.reset();

            losses++;
            iteration = 0;

            system("clear");
            std::cout << wins + losses << std::endl
            << "Wins: " << wins << std::endl
            << "Losses: " << losses << std::endl;

            map.setSeed(wins + losses);
            continue;
        }
        if (map.won())
        {
            generated = false;

            map.reset();
            s.reset();

            wins++;
            iteration = 0;

            system("clear");
            std::cout << wins + losses << std::endl
            << "Wins: " << wins << std::endl
            << "Losses: " << losses << std::endl;

            map.setSeed(wins + losses);
            continue;
        }

        s.update(map.print());
        
        for (coord c : s.getFlagged())
            map.flag(c.x, c.y);
    }
    time(&end);
    double time_taken = double(end - start);
    system("clear");
    std::cout << "######################################################" << std::endl;
    std::cout << "Total Games: " << wins + losses << std::endl << std::endl;
    std::cout << "Wins:        " << wins << std::endl;
    std::cout << "Losses:      " << losses << std::endl << std::endl;
    std::cout << "Win Rate:    " << ((float)wins/(float)m_runAmount)*100 << "%" << std::endl << std::endl;
    std::cout << "######################################################" << std::endl;
    std::cout << "Time Taken:         " << time_taken << " secs" << std::endl;
    std::cout << "Time Taken per run: " << (time_taken/(float)m_runAmount)*1000.0F << " millisecs per run" << std::endl << std::endl;
    std::cout << "######################################################" << std::endl;
    std::cin.get();
}

void app::watch()
{
    int seed = m_seed;
    if (m_randSeed)
        seed = time(0);

    mineMap map = mineMap(seed, m_safeRadius, m_difficulty);
    solver s = solver(map.sizeX, map.sizeY, m_safeRadius);

    int iteration = 0;
    
    bool generated = false;

    while (true)
    {
        iteration++;

        if (!generated)
        {
            map.generateBombs(s.getClickX(), s.getClickY());
            generated = true;
        }
        if (!map.click(s.getClickX(), s.getClickY()))
        {
            system("clear");
            std::cout << "iteration: " << iteration << std::endl;
            std::cout << "seed " << seed << std::endl;
            std::cout << "guesses: " << s.getGuesses() << std::endl;
            std::cout << map.printWithSpaces() << std::endl;
            std::cout << "Explode at " << s.getClickX() << " " << s.getClickY() << std::endl;
            std::cin.get();
            return;
        }
        else if (map.won())
        {
            system("clear");
            std::cout << "c " << s.getClickX() << " " << s.getClickY() << std::endl;
            std::cout << "iteration: " << iteration << std::endl;
            std::cout << "seed " << seed << std::endl;
            std::cout << "guesses: " << s.getGuesses() << std::endl;
            std::cout << map.printWithSpaces() << std::endl;
            std::cout << "Solved!" << std::endl;
            std::cin.get();
            return;
        }
        else
        {
            system("clear");
            std::cout << "c " << s.getClickX() << " " << s.getClickY() << std::endl;
            std::cout << "seed " << seed << std::endl;
            std::cout << "iteration: " << iteration << std::endl;
            std::cout << "guesses: " << s.getGuesses() << std::endl;
            std::cout << map.printWithSpaces() << std::endl;
            usleep(m_waitTime);
        }

        s.update(map.print());
        
        for (coord c : s.getFlagged())
            map.flag(c.x, c.y);
    }
}

void app::readSettings()
{
    std::ifstream settingsFile(SETTINGSFILE);
    if (!settingsFile.is_open())
    {
        settingsFile.close();
        settingsFile.open(SETTINGSFILE2);
        if (!settingsFile.is_open())
            throw std::runtime_error("readSettings failed to open settings file!");   
    }
    
    std::string line;

    while (std::getline(settingsFile, line))
    {
        std::string lineReader = "";
        for (char c : line)
        {
            lineReader += c;
            if (lineReader == "run_amount: ")
            {
                std::string setting = line.substr(lineReader.size(), line.size());
                m_runAmount = std::stoi(setting);
                break;
            }
            else if (lineReader == "difficulty: ")
            {
                std::string setting = line.substr(lineReader.size(), line.size());
                if (setting == "beginner")
                    m_difficulty = beginner;
                else if (setting == "intermediate")
                    m_difficulty = intermediate;
                else if (setting == "expert")
                    m_difficulty = expert;
                break;
            }
            else if (lineReader == "seed: ")
            {
                std::string setting = line.substr(lineReader.size(), line.size());
                if (setting[0] == 'r')
                {
                    m_randSeed = true;
                    break;
                }
                m_seed = std::stoi(setting);
                m_randSeed = false;
                break;
            }
            else if (lineReader == "wait_time: ")
            {
                std::string setting = line.substr(lineReader.size(), line.size());
                m_waitTime = std::stoi(setting);
                break;
            }
            m_safeRadius = 2;
        }
    }
    settingsFile.close();
}