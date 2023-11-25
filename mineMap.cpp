#include <cmath>
#include <string>
#include "mineMap.h"
#include <iostream>

node* mineMap::searchNode(const unsigned short& x, const unsigned short& y)
{
    if (x >= SIZEX || y >= SIZEY || x < 0 || y < 0)
        return nullptr;
    node* n = nodes[x + (y*SIZEX)];
    return n;
}

void mineMap::reset()
{
    bombCount = 0;
    for (node*& n : nodes)
    {
        n->isRevealed = false;
        n->isBomb = false;
        n->isFlagged = false;
        n->adjBombCount = 0;
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
        node* n = nodes[randomIndex];
        if (n->isBomb || (abs(n->x - x) < 3 && abs(n->y - y) < 3))
            continue;
        n->isBomb = true;
        bombCount++;
    }

    for (node* n : nodes)
    {
        int bombs = 0;
        for (node*& a : n->adjNodes)
            if (a->isBomb)
                bombs++;
        n->adjBombCount = bombs;
    }
}

void mineMap::reveal(node*& curr)
{
    if (!curr)
        return;

    curr->isRevealed = true;
    if (curr->adjBombCount != 0 || curr->isBomb)
        return;

    for (node*& n : curr->adjNodes)
    {
        if (!n || n->isRevealed)
            continue;
        reveal(n);
    }
}

void mineMap::flag(const unsigned short& x, const unsigned short& y)
{
    node* flaggedNode = searchNode(x, y);
    if (!flaggedNode)
        assert(false);

    if (!flaggedNode->isBomb)
    {
        std::cout << "Wrong flag at: " << x << " " << y << std::endl;
        exit(0);
    }

    if (!flaggedNode->isFlagged)
        bombCount--;
    flaggedNode->isFlagged = true;
}

bool mineMap::click(const unsigned short& x, const unsigned short& y)
{
    node* clickedNode = searchNode(x, y);
    if (!clickedNode)
        assert(false);

    if (clickedNode->isBomb)
    {
        reveal(clickedNode);
        return false;
    }

    reveal(clickedNode);

    return true;
}

bool mineMap::won()
{
    for (node*& n : nodes)
        if (!n->isBomb && !n->isRevealed)
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

    for (node* n : nodes)
    {
        if (currY != n->y)
        {
            currY = n->y;
            output += '\n';
        }
        if (n->isBomb && n->isRevealed)
            output += 'X';
        else if (!n->isRevealed && n->isFlagged)
            output += '@';
        else if (!n->isRevealed)
            output += '#';
        else if (n->adjBombCount == 0)
            output += ' ';
        else
            output += (char)('0' + n->adjBombCount);
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

    for (node* n : nodes)
    {
        if (currY != n->y)
        {
            currY = n->y;
            output += '\n';
        }
        if (n->isBomb && n->isRevealed)
            output += 'X';
        else if (!n->isRevealed && n->isFlagged)
            output += '@';
        else if (!n->isRevealed)
            output += '#';
        else if (n->adjBombCount == 0)
            output += ' ';
        else
            output += (char)('0' + n->adjBombCount);

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
            node* n = new node(x, y);
            nodes.push_back(n);
        }

    int offset[8][2] = {{-1, 1},  {0, 1},  {1, 1}, 
                        {-1, 0},           {1, 0}, 
                        {-1, -1}, {0, -1}, {1, -1}};

    for (node* n : nodes)
        for (int i = 0; i < 8; i++)
        {
            node* adjNode = searchNode(n->x + offset[i][0], n->y + offset[i][1]);

            if (!adjNode)
                continue;
            
            n->adjNodes.push_back(adjNode);
        }
}

mineMap::~mineMap()
{
    for (node* n : nodes)
        delete n;
}