#include "solver.h"
#include <iostream>
#include <math.h>
#include <unistd.h>

solverNode* solver::searchNode(const unsigned short& x, const unsigned short& y)
{
    if (x >= SIZEX || y >= SIZEY || x < 0 || y < 0)
        return nullptr;
    solverNode* n = nodes[x + (y*SIZEX)];
    return n;
}
solverNode* solver::searchNode(const unsigned short& val)
{
    return nodes[val];
}

std::vector<coord> solver::getFlagged()
{
    return flagged;
}

unsigned short solver::getGuesses()
{
    return amountOfGuesses;
}

unsigned short solver::getClickX()
{
    return clickX;
}

unsigned short solver::getClickY()
{
    return clickY;
}

bool solver::bombsInStack()
{
    if (!noBombNodes.empty())
    {
        solverNode* top = noBombNodes.top();
        clickX = top->x;
        clickY = top->y;
        noBombNodes.pop();
        return true;
    }
    return false;
}

void solver::update(const std::string& input)
{
    if (bombsInStack())
        return;

    readMineMap(input);

    getEasyNoBombs();

    if (bombsInStack())
        return;

    runBruteForce();

    if (bombsInStack())
        return;

    chooseNextClick();
}

void solver::reset()
{
    for (solverNode*& n : nodes)
    {
        n->weight = -1;
        n->adjBombs = 0;
        n->group = 0;
        n->flagged = false;
        n->discovered = false;
        n->nextToFlag = false;
        n->visited = false;
    }
    flagged.clear();
    while(!noBombNodes.empty())
        noBombNodes.pop();
    clickX = 1;
    clickY = 1;
    bombCount = 0;
    undiscoveredCount = 0;
    amountOfGuesses = 0;
}

void solver::chooseNextClick()
{
    solverNode* min = nullptr;
    float minWeight = (float)10000;
    float minReplace = ((float)bombCount/(float)undiscoveredCount);

    for (solverNode*& n : nodes)
    {
        if (n->discovered || n->flagged)
            continue;

        float weight = n->weight;

        if (n->weight == -1)
        {
            weight = minReplace;
            if (n->nextToFlag)
                weight += 0.05;
        }
        
        if (minWeight > weight)
        {
            minWeight = weight;
            min = n;
        }
    }

    if (!min)
        return;

    amountOfGuesses++;
    clickX = min->x;
    clickY = min->y;
}

void solver::readMineMap(const std::string& input)
{
    bool firstLine = true;
    unsigned short x = 0;
    unsigned short y = 0;
    unsigned short i = 0;

    bombCount = 0;
    std::string bombStr = "";
    undiscoveredCount = 0;
    for (const char& c : input)
    {
        if (firstLine)
        {
            if (isdigit(c))
                bombStr += c;
            if (c == '\n')
            {
                bombCount = stoi(bombStr);
                firstLine = false;
            }
            continue;
        }

        if (c == '\n')
        {
            y++;
            x = 0;
            continue;
        }

        solverNode* n = nodes[i];

        if (!n)
        {
            std::cout << "null at: " << x << " " << y <<std::endl;
            return;
        }

        if (c == '#' || c == '@')
        {
            if (c == '#')
                undiscoveredCount++;
            n->discovered = false;
        }
        else
            n->discovered = true;

        if (c == ' ')
            n->adjBombs = 0;
        else
            n->adjBombs = c - '0';

        x++;
        i++;
    }
    getImportantNodes();
}

void solver::getImportantNodes()
{
    importantNodes.clear();
    for (solverNode*& n : nodes)
    {
        if (n->flagged || !n->discovered || n->adjBombs == 0)
            continue;
        
        for (solverNode*& a : n->adjNodes)
            if (!a->discovered && !a->flagged)
            {
                importantNodes.push_back(n);
                break;
            }
    }
}

void solver::DFSHelper(solverNode*& curr, const unsigned short& group, std::vector<solverNode*>& set)
{
    curr->visited = true;
    curr->group = group;

    for (solverNode* n : curr->adjNodes)
    {
        if (curr->discovered && n->discovered)
            continue;
        if (n->visited)
            continue;

        bool shouldContinue = true;

        for (solverNode*& compare : set)
            if (n == compare)
                shouldContinue = false;

        if (shouldContinue || (!(curr->discovered || n->discovered) && !shareNumbered(curr, n, set)))
            continue;

        DFSHelper(n, group, set);
    }
}
void solver::DFSGrouping(std::vector<solverNode*>& set)
{
    unsigned short group = 0;
    for (solverNode*& n : nodes)
    {
        n->visited = false;
        n->group = 0;
    }

    for (solverNode*& curr : set)
    {
        if (curr->visited)
            continue;

        DFSHelper(curr, group, set);
        group++;
    }
}
bool solver::shareNumbered(solverNode*& n1, solverNode*& n2, std::vector<solverNode*>& set)
{
    for (solverNode*& a1 : n1->adjNodes)
        for (solverNode*& a2 : n2->adjNodes)
            for (solverNode*& s : set)
                if (a1->discovered && a1 == a2 && a1 == s)
                    return true;
    return false;
}

void solver::runBruteForce()
{
    bruteForce b = bruteForce(bombCount);
    
    std::vector<solverNode*> numNodes;
    std::vector<solverNode*> set;
    std::vector<unsigned short> flaggedAmount;

    for(solverNode*& n : importantNodes)
    {   
        for (solverNode*& a : n->adjNodes)
            if (!a->discovered && !a->flagged)
            {
                numNodes.push_back(n);
                set.push_back(n);
                flaggedAmount.push_back(0);
                break;
            }
    }

    unsigned short numNodesSize = numNodes.size();
    for(unsigned short i = 0; i < numNodesSize; i++)
    {   
        solverNode* n = numNodes[i];
        for (solverNode*& a : n->adjNodes)
        {
            if (a->discovered)
                continue;
            else if (a->flagged)
            {
                flaggedAmount[i]++;
                continue;
            }
            else
                set.push_back(a);
        }
    }

    DFSGrouping(set);

    for (int i = 0; i < numNodesSize; i++)
    {
        solverNode* n = numNodes[i];
        b.addNumbered(n->x + SIZEX*n->y, n->group, n->adjBombs-flaggedAmount[i]);
        for (solverNode*& a : n->adjNodes)
        {
            if (a->discovered || a->flagged)
                continue;
            
            b.addUnknown(a->x + SIZEX*a->y, a->group, n->x + SIZEX*n->y);
        }
    }

    b.findSafePicks();

    for (solverNode*& n : nodes)
    {
        int iD = n->x + n->y*SIZEX;
        float a = b.getProbability(iD);

        if (a == 0)
            noBombNodes.push(n);
        else if (a == 1)
        {
            n->flagged = true;
            flagged.push_back(coord(n->x, n->y));
        }
        else
            n->weight = a;
    }
}

void solver::getEasyNoBombs()
{
    unsigned short newFlags = 0;

    newFlags = 0;
    for (solverNode*& n : importantNodes)
    {
        unsigned short flaggedOptions = 0;
        unsigned short validOptions = 0;

        for (solverNode*& a : n->adjNodes)
            if (a->discovered)
                continue;
            else if (a->flagged)
                flaggedOptions++;
            else
                validOptions++;

        for (solverNode*& a : n->adjNodes)
        {
            if (a->discovered || a->flagged)
                continue;

            if (n->adjBombs - flaggedOptions == 0)
            {
                noBombNodes.push(a);
                a->discovered = true;
                continue;
            }

            if ((n->adjBombs - flaggedOptions) == validOptions)
            {
                flagged.push_back(coord(a->x, a->y));
                a->flagged = true;
                bombCount--;
                newFlags++;
            }
        }
    }
}

void solver::printMap()
{
    std::string output = "";
    int currY = 0;

    for (solverNode* n : nodes)
    {
        if (currY != n->y)
        {
            currY = n->y;
            output += '\n';
        }

        if (n->visited && !n->discovered && !n->flagged)
            output += 'a' + n->group;
        else if (n->visited && !n->flagged)
        {
            int flagged = 0;
            for (solverNode* a : n->adjNodes)
                if (a->flagged)
                    flagged++;
            output += '0' + n->adjBombs - flagged;
        }
        else if (!n->discovered && !n->flagged)
            output += '-';
        else
            output += ' ';
        output += ' ';
    }

    std::cout << output << std::endl;
}

solver::solver()
{
    amountOfGuesses = 0;
    clickX = 1;
    clickY = 1;

    for (int i = 0; i < SIZEY; i++)
        for (int j = 0; j < SIZEX; j++)
        {
            solverNode* n = new solverNode(j, i);
            nodes.push_back(n);
        }

    int offset[8][2] = {{-1, 1},  {0, 1},  {1, 1}, 
                        {-1, 0},           {1, 0}, 
                        {-1, -1}, {0, -1}, {1, -1}};

    for (solverNode* n : nodes)
        for (int i = 0; i < 8; i++)
        {
            solverNode* adjNode = searchNode(n->x + offset[i][0], n->y + offset[i][1]);

            if (!adjNode)
                continue;
            
            n->adjNodes.push_back(adjNode);
        }
}

solver::~solver()
{
    for (solverNode* n : nodes)
        delete n;
}