#include "solver.h"
// #include "incongruency.cpp"
// #include "util.h"
#include <iostream>
#include <math.h>
#include <unistd.h>

solverNode* solver::searchNode(int x, int y)
{
    for (solverNode* n : nodes)
        if (n->x == x && n->y == y)
            return n;
    return nullptr;
}
solverNode* solver::searchNode(int val)
{
    return nodes[val];
}

std::vector<coord> solver::getFlagged()
{
    return flagged;
}

int solver::getGuesses()
{
    return amountOfGuesses;
}

int solver::getClickX()
{
    return clickX;
}

int solver::getClickY()
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

void solver::update(std::string input)
{
    if (bombsInStack())
        return;

    readMineMap(input);

    getEasyNoBombs();

    if (bombsInStack())
        return;

    runBruteForce();
    getEasyNoBombs();

    // std::string a;
    // std::cin >> a;

    if (bombsInStack())
        return;

    updateWeights();
    chooseNextClick();
}

void solver::reset()
{
    for (solverNode* n : nodes)
    {
        n->elements = 0;
        n->sum = 0;
        n->adjBombs = 0;
        n->group = 0;
        n->flagged = false;
        n->discovered = false;
        n->nextToFlag = false;
        n->visited = false;
    }
    flagged.clear();
    meaningfulNodes.clear();
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
    // srand(time(0));
    solverNode* min = nullptr;
    float minWeight = (float)10000;
    float minReplace = ((float)bombCount/(float)undiscoveredCount) + 0.25F;

    for (solverNode* n : nodes)
    {
        if (n->discovered || n->flagged)
            continue;

        float weight = (n->sum/(float)n->elements);

        if (n->elements == 0)
        {
            weight = minReplace;
            if (n->nextToFlag)
                weight += 0.05;
        }

        if (weight == 0)
            weight = minReplace;
        
        if (minWeight > weight)
        {
            minWeight = weight;
            min = n;
        }
        else if (minWeight == weight && n->elements < min->elements)
        {
            minWeight = weight;
            min = n;
        }
    }

    if (!min)
    {
        // std::cout << "null min!" << std::endl;
        return;
    }

    amountOfGuesses++;
    clickX = min->x;
    clickY = min->y;
}

void solver::readMineMap(std::string input)
{
    bool firstLine = true;
    int x = 0;
    int y = 0;
    int i = 0;

    bombCount = 0;
    std::string bombStr = "";
    undiscoveredCount = 0;
    for (char c : input)
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

        n->sum = 0.0F;
        n->elements = 0;

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
}

void solver::DFSHelper(solverNode* curr, int group, std::vector<solverNode*> set)
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

        for (solverNode* compare : set)
            if (n == compare)
                shouldContinue = false;

        if (shouldContinue)
            continue;

        DFSHelper(n, group, set);
    }
}
void solver::DFSGrouping(std::vector<solverNode*> set)
{
    int group = 0;
    for (solverNode* n : set)
    {
        n->visited = false;
        n->group = 0;
    }

    for (solverNode* curr : set)
    {
        if (curr->visited)
            continue;

        DFSHelper(curr, group, set);
        group++;
    }
    // std::cout << "Groups: " << group << std::endl;
}

void solver::runBruteForce()
{
    bruteForce b;
    
    std::vector<solverNode*> numNodes;
    std::vector<solverNode*> set;
    std::vector<int> flaggedAmount;

    for(solverNode* n : nodes)
    {
        if (!n->discovered || n->adjBombs == 0)
            continue;
        
        for (solverNode* a : n->adjNodes)
            if (!a->discovered && !a->flagged)
            {
                numNodes.push_back(n);
                set.push_back(n);
                flaggedAmount.push_back(0);
                break;
            }
    }

    for(int i = 0; i < numNodes.size(); i++)
    {   
        solverNode* n = numNodes[i];
        for (solverNode* a : n->adjNodes)
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
    // printMap();

    for (int i = 0; i < numNodes.size(); i++)
    {
        solverNode* n = numNodes[i];
        b.addNumbered(n->x + SIZEX*n->y, n->group, n->adjBombs-flaggedAmount[i]);
        for (solverNode* a : n->adjNodes)
        {
            if (a->discovered || a->flagged)
                continue;
            
            b.addUnknown(a->x + SIZEX*a->y, a->group, n->x + SIZEX*n->y);
        }
    }

    b.findSafePicks2();

    std::vector<int> bombs = b.getBombs();
    std::vector<int> notBombs = b.getNotBombs();

    for (int a : bombs)
    {
        solverNode* n = searchNode(a);
        if (!n)
        {
            std::cout << "Null Bomb" << std::endl;
            exit(0);
        }
        // std::cout << "Bomb at: " << n->x << " " << n->y << std::endl;
        n->flagged = true;
        flagged.push_back(coord(n->x, n->y));
    }
    for (int a : notBombs)
    {
        solverNode* n = searchNode(a);
        if (!n)
        {
            std::cout << "Null Not Bomb" << std::endl;
            exit(0);
        }
        // std::cout << "Not bomb at: " << n->x << " " << n->y << std::endl;
        noBombNodes.push(n);
    }
}

void solver::getEasyNoBombs()
{
    int newFlags = 0;
    do 
    {
        newFlags = 0;
        for (solverNode* n : nodes)
        {
            if (!n->discovered || n->adjBombs == 0)
                continue;

            int flaggedOptions = 0;
            int validOptions = 0;

            for (solverNode* a : n->adjNodes)
            {
                if (a->discovered)
                    continue;
                if (a->flagged)
                    flaggedOptions++;
                else
                    validOptions++;
            }

            for (solverNode* a : n->adjNodes)
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
    while (newFlags != 0);
}

void solver::updateWeights()
{
    for (solverNode* n : nodes)
    {
        if ((!n->discovered && !n->flagged)|| n->adjBombs == 0)
            continue;

        int flaggedOptions = 0;
        int validOptions = 0;

        for (solverNode* a : n->adjNodes)
        {
            if (a->discovered || a->flagged)
                continue;

            if (a->flagged)
                flaggedOptions++;
            else
                validOptions++;
        }

        float prob = (float)(n->adjBombs - flaggedOptions)/(float)validOptions;
        if (n->flagged)
            prob = 0;

        if (validOptions == 0)
            prob = 0;

        for (solverNode* a : n->adjNodes)
        {
            if (a->discovered || a->flagged)
                continue;
            
            if (n->flagged)
            {
                a->nextToFlag = true;
                continue;
            }

            a->sum += prob;
            if (prob != 0.05F)
                a->elements++;
        }
    }
}

void solver::printMap()
{
    std::string output = "";
    int currY = 0;

    // output += "Flags: "; 
    // output += std::to_string(bombCount);
    // output += '\n';

    for (solverNode* n : nodes)
    {
        if (currY != n->y)
        {
            currY = n->y;
            output += '\n';
        }

        if (n->visited && !n->discovered && !n->flagged)
            output += '0' + n->group;
        else if (n->visited && !n->flagged)
            output += 'A';
        else if (!n->discovered && !n->flagged)
            output += '#';
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