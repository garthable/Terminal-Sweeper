#include <cmath>
#include <string>
#include "mineMap.h"
#include <iostream>

inline int mineMap::searchNode(const short& x, const short& y)
{
    if (x >= SIZEX || y >= SIZEY || x < 0 || y < 0)
        return -1;
    return x + (y*SIZEX);
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
        if (m_nodes[i].isRevealed)
            continue;
        reveal(m_nodes[i]);
    }
}