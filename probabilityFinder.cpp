#include "probabilityFinderPrivate.cpp"

void probabilityFinder::addNumbered(const unsigned short& solutionNodeIndex, const unsigned short& group, 
                                    const unsigned short& adjBombAmount)
{
    if (searchNumbered(solutionNodeIndex))
        return;

    unsigned short groupSize = group + 1;
    while (m_numberedNodesGrouped.size() < groupSize) 
        m_numberedNodesGrouped.push_back(std::vector<numberedNode>());

    m_numberedNodesGrouped[group].push_back(numberedNode(solutionNodeIndex, adjBombAmount));
    m_adjBombSum += adjBombAmount;
}

void probabilityFinder::addUnknown(const unsigned short& solutionNodeIndex, const unsigned short& group, 
                                   const unsigned short& parentSolutionNodeIndex)
{
    unknownNode* unNode = searchUnknown(solutionNodeIndex);
    numberedNode* parentNumNode  = searchNumbered(parentSolutionNodeIndex);

    if (!parentNumNode)
        return;

    if (!unNode)
    {
        unsigned short groupSize = group + 1;
        while (m_unknownNodesGrouped.size() < groupSize) 
            m_unknownNodesGrouped.push_back(std::vector<unknownNode>());

        m_unknownNodesGrouped[group].push_back(unknownNode(solutionNodeIndex));
        m_unknownNodeAmount++;
        unsigned short endOfVectorIndex = m_unknownNodesGrouped[group].size() - 1;
        unNode = &m_unknownNodesGrouped[group][endOfVectorIndex];
    }

    for (unsigned short index = 0; index < m_unknownNodesGrouped[group].size(); index++)
        if (m_unknownNodesGrouped[group][index]._solutionNodeIndex == unNode->_solutionNodeIndex)
        {
            parentNumNode->_attached.push_back(index);
            return;
        }
}

std::vector<probData> probabilityFinder::getProbdata()
{
    return m_probabilities;
}

float probabilityFinder::getAverageAmountOfBombsUsed()
{
    return m_averageAmountOfBombsUsed;
}

unsigned short probabilityFinder::getMinAmountOfBombsUsed()
{
    return m_minAmountOfBombsUsed;
}

unsigned short probabilityFinder::getUnknownCount()
{
    return m_unknownNodeAmount;
}

void probabilityFinder::findSafePicks()
{
    std::vector<std::vector<std::vector<bool>>> bombLayouts;
    unsigned short maxGroup = m_numberedNodesGrouped.size();
    for (unsigned short group = 0; group < maxGroup; group++)
    {
        std::vector<std::vector<bool>> sol = getSolutions(group);
        bombLayouts.push_back(sol);
    }

    m_minAmountOfBombsUsed = findMinAmountBetweenVectors(bombLayouts);

    if (m_adjBombSum > m_remainingBombs && m_unknownNodeAmount > m_remainingBombs 
        && (findMaxAmountBetweenVectors(bombLayouts) > m_remainingBombs))
    {
        findSafePicksAccountingForBombCount(bombLayouts);
        return;
    }
    findSafePicksFast(bombLayouts);
}

probabilityFinder::probabilityFinder(int remainingBombs)
{
    m_remainingBombs = remainingBombs;
    m_adjBombSum = 0;
    m_unknownNodeAmount = 0;
    m_averageAmountOfBombsUsed = 0;
    m_minAmountOfBombsUsed = 0;
}