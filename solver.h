#include "mineMap.h"
#include <stack>
#include "bruteForceLogic.h"

#ifndef SOLVER
#define SOLVER

#define INFOMODIFIER

struct coord
{
    int x;
    int y;

    coord(int _x, int _y)
    {
        x = _x;
        y = _y;
    }
};

struct solverNode
{
    bool discovered;
    bool flagged;
    bool nextToFlag;

    bool visited;

    int group;

    int x;
    int y;
    int adjBombs;

    float weight;

    std::vector<solverNode*> adjNodes;

    solverNode(int _x, int _y)
    {
        discovered = false;
        nextToFlag = false;
        flagged = false;
        visited = false;
        x = _x;
        y = _y;
        adjBombs = 0;

        weight = 0;

        group = 0;
    }
};


class solver
{
    public:
        solverNode* searchNode(int, int);
        solverNode* searchNode(int);

        void update(std::string);
        void printMap();
        void readMineMap(std::string);

        void testIncogs();
        void runBruteForce();
        void getEasyNoBombs();
        void updateWeights();
        void chooseNextClick();
        void reset();

        void DFSHelper(solverNode*, int, std::vector<solverNode*>);
        void DFSGrouping(std::vector<solverNode*>);
        bool shareNumbered(solverNode*, solverNode*, std::vector<solverNode*>);

        void resetValidCombinations();
        void resetMarked();
        int getBorderingBombCount();
        std::vector<std::vector<solverNode*>> findValidCombinations(std::vector<std::vector<solverNode*>>);

        bool bombsInStack();

        int getClickX();
        int getClickY();
        int getGuesses();
        std::vector<coord> getFlagged();

        solver();
        ~solver();

    private:
        std::vector<solverNode*> nodes;
        std::stack<solverNode*> noBombNodes;
        std::vector<solverNode*> meaningfulNodes;
        std::vector<coord> flagged;
        int clickX;
        int clickY;
        int bombCount;
        int undiscoveredCount;
        int amountOfGuesses;
};

#endif