#include <vector>
#include <array>
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

    short x;
    short y;

    unsigned short adjBombCount;

    std::vector<unsigned short> adjNodes;

    node(short _x, short _y)
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
        int searchNode(const short&, const short&);

        void reset();
        void setSeed(const unsigned int&);
        void generateBombs(const unsigned short&, const unsigned short&);
        void flag(const unsigned short&, const unsigned short&);
        bool click(const unsigned short&, const unsigned short&);
        void reveal(node&);
        bool won();

        std::string print();
        std::string printWithSpaces();

        mineMap(const unsigned int&);
        ~mineMap();

    private:
        unsigned int seed;
        unsigned short bombCount;
        std::vector<node> nodes;
};

#endif