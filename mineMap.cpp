#include <cmath>
#include <string>
#include "mineMap.h"
#include <iostream>

node* mineMap::searchNode(int x, int y)
{
    for (node* n : nodes)
        if (n->x == x && n->y == y)
            return n;
    return nullptr;
}

void mineMap::reset()
{
    bombCount = 0;
    for (node* n : nodes)
    {
        n->isRevealed = false;
        n->isBomb = false;
        n->isFlagged = false;
        n->adjBombCount = 0;
    }
}

void mineMap::setSeed(int _seed)
{
    seed = _seed;
}

void mineMap::generateBombs(int x, int y)
{
    reset();
    srand(seed);
    for (node* n : chunkNodes)
    {
        if (abs(n->x - x) < 3 && abs(n->y - y) < 3)
            continue;

        if (rand() % 100 > CHUNKCHANCE)
            continue;

        if (n->isBomb || rand() % 100 <= BOMBCHANCE)
        {
            n->isBomb = true;
            bombCount++;
        }

        if (bombCount == BOMBCOUNT)
            goto exit;
        
        for (node* a : n->adjNodes)
        {
            if (a->isBomb || rand() % 100 > BOMBCHANCE)
                continue;

            a->isBomb = true;
            bombCount++;

            if (bombCount == BOMBCOUNT)
                goto exit;
        }
    }
    while (bombCount != BOMBCOUNT)
    {
        int randomIndex = rand() % nodes.size();
        node* n = nodes[randomIndex];
        if (n->isBomb || (abs(n->x - x) < 3 && abs(n->y - y) < 3))
            continue;
        n->isBomb = true;
        bombCount++;
    }
    exit:

    for (node* n : nodes)
    {
        int bombs = 0;
        for (node* a : n->adjNodes)
            if (a->isBomb)
                bombs++;
        n->adjBombCount = bombs;
    }
}

void mineMap::reveal(node* curr)
{
    if (!curr)
        return;

    curr->isRevealed = true;
    if (curr->adjBombCount != 0 || curr->isBomb)
        return;

    for (node* n : curr->adjNodes)
    {
        if (!n || n->isRevealed)
            continue;
        reveal(n);
    }
}

void mineMap::flag(int x, int y)
{
    node* flaggedNode = searchNode(x, y);
    if (!flaggedNode)
    {
        assert(false);
    }

    if (!flaggedNode->isBomb)
    {
        std::cout << "Wrong flag at: " << x << " " << y << std::endl;
        exit(0);
    }

    if (!flaggedNode->isFlagged)
        bombCount--;
    flaggedNode->isFlagged = true;
}

bool mineMap::click(int x, int y)
{
    node* clickedNode = searchNode(x, y);
    if (!clickedNode)
    {
        assert(false);
    }

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
    for (node* n : nodes)
        if (!n->isBomb && !n->isRevealed)
            return false;
    return true;
}

float mineMap::averageBombAdjs()
{
    float chance = 0;
    int _bombCount = 0;
    for (node* n : nodes)
    {
        if (n->isBomb)
        {
            _bombCount++;
            int adjBombCount = 0;
            for (node* a : n->adjNodes)
                if (a->isBomb)
                    adjBombCount++;
            chance += (float)adjBombCount/(float)n->adjNodes.size();
        }
    }
    return chance/(float)_bombCount;
}

float mineMap::averageNonBombAdjs()
{
    float chance = 0;
    int _notBombCount = 0;
    for (node* n : nodes)
    {
        if (!n->isBomb)
        {
            _notBombCount++;
            int adjBombCount = 0;
            for (node* a : n->adjNodes)
                if (a->isBomb)
                    adjBombCount++;
            chance += (float)adjBombCount/(float)n->adjNodes.size();
        }
    }
    return chance/(float)_notBombCount;
}

float mineMap::averageAdjs()
{
    float chance = 0;
    int count = 0;
    for (node* n : nodes)
    {
        count++;
        int adjBombCount = 0;
        for (node* a : n->adjNodes)
            if (a->isBomb)
                adjBombCount++;
        chance += (float)adjBombCount/(float)n->adjNodes.size();
    }
    return chance/(float)count;
}

float mineMap::chanceOfAdj(int type, int val)
{
    float chance = 0;
    int notBombCount = 0;
    for (node* n : nodes)
    {
        if (n->isBomb || n->adjBombCount != type)
            continue;

        notBombCount++;

        int count = 0;

        for (node* a : n->adjNodes)
        {
            if (a->isBomb)
                continue;
            if (a->adjBombCount == val)
                count++;
        }
        
        chance += (float)count/n->adjNodes.size();
    }
    if (notBombCount == 0)
        return 0;
    return chance/(float)notBombCount;
}

float mineMap::amountOf(int type)
{
    float amount = 0;
    for (node* n : nodes)
    {
        if (n->isBomb || n->adjBombCount != type)
            continue;

        amount++;
    }

    return amount;
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

mineMap::mineMap(int _seed)
{
    seed = _seed;
    bombCount = -1;
    for (int i = 0; i < SIZEY; i++)
        for (int j = 0; j < SIZEX; j++)
        {
            node* n = new node(j, i);
            nodes.push_back(n);
            if (i % 3 == 0 && j % 3 == 0)
                chunkNodes.push_back(n);
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