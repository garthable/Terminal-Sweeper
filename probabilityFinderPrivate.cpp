#include "probabilityFinderUtil.cpp"
#include "probabilityFinder.h"

numberedNode* probabilityFinder::searchNumbered(const unsigned short& solutionNodeIndex)
{
    unsigned short maxGroup = m_numberedNodesGrouped.size();
    for (unsigned short group = 0; group < maxGroup; group++)
    {
        unsigned short numberedNodeListSize = m_numberedNodesGrouped[group].size();
        for (unsigned short g = 0; g < numberedNodeListSize; g++)
            if (m_numberedNodesGrouped[group][g]._solutionNodeIndex == solutionNodeIndex)
                return &m_numberedNodesGrouped[group][g];
    }

    return nullptr;
}

unknownNode* probabilityFinder::searchUnknown(const unsigned short& solutionNodeIndex)
{
    unsigned short maxGroup = m_unknownNodesGrouped.size();
    for (unsigned short group = 0; group < maxGroup; group++)
    {
        unsigned short unknownNodeListSize = m_unknownNodesGrouped[group].size();
        for (unsigned short g = 0; g < unknownNodeListSize; g++)
            if (m_unknownNodesGrouped[group][g]._solutionNodeIndex == solutionNodeIndex)
                return &m_unknownNodesGrouped[group][g];
    }

    return nullptr;
}

void probabilityFinder::sortNumbered(const unsigned short& group, std::vector<unknownNode>& unknownNodeList)
{
    std::vector<numberedNode> clonedNumberNodeList = m_numberedNodesGrouped[group];
    std::vector<numberedNode> sortedNumberNodeList;
    sortedNumberNodeList.reserve(unknownNodeList.size());
    
    unsigned short numberedNodeGroupedSize = m_numberedNodesGrouped[group].size();
    while (numberedNodeGroupedSize != sortedNumberNodeList.size())
    {
        unsigned short minCombinationSize = 999;
        numberedNode minCombinationNode = numberedNode(-1, -1);

        for (const numberedNode& numNode : clonedNumberNodeList)
        {
            std::vector<unsigned short> childNodes;
            for (unsigned short unknownNodeIndex : numNode._attached)
                if (!unknownNodeList[unknownNodeIndex]._visited)
                    childNodes.push_back(unknownNodeIndex);
            
            unsigned short combinationSize = combinationValueHardcoded(childNodes, numNode._adjBombAmount);
            if (minCombinationSize > combinationSize)
            {
                minCombinationSize = combinationSize;
                minCombinationNode = numNode;
            }
        }
        unsigned short clonedNumberedSize = clonedNumberNodeList.size();
        for (unsigned short clonedNumberNodeIndex = 0; clonedNumberNodeIndex < clonedNumberedSize; clonedNumberNodeIndex++)
            if (clonedNumberNodeList[clonedNumberNodeIndex]._solutionNodeIndex == minCombinationNode._solutionNodeIndex)
            {
                clonedNumberNodeList.erase(clonedNumberNodeList.begin() + clonedNumberNodeIndex);
                break;
            }
        for (unsigned short unknownNodeIndex : minCombinationNode._attached)
            unknownNodeList[unknownNodeIndex]._visited = true;
        sortedNumberNodeList.push_back(minCombinationNode);
    }

    for (unknownNode& unNode : unknownNodeList)
        unNode._visited = false;

    m_numberedNodesGrouped[group] = sortedNumberNodeList;
}

bool probabilityFinder::isValid(const std::vector<numberedNode>& numberedList, const std::vector<unknownNode>& unknownList)
{
    for(const numberedNode& numNode : numberedList)
    {
        unsigned short bombCount = 0;
        for (const unsigned short& attachedIndex : numNode._attached)
            if (unknownList[attachedIndex]._isBomb)
                bombCount++;
        if (bombCount != numNode._adjBombAmount)
            return false;
    }
    return true;
}

void probabilityFinder::getSolutionsHelper(unsigned short index, const std::vector<numberedNode>& numberedList, 
                                    std::vector<unknownNode> unknownList, std::vector<std::vector<bool>>& outBombLayouts)
{       
    if (index == numberedList.size()) //pass numberedList size into function to reduce calls to size
    {
        if (!isValid(numberedList, unknownList))
            return;

        std::vector<bool> solution;
        solution.reserve(unknownList.size());

        unsigned short unknownNodeListSize = unknownList.size();
        for (unsigned short unknownNodeListIndex = 0; unknownNodeListIndex < unknownNodeListSize; unknownNodeListIndex++)
            solution.push_back(unknownList[unknownNodeListIndex]._isBomb);

        outBombLayouts.push_back(solution);
        return;
    }

    numberedNode currNumberedNode = numberedList[index];
    unsigned short bombCount = 0;
    std::vector<unsigned short> childIndexes;
    childIndexes.reserve(currNumberedNode._attached.size());

    unsigned short attachedSize = currNumberedNode._attached.size();
    for (unsigned short attachedIndex = 0; attachedIndex < attachedSize; attachedIndex++)
    {
        unsigned short unknownNodeIndex = currNumberedNode._attached[attachedIndex];
        unknownNode& unNode = unknownList[unknownNodeIndex];
        if (unNode._isBomb)
            bombCount++;
        else if (!unNode._visited)
        {
            childIndexes.push_back(unknownNodeIndex);
            unNode._visited = true;
        }
    }

    unsigned short adjBombAmount = currNumberedNode._adjBombAmount - bombCount;

    if (adjBombAmount > childIndexes.size())
        return;
    else if (adjBombAmount == 0)
    {
        getSolutionsHelper(index + 1, numberedList, unknownList, outBombLayouts);
        return;
    }

    combinationHardcoded(childIndexes, adjBombAmount, currNumberedNode._combinations);
    
    unsigned short combinationSize = currNumberedNode._combinations.size();
    for (unsigned short i = 0; i < combinationSize; i++)
    {
        std::vector<unknownNode> unknownListClone = unknownList;

        unsigned short combinationsSize = currNumberedNode._combinations[i].size();
        for (unsigned short combinationIndex = 0; combinationIndex < combinationsSize; combinationIndex++)
        {
            unsigned short unknownListIndex = currNumberedNode._combinations[i][combinationIndex];
            unknownListClone[unknownListIndex]._isBomb = true;
        }

        getSolutionsHelper(index + 1, numberedList, unknownListClone, outBombLayouts);
    }
}

std::vector<std::vector<bool>> probabilityFinder::getSolutions(const int& group)
{
    sortNumbered(group, m_unknownNodesGrouped[group]);
    std::vector<std::vector<bool>> solutions;
    for (unknownNode& unNode : m_unknownNodesGrouped[group])
    {
        unNode._isBomb = false;
        unNode._visited = false;
    }
    getSolutionsHelper(0, m_numberedNodesGrouped[group], m_unknownNodesGrouped[group], solutions);
    return solutions;
}

void probabilityFinder::findSafePicksFast(const std::vector<std::vector<std::vector<bool>>>& bombLayouts)
{
    unsigned short numberedSize = m_numberedNodesGrouped.size();
    for (unsigned short group = 0; group < numberedSize; group++)
    {
        std::vector<std::vector<bool>> sol = bombLayouts[group];

        std::vector<probData> bombChances;

        unsigned short length = sol[0].size();
        bombChances.reserve(length);
        for (unsigned short i = 0; i < length; i++)
            bombChances.push_back(probData(m_unknownNodesGrouped[group][i]._solutionNodeIndex, 0));

        for (const std::vector<bool>& v : sol)
        {
            unsigned short vectorSize = v.size();
            for (unsigned short i = 0; i < vectorSize; i++)
                bombChances[i]._probability += v[i];
        }

        m_probabilities.reserve(bombChances.size());
        for (probData& p : bombChances)
        {
            p._probability /= sol.size();
            m_probabilities.push_back(p);
        }   
    }
}

void probabilityFinder::findSafePicksAccountingForBombCount(const std::vector<std::vector<std::vector<bool>>>& bombLayouts)
{
    std::vector<std::vector<bool>> sol = combineAll(bombLayouts, m_remainingBombs);

    if (sol.size() == 0)
        return;
    unsigned int length = sol[0].size();

    unsigned short j = 0;
    unsigned short group = 0;
    std::vector<unknownNode> unknownList = m_unknownNodesGrouped[group];
    unsigned short unknownSize = unknownList.size();
    m_probabilities.reserve(length);
    for (unsigned int i = 0; i < length; i++)
    {
        if (j == unknownList.size())
        {
            j = 0;
            group++;
            unknownList = m_unknownNodesGrouped[group];
            unknownSize = unknownList.size();
        }
        m_probabilities.push_back(probData(unknownList[j]._solutionNodeIndex, 0));
        j++;
    }

    for (const std::vector<bool>& v : sol)
        for (unsigned int i = 0; i < length; i++)
            m_probabilities[i]._probability += v[i];
    float solSize = sol.size();
    for (probData& p : m_probabilities)
        p._probability /= solSize;
}

float probabilityFinder::calcAverageBombs(const std::vector<std::vector<std::vector<bool>>>& layouts)
{
    if (layouts.size() == 0)
        return 0;
    float returnVal = 0;
    for (const std::vector<std::vector<bool>>& v : layouts)
        returnVal += calcAverageBombs(v);
    return returnVal/layouts.size();
}

float probabilityFinder::calcAverageBombs(const std::vector<std::vector<bool>>& layouts)
{
    if (layouts.size() == 0)
        return 0;
    float returnVal = 0;
    for (const std::vector<bool>& v : layouts)
        returnVal += (float)getBombCount(v);
    return returnVal/layouts.size();
}