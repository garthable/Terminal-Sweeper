#ifndef APP
#define APP

#include <stdint.h>

#include "mineSweeperSolver.h"
#include "mineSweeper.h"

#define SETTINGSFILE "doc/settings.txt"

// Handles UI, user input and program state.
class App
{
    public:
        App();

        // Purpose:
        // Runs main program loop
        void run();
    private:
        void readSettings();

        void playMineSweeper();

        // Purpose:
        // Lets user watch in real time as the solver solves the generated map.
        void watchMineSweeperSolver();

        // Purpose:
        // Tests solver against a predetermined number of mine sweeper maps to determine its overall effectiveness.
        void testMineSweeperSolver();

        // Purpose:
        // Runs specially made maps to test capabilities of minesweeper solver
        void debugTestMineSweeperSolver();
    private:
        uint8_t m_sizeX;
        uint8_t m_sizeY;
        uint16_t m_bombCount;

        bool m_makeSeedEqualToTime;
        uint32_t m_seed;
};

#endif