#include <vector>
#include <array>
#include <string>

#ifndef MINEMAP
#define MINEMAP

enum difficulty
{
    beginner,
    intermediate,
    expert
};

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
        void reset();
        void setSeed(const unsigned int&);
        void generateBombs(const unsigned short&, const unsigned short&);
        void flag(const unsigned short&, const unsigned short&);
        bool click(const unsigned short&, const unsigned short&);
        bool won();

        std::string print();
        std::string printWithSpaces();

        mineMap(const unsigned int&, const unsigned int&, const difficulty&);
        ~mineMap();

    public:
        unsigned short sizeX;
        unsigned short sizeY;
        unsigned short bombCount;

    private:
        inline int searchNode(const short&, const short&);
        void reveal(node&);

        unsigned int m_seed;
        unsigned short m_safeRadius;
        unsigned short m_bombCount;
        std::vector<node> m_nodes;
};

#endif