#include "solverPrivateGrouping.cpp"

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
            std::cout << "null at: " << x << " " << y <<std::endl;
            return;
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
        b.addNumbered(n->x + SIZEX*n->y, n->group, n->adjBombs-flaggedAmount[i]);
        for (const unsigned short index : n->adjNodes)
        {
            solverNode*& a = m_nodes[index];
            if (a->discovered || a->flagged)
                continue;
            
            b.addUnknown(a->x + SIZEX*a->y, a->group, n->x + SIZEX*n->y);
        }
    }

    b.findSafePicks();

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
    float minReplace = ((float)m_bombCount/(float)m_undiscoveredCount);

    for (solverNode*& n : m_nodes)
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

    m_amountOfGuesses++;
    m_clickX = min->x;
    m_clickY = min->y;
}

inline int solver::searchNode(const unsigned short& x, const unsigned short& y)
{
    if (x >= SIZEX || y >= SIZEY || x < 0 || y < 0)
        return -1;
    return x + (y*SIZEX);
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