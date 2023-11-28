#include "mineMap.h"
#include <stack>
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

        solver();
        ~solver();

    private:
        inline int searchNode(const unsigned short&, const unsigned short&);
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
};

#endif