#include "bruteForceLogic.h"
#include "util.h"

// #define INFO
// #define GETSOLINFO
// #define DELETEINFO
// #define INFOALLSOLS
// #define INTERESTX 13
// #define INTERESTY 7

numberedNode* bruteForce::searchNumbered(int iD)
{
    for (std::vector<numberedNode*> v : numbered)
        for (numberedNode* n : v)
            if (n->iD == iD)
                return n;

    return nullptr;
}

unknownNode* bruteForce::searchUnknown(int iD)
{
    for (std::vector<unknownNode*> unknownsSubset : unknowns)
        for (unknownNode* n : unknownsSubset)
            if (n->iD == iD)
                return n;

    return nullptr;
}

void bruteForce::addNumbered(int iD, int group, int number)
{
    if (searchNumbered(iD))
        return;

    while (numbered.size() < group + 1) 
        numbered.push_back(std::vector<numberedNode*>());

    numbered[group].push_back(new numberedNode(iD, number));
}

void bruteForce::addUnknown(int iD, int group, int parentId)
{
    unknownNode* unNode = searchUnknown(iD);
    numberedNode* numNode = searchNumbered(parentId);

    if (!numNode)
        return;
    if (!unNode)
    {
        while (unknowns.size() < group + 1) 
            unknowns.push_back(std::vector<unknownNode*>());

        unNode = new unknownNode(iD);
        unknowns[group].push_back(unNode);
    }

    numNode->unknownNodes.push_back(unNode);
}

void bruteForce::getSolutions()
{
    for (std::vector<numberedNode*> v : numbered)
        for (numberedNode* n : v)
        {
            std::vector<int> set;
            for (unknownNode* u : n->unknownNodes)
                set.push_back(u->iD);
            n->solutions.clear();
            combination(set, n->number, n->solutions);

            #ifdef INFOALLSOLS
            for (std::vector<int> v : n->solutions)
            {
                for (int i : v)
                {
                    #ifdef INTERESTX
                    if (i != INTERESTX + INTERESTY*16)
                        continue;
                    #endif
                    std::cout << "x: " << i % 16 << " y: " << i/16 << " | ";
                }
                std::cout << std::endl;
            }
            #endif

        }
}

void bruteForce::removeSolutions()
{
    int upperRemoved = 0;
    int belowRemoved = 0;
    int duplicateRemoved = 0;
    int intersectRemove = 0;

    for (int group = 0; group < numbered.size(); group++)
    {
    for (numberedNode* n1 : numbered[group])
    {
        for (numberedNode* n2 : numbered[group])
        {
            if (n1 == n2)
                continue;

            bool removed = false;
                
            for (int i = 0; i < n1->solutions.size(); i++)
            {
                std::vector<int> v1 = n1->solutions[i];

                if (v1.size() == 0)
                    continue;

                for (int j = 0; j < n2->solutions.size(); j++)
                {
                    std::vector<int> v2 = n2->solutions[j];

                    if (v2.empty())
                        continue;

                    if (!validUpperCheck(v2, group))
                    {
                        for (int i : v2)
                            if (i == 12 + 10*16)
                                std::cout << "upper dELETED" << std::endl;
                        n2->solutions.erase(n2->solutions.begin() + j);
                        upperRemoved++;
                        removed = true;
                    }
                    else if (!validBelowCheck(v2, n2, group))
                    {
                        for (int i : v2)
                            if (i == 12 + 10*16)
                                std::cout << "below dELETED" << std::endl;
                        n2->solutions.erase(n2->solutions.begin() + j);
                        belowRemoved++;
                        removed = true;
                    }
                    else if (compareVects(v1, v2))
                    {
                        for (int i : v2)
                            if (i == 12 + 10*16)
                                std::cout << "compare dELETED" << std::endl;
                        n2->solutions.erase(n2->solutions.begin() + j);
                        duplicateRemoved++;
                        removed = true;
                    }
                    // else if (removeInterectionVects(v2, v1))
                    // {
                    //     if (v2.size() == 0)
                    //     {
                    //         n2->solutions.erase(n2->solutions.begin() + j);
                    //         intersectRemove++;
                    //     }
                    // }
                }
            }

            if (removed)
                n2->solutions.push_back(std::vector<int>());
        }
    }
        for (int i = 0; i < numbered[group].size(); i++)
            if (numbered[group][i]->solutions.size() == 0)
                numbered[group][i]->solutions.push_back(std::vector<int>());
    }
    // // #ifdef DELETEINFO
    // std::cout << "Intersect: " << intersectRemove << " Duplicate: " << duplicateRemoved << " Upper: " << upperRemoved << " Below: " << belowRemoved << std::endl;
    // std::string a;
    // std::cin >> a;
    // // #endif
}

bool bruteForce::validBelowCheck(std::vector<int> vect, numberedNode* num, int group)
{
    for (unknownNode* n : unknowns[group])
        n->isBomb = true;

    for (unknownNode* n : num->unknownNodes)
        n->isBomb = false;

    for (int i : vect)
        searchUnknown(i)->isBomb = true;

    for (numberedNode* n : numbered[group])
    {
        int bombs = 0;
        for (unknownNode* u : n->unknownNodes)
            if (u->isBomb)
                bombs++;

        if (n->number > bombs)
            return false;
    }
    return true;
}

bool bruteForce::validUpperCheck(std::vector<int> vect, int group)
{
    for (unknownNode* n : unknowns[group])
        n->isBomb = false;

    for (int i : vect)
        searchUnknown(i)->isBomb = true;

    for (numberedNode* n : numbered[group])
    {
        int bombs = 0;
        for (unknownNode* u : n->unknownNodes)
            if (u->isBomb)
                bombs++;
        if (n->number < bombs)
            return false;
    }
    return true;
}

void bruteForce::getStats()
{
    std::vector<int> sum;
    int temp = 1;
    for (std::vector<numberedNode*> v : numbered)
    {
        temp = 1;
        for (numberedNode* n : v)
        {
            if (n->solutions.size() == 0)
                continue;
            temp *= n->solutions.size();
        }

        sum.push_back(temp);
    }

    summation = 0;
    for (int i : sum)
        summation += i;
    unsigned long alt = 0;
    for (std::vector<unknownNode*> v : unknowns)
        alt += pow(2, v.size());
    std::cout << "Combos: " << summation << " Alt: " << alt << std::endl;
    std::string a;
    std::cin >> a;
}

bool bruteForce::nextBombSet(int group)
{
    if (currNode == numbered[group].size())
        return true;

    for (std::vector<unknownNode*> unknownsSubset : unknowns)
        for (unknownNode* n : unknownsSubset)
            n->isBomb = false;

    for (numberedNode* n : numbered[group])
    {
        for (int i : n->solutions[n->currSol])
            searchUnknown(i)->isBomb = true;
    }
    
    iteration++;

    do
    {
        numberedNode* n = numbered[group][currNode];
        n->currSol++;
        if (n->currSol == n->solutions.size())
        {
            n->currSol = 0;
            currNode++;
            if (currNode == numbered[group].size())
                break;
            continue;
        }
        
        currNode = 0;
    }
    while (currNode != 0);

    // if (iteration > summation + 1)
    // {
    //     std::cout << iteration << " " << summation << std::endl;
    //     std::cout << "broken" << std::endl;
    //     exit(0);
    // }

    return false;
}

bool bruteForce::isValidSolution(int group)
{
    #ifdef INFOALLSOLS
    for (unknownNode* u : unknowns[group])
        std::cout << u->isBomb << " ";
    std::cout << std::endl;
    #endif
    for (numberedNode* n : numbered[group])
    {
        int bombs = 0;
        for (unknownNode* u : n->unknownNodes)
            if (u->isBomb)
                bombs++;
        if (n->number != bombs)
            return false;
    }
    return true;
}

// void bruteForce::findSafePicks()
// {
//     std::vector<unsigned long long int> validLongs;
//     int group = 0;

//     for (std::vector<unknownNode*> unknownsSubset : unknowns)
//     {

//     for (unsigned long long int i = 0; i < pow(2, unknownsSubset.size()); i++)
//     {
//         for (int j = 0; j < unknownsSubset.size() && j < 64; j++)
//             if (getBitLong(i, j))
//                 unknownsSubset[j]->isBomb = true;
//             else
//                 unknownsSubset[j]->isBomb = false;
//         bool valid = true;
//         for (numberedNode* n : numbered[group])
//         {
//             int bombs = 0;
//             for (unknownNode* u : n->unknownNodes)
//                 if (u->isBomb)
//                     bombs++;
//             if (n->number != bombs)
//             {
//                 valid = false;
//                 break;
//             }
//         }
//         if (valid)
//             validLongs.push_back(i);
//     }
//     unsigned long long int bombLong = 0xffffffffffffffff;
//     unsigned long long int notBombLong = 0;

//     for (unsigned long i : validLongs)
//     {
//         bombLong &= i;
//         notBombLong |= i;
//     }   
//     for (int j = 0; j < unknownsSubset.size(); j++)
//     {
//         if (getBitLong(bombLong, j))
//             bombs.push_back(unknownsSubset[j]->iD);

//         if (!getBitLong(notBombLong, j))
//             notBombs.push_back(unknownsSubset[j]->iD);
//     }
//     group++;
//     }
// }

// void bruteForce::findSafePicks2()
// {
//     iteration = 0;
//     int amountOfGroups = unknowns.size();
//     getSolutions();
//     removeSolutions();
//     getStats();
//     for (int group = 0; group < amountOfGroups; group++)
//     {
//         for (std::vector<numberedNode*> v : numbered)
//             for (numberedNode* n : v)
//                 n->currSol = 0;
//         currNode = 0;
//         std::vector<numberedNode*> numberedSet = numbered[group];
//         std::vector<unknownNode*> unknownSet = unknowns[group];
//         std::vector<std::vector<bool>> bombTables;

//         while (!nextBombSet(group))
//         {
//             if (!isValidSolution(group))
//                 continue;

//             bombTables.push_back(std::vector<bool>());

//             for (int i = 0; i < unknownSet.size(); i++)
//                 if (unknownSet[i]->isBomb)
//                     bombTables[bombTables.size()-1].push_back(true);
//                 else
//                     bombTables[bombTables.size()-1].push_back(false);
//         }

//         if (bombTables.size() == 0)
//             continue;

//         std::vector<bool> bombSet;
//         std::vector<bool> notBombSet;
//         for (int i = 0; i < unknownSet.size(); i++)
//         {
//             bombSet.push_back(true);
//             notBombSet.push_back(false);
//         }

//         for (std::vector<bool> bombTable : bombTables)
//             for (int i = 0; i < unknownSet.size(); i++)
//             {
//                 bool curr = bombTable[i];
//                 bombSet[i] = bombSet[i] & curr;
//                 notBombSet[i] = notBombSet[i] | curr;
//             }
        
//         for (int i = 0; i < unknownSet.size(); i++)
//         {
//             if (bombSet[i])
//                 bombs.push_back(unknownSet[i]->iD);

//             if (!notBombSet[i])
//                 notBombs.push_back(unknownSet[i]->iD);
//         }

//         #ifdef INFO
//         std::cout << "Total Output:" << std::endl;
//         for (std::vector<bool> v : bombTables)
//         {
//             for (bool b : v)
//                 std::cout << b << " ";

//             std::cout << std::endl;
//         }
//         std::cout << "Bombs:" << std::endl;
//         for (bool b : bombSet)
//             std::cout << b << " ";
//         std::cout << std::endl;
//         for (int i = 0; i < unknownSet.size(); i++)
//             if (bombSet[i])
//                 std::cout << unknownSet[i]->iD % 16 << " " << unknownSet[i]->iD / 16 << " / ";
//         std::cout << std::endl;

//         std::cout << "Not Bombs:" << std::endl;
//         for (bool b : notBombSet)
//             std::cout << b << " ";
//         std::cout << std::endl;
//         for (int i = 0; i < unknownSet.size(); i++)
//             if (!notBombSet[i])
//                 std::cout << unknownSet[i]->iD % 16 << " " << unknownSet[i]->iD / 16 << " / ";
//         std::cout << std::endl;
//         for (int i = 0; i < unknownSet.size(); i++)
//             std::cout << unknownSet[i]->iD % 16 << " " << unknownSet[i]->iD / 16 << " / ";
//         std::cout << std::endl;
//         std::cout << "Group: " << (char)('a' + group) << std::endl;
//         std::string a;
//         std::cin >> a;
//         #endif
//     }

//     // std::cout << "Iterations: " << iteration << " " << "Expected Iterations: " << summation << std::endl;
//     // std::string a;
//     // std::cin >> a;
// }

std::vector<int> bruteForce::getBombs()
{
    return bombs;
}

std::vector<int> bruteForce::getNotBombs()
{
    return notBombs;
}

bruteForce::bruteForce()
{

}

bruteForce::~bruteForce()
{
    for (std::vector<numberedNode*> v : numbered)
        for (numberedNode* n : v)
            delete n;
    for (std::vector<unknownNode*> v : unknowns)
        for (unknownNode* n : v)
            delete n;
}