#include "bruteForceLogic.h"
#include "util.h"

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

void bruteForce::getCombinations()
{
    for (int i = 0; i < numbered.size(); i++)
        for (int g = 0; g < numbered[i].size(); g++)
        {
            std::vector<int> childIndexes;

            combination(numbered[i][g].attached, numbered[i][g].number, numbered[i][g].combinations);
        }
}

bool bruteForce::isValidUpper(std::vector<numberedNode> numberedList, std::vector<unknownNode> unknownList)
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

bool bruteForce::isValid(std::vector<numberedNode> numberedList, std::vector<unknownNode> unknownList)
{
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

void bruteForce::getSolutionsHelper(int index, std::vector<numberedNode> numberedList, 
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
        else
            childIndexes.push_back(i);

    n.number -= bombCount;

    if (n.number < 0 || n.number > childIndexes.size())
        return;

    else if (n.number == 0)
    {
        getSolutionsHelper(index + 1, numberedList, unknownList, out);
        return;
    }

    combination(childIndexes, n.number, n.combinations);
    
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
    std::vector<std::vector<bool>> solutions;
    for (unknownNode& u : unknowns[group])
        u.isBomb = false;
    getSolutionsHelper(0, numbered[group], unknowns[group], solutions);
    return solutions;
}

void bruteForce::findSafePicks()
{
    probabilities.clear();
    for (int group = 0; group < numbered.size(); group++)
    {
        std::vector<std::vector<bool>> sol = getSolutions(group);

        // for (std::vector<bool> v : sol)
        // {
        //     std::string s = "";
        //     for (bool b : v)
        //         if (b)
        //             s += "1";
        //         else
        //             s += "0";
        //     uprint(s);
        // }

        std::vector<probData> bombChances;
        for (int i = 0; i < sol[0].size(); i++)
            bombChances.push_back(probData(unknowns[group][i].iD, 0));

        for (std::vector<bool> v : sol)
            for (int i = 0; i < v.size(); i++)
                bombChances[i].probability += v[i];

        for (probData& p : bombChances)
        {
            p.probability /= sol.size();
            // uprint(p.probability);
        }

        for (probData p : bombChances)
            probabilities.push_back(p);
    }
}

float bruteForce::getProbability(int iD)
{
    for (probData p : probabilities)
        if (p.iD == iD)
            return p.probability;

    return -1;
}

bruteForce::bruteForce()
{

}

bruteForce::~bruteForce()
{

}