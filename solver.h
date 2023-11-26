#include "mineMap.h"
#include <stack>
#include "bruteForceLogic.h"

#ifndef SOLVER
#define SOLVER

#define INFOMODIFIER

struct coord
{
    unsigned short x;
    unsigned short y;

    coord(unsigned short _x, unsigned short _y)
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

    unsigned short group;

    unsigned short x;
    unsigned short y;
    unsigned short adjBombs;

    float weight;

    std::vector<solverNode*> adjNodes;

    solverNode(unsigned short _x, unsigned short _y)
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
        solverNode* searchNode(const unsigned short&, const unsigned short&);
        solverNode* searchNode(const unsigned short&);

        void update(const std::string&);
        void printMap();
        void readMineMap(const std::string&);
        void getImportantNodes();
        void updateImportantNodes();

        void runBruteForce();
        void getEasyNoBombs();
        void updateWeights();
        void chooseNextClick();
        void reset();

        void DFSHelper(solverNode*&, const unsigned short&, std::vector<solverNode*>&);
        void DFSGrouping(std::vector<solverNode*>&);
        bool shareNumbered(solverNode*&, solverNode*&, std::vector<solverNode*>&);

        bool bombsInStack();

        unsigned short getClickX();
        unsigned short getClickY();
        unsigned short getGuesses();
        std::vector<coord> getFlagged();

        solver();
        ~solver();

    private:
        std::vector<solverNode*> nodes;
        std::vector<solverNode*> importantNodes;
        std::stack<solverNode*> noBombNodes;
        std::vector<coord> flagged;
        unsigned short clickX;
        unsigned short clickY;
        unsigned short bombCount;
        unsigned short undiscoveredCount;
        unsigned short amountOfGuesses;
};

#endif