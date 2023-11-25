#include "bruteForceLogic.h"
#include "util.h"

numberedNode* bruteForce::searchNumbered(const unsigned short& iD)
{
    unsigned short numberedSize = numbered.size();
    for (unsigned short group = 0; group < numberedSize; group++)
    {
        unsigned short groupSize = numbered[group].size();
        for (unsigned short g = 0; g < groupSize; g++)
            if (numbered[group][g].iD == iD)
                return &numbered[group][g];
    }

    return nullptr;
}

unknownNode* bruteForce::searchUnknown(const unsigned short& iD)
{
    unsigned short unknownsSize = unknowns.size();
    for (unsigned short group = 0; group < unknownsSize; group++)
    {
        unsigned short groupSize = unknowns[group].size();
        for (unsigned short g = 0; g < groupSize; g++)
            if (unknowns[group][g].iD == iD)
                return &unknowns[group][g];
    }

    return nullptr;
}

void bruteForce::addNumbered(const unsigned short& iD, const unsigned short& group, const unsigned short& number)
{
    if (searchNumbered(iD))
        return;

    while (numbered.size() < group + 1) 
        numbered.push_back(std::vector<numberedNode>());

    numbered[group].push_back(numberedNode(iD, number));
    numberCount += number;
}

void bruteForce::addUnknown(const unsigned short& iD, const unsigned short& group, const unsigned short& parentId)
{
    unknownNode* unNode = searchUnknown(iD);
    numberedNode* numNode  = searchNumbered(parentId);

    if (!numNode)
        return;

    if (!unNode)
    {
        while (unknowns.size() < group + 1) 
            unknowns.push_back(std::vector<unknownNode>());

        unknowns[group].push_back(unknownNode(iD));
        unknownCount++;
        unNode = &unknowns[group][unknowns[group].size() - 1];
    }

    for (unsigned short index = 0; index < unknowns[group].size(); index++)
        if (unknowns[group][index].iD == unNode->iD)
        {
            numNode->attached.push_back(index);
            return;
        }
}

void bruteForce::sortNumbered(const unsigned short& group, std::vector<unknownNode>& unknownList)
{
    std::vector<numberedNode> clonedNumbered = numbered[group];
    std::vector<numberedNode> sortedList;
    sortedList.reserve(unknownList.size());
    
    while (numbered[group].size() != sortedList.size())
    {
        unsigned short min = 999;
        numberedNode minNode = numberedNode(-1, -1);

        for (const numberedNode& n : clonedNumbered)
        {
            std::vector<unsigned short> childNodes;
            for (unsigned short i : n.attached)
                if (!unknownList[i].visited)
                    childNodes.push_back(i);
            
            unsigned short val = combinationValueHardcoded(childNodes, n.number);
            if (min > val)
            {
                min = val;
                minNode = n;
            }
        }
        unsigned short clonedNumberedSize = clonedNumbered.size();
        for (unsigned short i = 0; i < clonedNumberedSize; i++)
            if (clonedNumbered[i].iD == minNode.iD)
            {
                clonedNumbered.erase(clonedNumbered.begin() + i);
                break;
            }
        for (unsigned short i : minNode.attached)
            unknownList[i].visited = true;
        sortedList.push_back(minNode);
    }

    for (unknownNode& u : unknownList)
        u.visited = false;

    numbered[group] = sortedList;
}

bool bruteForce::isValid(const std::vector<numberedNode>& numberedList, const std::vector<unknownNode>& unknownList)
{
    unsigned short totalCount = 0;
    for(const numberedNode& n : numberedList)
    {
        unsigned short count = 0;
        for (const unsigned short& i : n.attached)
            if (unknownList[i].isBomb)
                count++;
        if (count != n.number)
            return false;
    }
    return true;
}

void bruteForce::getSolutionsHelper(unsigned short index, const std::vector<numberedNode>& numberedList, 
                                    std::vector<unknownNode> unknownList, std::vector<std::vector<bool>>& out)
{       
    if (index == numberedList.size())
    {
        if (!isValid(numberedList, unknownList))
            return;

        std::vector<bool> solution;
        solution.reserve(unknownList.size());
        for (const unknownNode& u : unknownList)
            solution.push_back(u.isBomb);
        out.push_back(solution);
        return;
    }

    numberedNode n = numberedList[index];
    unsigned short bombCount = 0;
    std::vector<unsigned short> childIndexes;
    for (int i : n.attached)
    {
        unknownNode& u = unknownList[i];
        if (u.isBomb)
            bombCount++;
        else if (!u.visited)
        {
            childIndexes.push_back(i);
            u.visited = true;
        }
    }

    n.number -= bombCount;

    if (n.number < 0 || n.number > childIndexes.size())
        return;
    else if (n.number == 0)
    {
        getSolutionsHelper(index + 1, numberedList, unknownList, out);
        return;
    }

    combinationHardcoded(childIndexes, n.number, n.combinations);
    
    unsigned short combinationSize = n.combinations.size();
    for (unsigned short i = 0; i < combinationSize; i++)
    {
        std::vector<unknownNode> unknownListClone = unknownList;
        for (unsigned short g : n.combinations[i])
            unknownListClone[g].isBomb = true;

        getSolutionsHelper(index + 1, numberedList, unknownListClone, out);
    }
}

std::vector<std::vector<bool>> bruteForce::getSolutions(const int& group)
{
    sortNumbered(group, unknowns[group]);
    std::vector<std::vector<bool>> solutions;
    for (unknownNode& u : unknowns[group])
    {
        u.isBomb = false;
        u.visited = false;
    }
    getSolutionsHelper(0, numbered[group], unknowns[group], solutions);
    return solutions;
}

unsigned short getBombCount(const std::vector<bool>& v)
{
    unsigned short bombCount = 0;
    for (const bool& b : v)
        bombCount += b;
    return bombCount;
}

unsigned short findMaxInVector(const std::vector<std::vector<bool>>& input)
{
    unsigned short max = 0;
    for (const std::vector<bool>& v : input)
    {
        unsigned short bCount = getBombCount(v);
        if (bCount > max)
            max = bCount;
    }
    return max;
}

unsigned short findMaxAmountBetweenVectors(const std::vector<std::vector<std::vector<bool>>>& input)
{
    unsigned short sum;
    for (const std::vector<std::vector<bool>>& v : input)
        sum += findMaxInVector(v);
    return sum;
}

std::vector<bool> combineBoolVectors(const std::vector<bool>& A, const std::vector<bool>& B)
{
    std::vector<bool> AB;
    AB.reserve( A.size() + B.size() ); // preallocate memory
    AB.insert( AB.end(), A.begin(), A.end() );
    AB.insert( AB.end(), B.begin(), B.end() );
    return AB;
}

std::vector<std::vector<bool>> combineSolutions(const std::vector<std::vector<bool>> &a, const std::vector<std::vector<bool>> &b, const unsigned short& max)
{
    if (a.size() == 0)
        return b;
    else if (b.size() == 0)
        return a;
    
    std::vector<std::vector<bool>> combined;
    combined.reserve(a.size() * b.size());
    for (const std::vector<bool>& va : a)
    {
        unsigned short vaBombCount = getBombCount(va);
        for (const std::vector<bool>& vb : b)
        {
            unsigned short vbBombCount = getBombCount(vb);
            if (max < vbBombCount + vaBombCount)
                continue;
            combined.push_back(combineBoolVectors(va, vb));
        }
    }

    return combined;
}

std::vector<std::vector<bool>> combineAll(const std::vector<std::vector<std::vector<bool>>>& p_vectors, const unsigned short& max)
{
    std::vector<std::vector<bool>> r_combined;
    for (std::vector<std::vector<bool>> vector : p_vectors)
        r_combined = combineSolutions(r_combined, vector, max);
    return r_combined;
}

void bruteForce::findSafePicks()
{
    std::vector<std::vector<std::vector<bool>>> bombLayouts;
    unsigned short numberedSize = numbered.size();
    for (unsigned short group = 0; group < numberedSize; group++)
    {
        std::vector<std::vector<bool>> sol = getSolutions(group);
        bombLayouts.push_back(sol);
    }
    if (numberCount > bombCount && unknownCount > bombCount && (findMaxAmountBetweenVectors(bombLayouts) > bombCount))
    {
        findSafePicksBombCount(bombLayouts);
        return;
    }
    findSafePicksFast(bombLayouts);
}

void bruteForce::findSafePicksFast(const std::vector<std::vector<std::vector<bool>>>& bombLayouts)
{
    unsigned short numberedSize = numbered.size();
    for (unsigned short group = 0; group < numberedSize; group++)
    {
        std::vector<std::vector<bool>> sol = bombLayouts[group];

        std::vector<probData> bombChances;

        unsigned short length = sol[0].size();
        bombChances.reserve(length);
        for (unsigned short i = 0; i < length; i++)
            bombChances.push_back(probData(unknowns[group][i].iD, 0));

        for (const std::vector<bool>& v : sol)
        {
            unsigned short vectorSize = v.size();
            for (unsigned short i = 0; i < vectorSize; i++)
                bombChances[i].probability += v[i];
        }

        probabilities.reserve(bombChances.size());
        for (probData& p : bombChances)
        {
            p.probability /= sol.size();
            probabilities.push_back(p);
        }   
    }
}

void bruteForce::findSafePicksBombCount(const std::vector<std::vector<std::vector<bool>>>& bombLayouts)
{
    std::vector<std::vector<std::vector<bool>>> sols;
    unsigned short numSize = numbered.size();
    sols.reserve(numSize);
    for (unsigned short group = 0; group < numSize; group++)
    {
        std::vector<std::vector<bool>> sol = bombLayouts[group];
        sols.push_back(sol);
    }

    std::vector<std::vector<bool>> sol = combineAll(sols, bombCount);

    if (sol.size() == 0)
        return;
    unsigned int length = sol[0].size();

    unsigned short j = 0;
    unsigned short group = 0;
    std::vector<unknownNode> unknownList = unknowns[group];
    unsigned short unknownSize = unknownList.size();
    probabilities.reserve(length);
    for (unsigned int i = 0; i < length; i++)
    {
        if (j == unknownList.size())
        {
            j = 0;
            group++;
            unknownList = unknowns[group];
            unknownSize = unknownList.size();
        }
        probabilities.push_back(probData(unknownList[j].iD, 0));
        j++;
    }

    for (const std::vector<bool>& v : sol)
        for (unsigned int i = 0; i < length; i++)
            probabilities[i].probability += v[i];
    float solSize = sol.size();
    for (probData& p : probabilities)
        p.probability /= solSize;
}

float bruteForce::getProbability(int iD)
{
    for (probData p : probabilities)
        if (p.iD == iD)
            return p.probability;

    return -1;
}

bruteForce::bruteForce(int _bombCount)
{
    bombCount = _bombCount;
    numberCount = 0;
}

bruteForce::~bruteForce()
{

}