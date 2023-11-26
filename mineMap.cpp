#include <cmath>
#include <string>
#include "mineMap.h"
#include <iostream>

int mineMap::searchNode(const short& x, const short& y)
{
    if (x >= SIZEX || y >= SIZEY || x < 0 || y < 0)
        return -1;
    return x + (y*SIZEX);
}

void mineMap::reset()
{
    bombCount = 0;
    for (node& n : nodes)
    {
        n.isRevealed = false;
        n.isBomb = false;
        n.isFlagged = false;
        n.adjBombCount = 0;
    }
}

void mineMap::setSeed(const unsigned int& _seed)
{
    seed = _seed;
}

void mineMap::generateBombs(const unsigned short& x, const unsigned short& y)
{
    reset();
    srand(seed);
    
    while (bombCount != BOMBCOUNT)
    {
        int randomIndex = rand() % nodes.size();
        node& n = nodes[randomIndex];
        if (n.isBomb || (abs(n.x - x) < 3 && abs(n.y - y) < 3))
            continue;
        n.isBomb = true;
        bombCount++;
    }

    for (node& n : nodes)
    {
        unsigned short bombs = 0;
        short x = n.x;
        short y = n.y;

        for (const unsigned short& i : n.adjNodes)
            if (nodes[i].isBomb)
                bombs++;

        n.adjBombCount = bombs;
    }
}

void mineMap::reveal(node& curr)
{
    if (curr.x == -1)
        return;

    curr.isRevealed = true;
    if (curr.adjBombCount != 0 || curr.isBomb)
        return;

    for (const unsigned short& i : curr.adjNodes)
    {
        if (nodes[i].isRevealed)
            continue;
        reveal(nodes[i]);
    }
}

void mineMap::flag(const unsigned short& x, const unsigned short& y)
{
    int index = searchNode(x, y);
    if (index == -1)
        assert(false);

    node& flaggedNode = nodes[index];

    if (!flaggedNode.isBomb)
    {
        std::cout << "Wrong flag at: " << x << " " << y << std::endl;
        exit(0);
    }

    if (!flaggedNode.isFlagged)
        bombCount--;
    flaggedNode.isFlagged = true;
}

bool mineMap::click(const unsigned short& x, const unsigned short& y)
{
    int index = searchNode(x, y);
    if (index == -1)
        assert(false);

    node& clickedNode = nodes[index];

    if (clickedNode.isBomb)
    {
        reveal(clickedNode);
        return false;
    }

    reveal(clickedNode);

    return true;
}

bool mineMap::won()
{
    for (const node& n : nodes)
        if (!n.isBomb && !n.isRevealed)
            return false;
    return true;
}

std::string mineMap::print()
{
    std::string output = "";
    int currY = 0;

    output += "Flags: "; 
    output += std::to_string(bombCount);
    output += '\n';

    for (const node& n : nodes)
    {
        if (currY != n.y)
        {
            currY = n.y;
            output += '\n';
        }
        if (n.isBomb && n.isRevealed)
            output += 'X';
        else if (!n.isRevealed && n.isFlagged)
            output += '@';
        else if (!n.isRevealed)
            output += '#';
        else if (n.adjBombCount == 0)
            output += ' ';
        else
            output += (char)('0' + n.adjBombCount);
    }

    return output;
}

std::string mineMap::printWithSpaces()
{
    std::string output = "";
    int currY = 0;

    output += "Flags: "; 
    output += std::to_string(bombCount);
    output += '\n';

    for (const node& n : nodes)
    {
        if (currY != n.y)
        {
            currY = n.y;
            output += '\n';
        }
        if (n.isBomb && n.isRevealed)
            output += 'X';
        else if (!n.isRevealed && n.isFlagged)
            output += '@';
        else if (!n.isRevealed)
            output += '#';
        else if (n.adjBombCount == 0)
            output += ' ';
        else
            output += (char)('0' + n.adjBombCount);

        output += ' ';
    }

    return  output;
}

mineMap::mineMap(const unsigned int& _seed)
{
    seed = _seed;
    bombCount = -1;
    for (int y = 0; y < SIZEY; y++)
        for (int x = 0; x < SIZEX; x++)
        {
            node n = node(x, y);
            nodes.push_back(n);
        }

    int offset[8][2] = {{-1, 1},  {0, 1},  {1, 1}, 
                        {-1, 0},           {1, 0}, 
                        {-1, -1}, {0, -1}, {1, -1}};

    for (node& n : nodes)
    {
        short x = n.x;
        short y = n.y;
        for (int i = 0; i < 8; i++)
        {
            int index = searchNode(x + offset[i][0], y + offset[i][1]);

            if (index == -1)
                continue;
            
            n.adjNodes.push_back(index);
        }
    }
}

mineMap::~mineMap()
{
    
}