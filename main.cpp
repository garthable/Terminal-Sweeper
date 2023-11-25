#include <unistd.h>
#include "solver.h"
#include <iostream>
#include <sys/time.h>

// #define DEBUG

#define CHANCEOF 8

int main()
{
    #ifndef DEBUG
    mineMap map = mineMap(0);
    #else
    int seed = time(0);
    seed = 166;
    mineMap map = mineMap(seed);
    #endif
    solver s = solver();

    int iteration = 0;

    #ifndef DEBUG
    float guessAmountLost = 0;
    float guessAmountWon = 0;
    float averageGuessPerIterationLost = 0;
    float averageGuessPerIterationWon = 0;
    int wins = 0;
    int losses = 0;
    int runAmount = 1000;
    int iterationAmountWon = 0;
    int iterationAmountLost = 0;

    float chanceOfAdj[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    float amountOf[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
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
            #ifndef DEBUG
            // for (int i = 0; i < 9; i++)
            //     amountOf[i] += map.amountOf(i);
            #endif
        }
        if (!map.click(s.getClickX(), s.getClickY()))
        {
            #ifndef DEBUG
            generated = false;
            guessAmountLost += s.getGuesses();
            averageGuessPerIterationLost += (float)s.getGuesses()/(float)iteration;
            iterationAmountLost += iteration;

            // std::cout << wins + losses << std::endl;
            // std::cout << map.printWithSpaces() << std::endl;

            map.reset();
            s.reset();

            // std::cin.get();

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
            averageGuessPerIterationWon += (float)s.getGuesses()/(float)iteration;
            iterationAmountWon += iteration;

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
    std::cout << "Time Taken:         " << time_taken << " secs" << std::endl;
    std::cout << "Time Taken per run: " << (time_taken/(float)runAmount)*1000.0F << " millisecs per run" << std::endl << std::endl;
    std::cout << "######################################################" << std::endl;
    std::cout << "Total Games:    " << wins + losses << std::endl << std::endl;
    std::cout << "Wins:           " << wins << std::endl;
    std::cout << "Losses:         " << losses << std::endl << std::endl;
    std::cout << "Win Loss Ratio: " << (float)wins/(float)losses << std::endl << std::endl;
    std::cout << "######################################################" << std::endl;
    std::cout << "Average Iterations:               " << ((float)iterationAmountWon + (float)iterationAmountLost)/(float)runAmount << std::endl << std::endl;
    std::cout << "Average Iterations In Won Games:  " << ((float)iterationAmountWon)/(float)wins << std::endl;
    std::cout << "Average Iterations In Lost Games: " << ((float)iterationAmountLost)/(float)losses << std::endl << std::endl;
    std::cout << "######################################################" << std::endl;
    std::cout << "Average Guesses:               " << (guessAmountLost + guessAmountWon)/(float)runAmount << std::endl << std::endl;
    std::cout << "Average Guesses In Won Games:  " << (guessAmountWon)/(float)wins << std::endl;
    std::cout << "Average Guesses In Lost Games: " << (guessAmountLost)/(float)losses << std::endl << std::endl;
    std::cout << "######################################################" << std::endl;
    std::cout << "Average Guesses per Iteration:               " << (averageGuessPerIterationWon + averageGuessPerIterationLost)/(float)runAmount << std::endl << std::endl;
    std::cout << "Average Guesses per Iteration In Won Games:  " << (averageGuessPerIterationWon)/(float)wins << std::endl;
    std::cout << "Average Guesses per Iteration In Lost Games: " << (averageGuessPerIterationWon + averageGuessPerIterationLost)/(float)losses << std::endl << std::endl;
    std::cout << "######################################################" << std::endl;
    // for (int i = 0; i < 9; i++)
    // {
    //     std::cout << "Amount of " << i << ": " << amountOf[i]/(float)runAmount << std::endl;
    // }
    // std::cout << "######################################################" << std::endl;
    #endif

    return 1;
}