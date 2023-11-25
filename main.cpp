#include <unistd.h>
#include "solver.h"
#include <iostream>
#include <sys/time.h>

// #define DEBUG

int main()
{
    #ifndef DEBUG
    mineMap map = mineMap(0);
    #else
    int seed = time(0);
    seed = 772;
    mineMap map = mineMap(seed);
    #endif
    solver s = solver();

    int iteration = 0;

    #ifndef DEBUG
    float guessAmountLost = 0;
    float guessAmountWon = 0;
    int wins = 0;
    int losses = 0;
    int runAmount = 1000;
    #endif
    
    bool generated = false;

    time_t start;
    time_t end;

    time(&start);

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
            #ifndef DEBUG
            generated = false;
            guessAmountLost += s.getGuesses();

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
            #else
            system("clear");
            std::cout << "iteration: " << iteration << std::endl;
            std::cout << "guesses: " << s.getGuesses() << std::endl;
            std::cout << map.printWithSpaces() << std::endl;
            std::cout << "Explode at " << s.getClickX() << " " << s.getClickY() << std::endl;
            return 0;
            #endif
        }
        #ifdef DEBUG
        system("clear");
        std::cout << "c " << s.getClickX() << " " << s.getClickY() << std::endl;
        std::cout << "seed " << seed << std::endl;
        std::cout << "iteration: " << iteration << std::endl;
        std::cout << "guesses: " << s.getGuesses() << std::endl;
        std::cout << map.printWithSpaces() << std::endl;
        usleep(100000);
        #endif
        if (map.won())
        {
            #ifndef DEBUG
            generated = false;
            guessAmountWon += s.getGuesses();

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
            #else
            system("clear");
            std::cout << "c " << s.getClickX() << " " << s.getClickY() << std::endl;
            std::cout << "iteration: " << iteration << std::endl;
            std::cout << "guesses: " << s.getGuesses() << std::endl;
            std::cout << map.printWithSpaces() << std::endl;
            std::cout << "YIPPIE" << std::endl;
            return 0;
            #endif
        }
        #ifndef DEBUG
        if (runAmount <= wins + losses)
            break;
        #endif

        s.update(map.print());
        
        for (coord c : s.getFlagged())
            map.flag(c.x, c.y);
    }
    time(&end);
    double time_taken = double(end - start);
    #ifndef DEBUG
    system("clear");
    std::cout << "######################################################" << std::endl;
    std::cout << "Total Games: " << wins + losses << std::endl << std::endl;
    std::cout << "Wins:        " << wins << std::endl;
    std::cout << "Losses:      " << losses << std::endl << std::endl;
    std::cout << "Win Rate:    " << ((float)wins/(float)runAmount)*100 << "%" << std::endl << std::endl;
    std::cout << "######################################################" << std::endl;
    std::cout << "Time Taken:         " << time_taken << " secs" << std::endl;
    std::cout << "Time Taken per run: " << (time_taken/(float)runAmount)*1000.0F << " millisecs per run" << std::endl << std::endl;
    std::cout << "######################################################" << std::endl;
    std::cout << "Average Guesses:               " << (guessAmountLost + guessAmountWon)/(float)runAmount << std::endl << std::endl;
    std::cout << "Average Guesses In Won Games:  " << (guessAmountWon)/(float)wins << std::endl;
    std::cout << "Average Guesses In Lost Games: " << (guessAmountLost)/(float)losses << std::endl << std::endl;
    std::cout << "######################################################" << std::endl;
    #endif

    return 1;
}