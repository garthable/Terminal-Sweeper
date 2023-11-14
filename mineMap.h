#include <vector>
#include <string>

#ifndef MINEMAP
#define MINEMAP

#define EXPERT

#ifdef BEGINNER
    #define SIZEX 9
    #define SIZEY 9
    #define BOMBCOUNT 10
#elif defined(INTERMEDIATE)
    #define SIZEX 16
    #define SIZEY 16
    #define BOMBCOUNT 40
#elif defined (EXPERT)
    #define SIZEX 30
    #define SIZEY 16
    #define BOMBCOUNT 99
#else
    #define SIZEX 30
    #define SIZEY 16
    #define BOMBCOUNT 99
#endif

#define CHUNKCHANCE 80
#define BOMBCHANCE 20

struct node
{
    bool isRevealed;
    bool isBomb;
    bool isFlagged;

    int x;
    int y;

    int adjBombCount;

    std::vector<node*> adjNodes;

    node(int _x, int _y)
    {
        x = _x;
        y = _y;

        isRevealed = false;
        isBomb = false;
        isFlagged = false;
        adjBombCount = 0;
    }
};

class mineMap
{
    public:
        node* searchNode(int, int);

        void reset();
        void setSeed(int);
        void generateBombs(int, int);
        void flag(int, int);
        bool click(int, int);
        void reveal(node*);
        bool won();

        float averageBombAdjs();
        float averageNonBombAdjs();
        float averageAdjs();

        float chanceOfAdj(int, int);
        float amountOf(int);

        float standardDivOfAdj(int, int, float);
        float standardDivOfAmountOf(int, float);

        std::string print();
        std::string printWithSpaces();

        mineMap(int);
        ~mineMap();

    private:
        int seed;
        int bombCount;
        std::vector<node*> nodes;
        std::vector<node*> chunkNodes;
};

#endif