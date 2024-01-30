#include "../include/solver.h"
#include <iostream>

void solver::update(const std::string& input)
{
    if (bombsInStack())
        return;

    readMineMap(input);

    getEasyNoBombs();

    if (bombsInStack())
        return;

    getProbabilities();

    if (bombsInStack())
        return;

    chooseNextClick();
}

void solver::reset()
{
    for (solverNode*& n : m_nodes)
    {
        n->weight = -1;
        n->adjBombs = 0;
        n->group = 0;
        n->flagged = false;
        n->discovered = false;
        n->nextToFlag = false;
        n->visited = false;
    }
    m_flagged.clear();
    while(!m_noBombNodes.empty())
        m_noBombNodes.pop();
    m_clickX = 1;
    m_clickY = 1;
    m_bombCount = 0;
    m_undiscoveredCount = 0;
    m_amountOfGuesses = 0;

    m_averageBombsUsed = 0;
    m_undiscoveredUsed = 0;
    m_minAmountOfBombsUsed = 0;
}

unsigned short solver::getClickX()
{
    return m_clickX;
}

unsigned short solver::getClickY()
{
    return m_clickY;
}

std::vector<coord> solver::getFlagged()
{
    return m_flagged;
}

unsigned short solver::getGuesses()
{
    return m_amountOfGuesses;
}

solver::solver(const unsigned short& sizeX, const unsigned short& sizeY, const unsigned short& safeRadius)
{
    m_sizeX = sizeX;
    m_sizeY = sizeY;

    m_amountOfGuesses = 0;
    m_clickX = safeRadius/2;
    m_clickY = safeRadius/2;

    for (int i = 0; i < m_sizeY; i++)
        for (int j = 0; j < m_sizeX; j++)
        {
            solverNode* n = new solverNode(j, i);
            m_nodes.push_back(n);
        }

    int offset[8][2] = {{-1, 1},  {0, 1},  {1, 1}, 
                        {-1, 0},           {1, 0}, 
                        {-1, -1}, {0, -1}, {1, -1}};

    for (solverNode* n : m_nodes)
        for (int i = 0; i < 8; i++)
        {
            int index = searchNode(n->x + offset[i][0], n->y + offset[i][1]);

            if (index == -1)
                continue;
            
            n->adjNodes.push_back(index);
        }
    assignDistance();
}

solver::~solver()
{
    for (solverNode* n : m_nodes)
        delete n;
}

//
// Private:
//

bool solver::bombsInStack()
{
    if (!m_noBombNodes.empty())
    {
        solverNode* top = m_noBombNodes.top();
        m_clickX = top->x;
        m_clickY = top->y;
        m_noBombNodes.pop();
        return true;
    }
    return false;
}

void solver::readMineMap(const std::string& input)
{
    bool firstLine = true;
    unsigned short x = 0;
    unsigned short y = 0;
    unsigned short i = 0;

    m_bombCount = 0;
    std::string bombStr = "";
    m_undiscoveredCount = 0;
    for (const char& c : input)
    {
        if (firstLine)
        {
            if (isdigit(c))
                bombStr += c;
            if (c == '\n')
            {
                m_bombCount = stoi(bombStr);
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

        solverNode* n = m_nodes[i];

        if (!n)
        {
            throw std::runtime_error("Read minemap error: Null at " + std::to_string(x) + " " + std::to_string(y));
        }

        if (c == '#' || c == '@')
        {
            if (c == '#')
                m_undiscoveredCount++;
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

void solver::getEasyNoBombs()
{
    unsigned short newFlags = 0;

    newFlags = 0;
    for (solverNode*& n : m_importantNodes)
    {
        unsigned short flaggedOptions = 0;
        unsigned short validOptions = 0;

        for (const unsigned short& index : n->adjNodes)
        {
            solverNode*& a = m_nodes[index];
            if (a->discovered)
                continue;
            else if (a->flagged)
                flaggedOptions++;
            else
                validOptions++;
        }

        for (const unsigned short& index : n->adjNodes)
        {
            solverNode*& a = m_nodes[index];
            if (a->discovered || a->flagged)
                continue;

            if (n->adjBombs - flaggedOptions == 0)
            {
                m_noBombNodes.push(a);
                a->discovered = true;
                continue;
            }

            if ((n->adjBombs - flaggedOptions) == validOptions)
            {
                m_flagged.push_back(coord(a->x, a->y));
                a->flagged = true;
                m_bombCount--;
                newFlags++;
            }
        }
    }
}

void solver::getProbabilities()
{
    probabilityFinder b = probabilityFinder(m_bombCount);
    
    std::vector<solverNode*> numNodes;
    std::vector<solverNode*> set;
    std::vector<unsigned short> flaggedAmount;

    for(solverNode*& n : m_importantNodes)
    {   
        for (const unsigned short& index : n->adjNodes)
        {
            solverNode*& a = m_nodes[index];
            if (!a->discovered && !a->flagged)
            {
                numNodes.push_back(n);
                set.push_back(n);
                flaggedAmount.push_back(0);
                break;
            }
        }
    }

    unsigned short numNodesSize = numNodes.size();
    for(unsigned short i = 0; i < numNodesSize; i++)
    {   
        solverNode* n = numNodes[i];
        for (const unsigned short& index : n->adjNodes)
        {
            solverNode*& a = m_nodes[index];
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
        b.addNumbered(n->x + m_sizeX*n->y, n->group, n->adjBombs-flaggedAmount[i]);
        for (const unsigned short index : n->adjNodes)
        {
            solverNode*& a = m_nodes[index];
            if (a->discovered || a->flagged)
                continue;
            
            b.addUnknown(a->x + m_sizeX*a->y, a->group, n->x + m_sizeX*n->y);
        }
    }

    b.findSafePicks();

    m_minAmountOfBombsUsed = b.getMinAmountOfBombsUsed();
    m_undiscoveredUsed = b.getUnknownCount();

    std::vector<probData> probabilities = b.getProbdata();

    for (const probData& prob : probabilities)
    {
        solverNode* n = m_nodes[prob._solutionNodeIndex];
        float p = prob._probability;

        if (p == 0)
            m_noBombNodes.push(n);
        else if (p == 1)
        {
            n->flagged = true;
            m_flagged.push_back(coord(n->x, n->y));
        }
        else if (p != -1)
            n->weight = p;
    }
}

void solver::chooseNextClick()
{
    solverNode* min = nullptr;
    float minWeight = (float)10000;
    unsigned short trueBombCount = m_bombCount - m_minAmountOfBombsUsed;
    unsigned short trueUndiscoveredCount = m_undiscoveredCount - m_undiscoveredUsed;
    float minReplace = ((float)trueBombCount/(float)trueUndiscoveredCount);

    if (trueUndiscoveredCount == 0)
        minReplace = 0;
    if (minReplace > 1)
        minReplace = 1;

    for (solverNode*& n : m_nodes)
    {
        if (n->discovered || n->flagged)
            continue;

        float weight = n->weight;

        if (n->weight == -1)
        {
            weight = minReplace;
            // if (n->nextToFlag)
            //     weight += 0.05;
        }
        
        if (minWeight > weight)
        {
            minWeight = weight;
            min = n;
        }
        else if (minWeight == weight)
        {
            if (!min)
            {
                throw std::runtime_error("\"min\" variable in chooseClick was null when called in minWeight == weight if statement");
            }
            if (min->distFromCenterWeight < n->distFromCenterWeight)
            {
                minWeight = weight;
                min = n;
            }
        }
    }

    if (!min)
    {
        throw std::runtime_error("ERROR NO MIN FOUND IN chooseNextClick");
    }

    m_amountOfGuesses++;
    if (m_clickX == min->x && m_clickY == min->y)
    {
        throw std::runtime_error("ERROR REPEAT CLICK IN chooseNextClick");
    }
    m_clickX = min->x;
    m_clickY = min->y;
}

void solver::getImportantNodes()
{
    m_importantNodes.clear();
    for (solverNode*& n : m_nodes)
    {
        if (n->flagged || !n->discovered || n->adjBombs == 0)
            continue;
        
        for (const unsigned short& index : n->adjNodes)
        {
            solverNode*& a = m_nodes[index];
            if (!a->discovered && !a->flagged)
            {
                m_importantNodes.push_back(n);
                break;
            }
        }
    }
}

void solver::assignDistance()
{
    unsigned short centerX = m_sizeX/2;
    for(solverNode* n : m_nodes)
    {
        if (n->adjNodes.size() == 3)
        {
            n->distFromCenterWeight = m_sizeX + m_sizeY + 1;
            continue;
        }
        else if (n->adjNodes.size() == 5)
        {
            n->distFromCenterWeight = m_sizeX + m_sizeY;
            continue;
        }
        unsigned short distX = abs(n->x - centerX);
        unsigned short distY = abs(n->x - centerX);
        n->distFromCenterWeight = distX + distY;
    }
}

void solver::printMap()
{
    std::string output = "";
    int currY = 0;

    for (solverNode* n : m_nodes)
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
            for (const unsigned short& index : n->adjNodes)
                if (m_nodes[index]->flagged)
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

void solver::DFSHelper(solverNode*& curr, const unsigned short& group, std::vector<solverNode*>& set)
{
    curr->visited = true;
    curr->group = group;

    for (const unsigned short& index : curr->adjNodes)
    {
        solverNode*& n = m_nodes[index];
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
    for (solverNode*& n : m_nodes)
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
    for (const unsigned short& index1 : n1->adjNodes)
    {
        solverNode*& a1 = m_nodes[index1];
        for (const unsigned short& index2 : n2->adjNodes)
        {
            solverNode*& a2 = m_nodes[index2];
            for (solverNode*& s : set)
                if (a1->discovered && a1 == a2 && a1 == s)
                    return true;  
        }
    }
    return false;
}