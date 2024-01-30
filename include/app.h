#include <string>
#include <iostream>
#include <fstream>
#include <sys/time.h>
#include <unistd.h>
#include "solver.h"

#ifndef APP
#define APP

#define SETTINGSFILE "doc/settings.txt"
#define SETTINGSFILE2 "../doc/settings.txt"

class app
{
    public:
        void run();
        app();

    private:
        void play();
        void watch();
        void massTests();

        void readSettings();
    
    private:
        unsigned long m_runAmount;
        difficulty m_difficulty;

        bool m_randSeed;
        int m_seed;
        int m_waitTime;
        int m_safeRadius;
};

#endif