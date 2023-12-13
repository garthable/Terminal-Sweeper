#include "mineMapPrivate.cpp"

void mineMap::reset()
{
    m_bombCount = 0;
    for (node& n : m_nodes)
    {
        n.isRevealed = false;
        n.isBomb = false;
        n.isFlagged = false;
        n.adjBombCount = 0;
    }
}

void mineMap::setSeed(const unsigned int& _seed)
{
    m_seed = _seed;
}

void mineMap::generateBombs(const unsigned short& x, const unsigned short& y)
{
    reset();
    srand(m_seed);
    
    while (m_bombCount != bombCount)
    {
        int randomIndex = rand() % m_nodes.size();
        node& n = m_nodes[randomIndex];
        if (n.isBomb || (abs(n.x - x) < 3 && abs(n.y - y) < 3))
            continue;
        n.isBomb = true;
        m_bombCount++;
    }

    for (node& n : m_nodes)
    {
        unsigned short bombs = 0;
        short x = n.x;
        short y = n.y;

        for (const unsigned short& i : n.adjNodes)
            if (m_nodes[i].isBomb)
                bombs++;

        n.adjBombCount = bombs;
    }
}

void mineMap::flag(const unsigned short& x, const unsigned short& y)
{
    int index = searchNode(x, y);
    if (index == -1)
        assert(false);

    node& flaggedNode = m_nodes[index];

    if (!flaggedNode.isBomb)
    {
        std::cout << "Wrong flag at: " << x << " " << y << std::endl;
        exit(0);
    }

    if (!flaggedNode.isFlagged)
        m_bombCount--;
    flaggedNode.isFlagged = true;
}

bool mineMap::click(const unsigned short& x, const unsigned short& y)
{
    int index = searchNode(x, y);
    if (index == -1)
        assert(false);

    node& clickedNode = m_nodes[index];

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
    for (const node& n : m_nodes)
        if (!n.isBomb && !n.isRevealed)
            return false;
    return true;
}

std::string mineMap::print()
{
    std::string output = "";
    int currY = 0;

    output += "Flags: "; 
    output += std::to_string(m_bombCount);
    output += '\n';

    for (const node& n : m_nodes)
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
    output += std::to_string(m_bombCount);
    output += '\n';

    for (const node& n : m_nodes)
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

mineMap::mineMap(const unsigned int& _seed, const difficulty& _difficulty)
{
    switch (_difficulty)
    {
    case beginner:
        sizeX = 9;
        sizeY = 9;
        bombCount = 10;
        break;

    case intermediate:
        sizeX = 16;
        sizeY = 16;
        bombCount = 40;
        break;

    case expert:
        sizeX = 30;
        sizeY = 16;
        bombCount = 99;
        break;
    
    default:
        sizeX = 1;
        sizeY = 1;
        bombCount = 1;
        break;
    }

    m_seed = _seed;
    m_bombCount = -1;
    for (int y = 0; y < sizeY; y++)
        for (int x = 0; x < sizeX; x++)
        {
            node n = node(x, y);
            m_nodes.push_back(n);
        }

    int offset[8][2] = {{-1, 1},  {0, 1},  {1, 1}, 
                        {-1, 0},           {1, 0}, 
                        {-1, -1}, {0, -1}, {1, -1}};

    for (node& n : m_nodes)
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