#include "bruteForceLogic.h"
#include "util.h"

//NEXT GOAL: IMPROVE BOMB COUNT LOGIC

numberedNode* bruteForce::searchNumbered(int iD)
{
    for (int i = 0; i < numbered.size(); i++)
        for (int g = 0; g < numbered[i].size(); g++)
            if (numbered[i][g].iD == iD)
                return &numbered[i][g];

    return nullptr;
}

unknownNode* bruteForce::searchUnknown(int iD)
{
    for (int i = 0; i < unknowns.size(); i++)
        for (int g = 0; g < unknowns[i].size(); g++)
            if (unknowns[i][g].iD == iD)
                return &unknowns[i][g];

    return nullptr;
}

void bruteForce::addNumbered(int iD, int group, int number)
{
    if (searchNumbered(iD))
        return;

    while (numbered.size() < group + 1) 
        numbered.push_back(std::vector<numberedNode>());

    numbered[group].push_back(numberedNode(iD, number));
}

void bruteForce::addUnknown(int iD, int group, int parentId)
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
        unNode = &unknowns[group][unknowns[group].size() - 1];
    }

    int index = 0;
    for (; index < unknowns[group].size(); index++)
        if (unknowns[group][index].iD == unNode->iD)
            break;

    numNode->attached.push_back(index);
}

void bruteForce::sortNumbered(int group, std::vector<unknownNode> unknownList)
{
    std::vector<numberedNode> clonedNumbered = numbered[group];
    std::vector<numberedNode> sortedList;
    
    for (unknownNode u : unknownList)
        u.visited = false;
    
    while (numbered[group].size() != sortedList.size())
    {
        int min = 99999;
        numberedNode minNode = numberedNode(-1, -1);

        for (numberedNode n : clonedNumbered)
        {
            std::vector<int> childNodes;
            for (int i : n.attached)
                if (!unknownList[i].visited)
                    childNodes.push_back(i);
            
            int val = combinationValueHardcoded(childNodes, n.number);
            if (min > val)
            {
                min = val;
                minNode = n;
            }
        }
        for (int i = 0; i < clonedNumbered.size(); i++)
            if (clonedNumbered[i].iD == minNode.iD)
            {
                clonedNumbered.erase(clonedNumbered.begin() + i);
                break;
            }
        for (int i : minNode.attached)
            unknownList[i].visited = true;
        sortedList.push_back(minNode);
    }

    for (unknownNode u : unknownList)
        u.visited = false;

    numbered[group] = sortedList;
}

bool bruteForce::isValidUpper(const std::vector<numberedNode>& numberedList, const std::vector<unknownNode>& unknownList)
{
    for(numberedNode n : numberedList)
    {
        int count = 0;
        for (int i : n.attached)
            if (unknownList[i].isBomb)
                count++;
        if (count > n.number)
            return false;
    }
    return true;
}

bool bruteForce::isValid(const std::vector<numberedNode>& numberedList, const std::vector<unknownNode>& unknownList)
{
    int totalCount = 0;
    for(numberedNode n : numberedList)
    {
        int count = 0;
        for (int i : n.attached)
            if (unknownList[i].isBomb)
                count++;
        if (count != n.number)
            return false;
    }
    return true;
}

void bruteForce::getSolutionsHelper(int index, const std::vector<numberedNode>& numberedList, 
                                    std::vector<unknownNode> unknownList, std::vector<std::vector<bool>>& out)
{       
    if (index == numberedList.size())
    {
        if (!isValid(numberedList, unknownList))
            return;

        std::vector<bool> solution;
        for (unknownNode u : unknownList)
            solution.push_back(u.isBomb);
        out.push_back(solution);
        return;
    }

    numberedNode n = numberedList[index];
    int bombCount = 0;
    std::vector<int> childIndexes;
    for (int i : n.attached)
        if (unknownList[i].isBomb)
            bombCount++;
        else if (!unknownList[i].visited)
        {
            childIndexes.push_back(i);
            unknownList[i].visited = true;
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
    
    for (int i = 0; i < n.combinations.size(); i++)
    {
        std::vector<unknownNode> unknownListClone = unknownList;
        for (int g : n.combinations[i])
            unknownListClone[g].isBomb = true;

        if (!isValidUpper(numberedList, unknownListClone))
            continue;

        getSolutionsHelper(index + 1, numberedList, unknownListClone, out);
    }
}

std::vector<std::vector<bool>> bruteForce::getSolutions(int group)
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

std::vector<bool> combineBoolVectors(std::vector<bool> A, std::vector<bool> B)
{
    std::vector<bool> AB;
    AB.reserve( A.size() + B.size() ); // preallocate memory
    AB.insert( AB.end(), A.begin(), A.end() );
    AB.insert( AB.end(), B.begin(), B.end() );
    return AB;
}

std::vector<std::vector<bool>> combineSolutions(std::vector<std::vector<bool>> a, std::vector<std::vector<bool>> b)
{
    if (a.size() == 0)
        return b;
    else if (b.size() == 0)
        return a;
    else if (a.size() == 0 || b.size() == 0)
        return {{}};
    std::vector<std::vector<bool>> combined;
    for (std::vector<bool> va : a)
        for (std::vector<bool> vb : b)
            combined.push_back(combineBoolVectors(va, vb));

    return combined;
}

std::vector<std::vector<bool>> combineAll(std::vector<std::vector<std::vector<bool>>> p_vectors)
{
    std::vector<std::vector<bool>> r_combined;
    int r_combinedBombCount = 0;
    for (std::vector<std::vector<bool>> vector : p_vectors)
        r_combined = combineSolutions(r_combined, vector);
    return r_combined;
}

void bruteForce::findSafePicks()
{
    probabilities.clear();
    std::vector<std::vector<std::vector<bool>>> sols;
    for (int group = 0; group < numbered.size(); group++)
    {
        std::vector<std::vector<bool>> sol = getSolutions(group);
        sols.push_back(sol);
    }

    std::vector<std::vector<bool>> sol = combineAll(sols);

    for (int i = 0; i < sol.size(); i++)
    {
        std::vector<bool> s = sol[i];
        int bCount = 0;
        for (bool b : s)
            if (b)
                bCount++;
        if (bCount > bombCount)
            sol.erase(sol.begin() + i);
    }

    if (sol.size() == 0)
        return;
    int length = sol[0].size();

    int j = 0;
    int group = 0;
    for (int i = 0; i < length; i++)
    {
        if (j == unknowns[group].size())
        {
            j = 0;
            group++;
        }
        probabilities.push_back(probData(unknowns[group][j].iD, 0));
        j++;
    }

    for (std::vector<bool> v : sol)
        for (int i = 0; i < length; i++)
            probabilities[i].probability += v[i];
    for (probData& p : probabilities)
        p.probability /= sol.size();
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
}

bruteForce::~bruteForce()
{

}