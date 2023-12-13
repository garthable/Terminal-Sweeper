#include "solverPrivate.cpp"

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

solver::solver(const unsigned short& sizeX, const unsigned short& sizeY)
{
    m_sizeX = sizeX;
    m_sizeY = sizeY;

    m_amountOfGuesses = 0;
    m_clickX = 1;
    m_clickY = 1;

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
}

solver::~solver()
{
    for (solverNode* n : m_nodes)
        delete n;
}