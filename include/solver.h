#include <stack>

#include "mineMap.h"
#include "probabilityFinder.h"

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
    unsigned short distFromCenterWeight;

    std::vector<unsigned short> adjNodes;

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
        distFromCenterWeight = -1;

        group = 0;
    }
};


class solver
{
    public:
        void update(const std::string&);

        void reset();

        unsigned short getClickX();
        unsigned short getClickY();
        unsigned short getGuesses();
        std::vector<coord> getFlagged();

        solver(const unsigned short&, const unsigned short&, const unsigned short&);
        ~solver();

    private:
        inline int searchNode(const unsigned short& x, const unsigned short& y)
        {
            if (x >= m_sizeX || y >= m_sizeY || x < 0 || y < 0)
                return -1;
            return x + (y*m_sizeX);
        }
        bool bombsInStack();
        void readMineMap(const std::string&);
        void getProbabilities();
        void getEasyNoBombs();
        void chooseNextClick();

        void DFSHelper(solverNode*&, const unsigned short&, std::vector<solverNode*>&);
        void DFSGrouping(std::vector<solverNode*>&);
        bool shareNumbered(solverNode*&, solverNode*&, std::vector<solverNode*>&);

        void printMap();
        void getImportantNodes();
        void assignDistance();

    private:
        std::vector<solverNode*> m_nodes;
        std::vector<solverNode*> m_importantNodes;
        std::stack<solverNode*> m_noBombNodes;
        std::vector<coord> m_flagged;
        unsigned short m_clickX;
        unsigned short m_clickY;
        unsigned short m_bombCount;
        unsigned short m_undiscoveredCount;
        unsigned short m_amountOfGuesses;
        float m_averageBombsUsed;
        unsigned short m_undiscoveredUsed;
        unsigned short m_minAmountOfBombsUsed;

        unsigned short m_sizeX;
        unsigned short m_sizeY;
};

#endif