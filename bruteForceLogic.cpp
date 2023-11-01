#include "bruteForceLogic.h"
#include "util.h"

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

void bruteForce::getValidSolutions()
{
    for (std::vector<numberedNode*> v : numbered)
        for (numberedNode* n : v)
        {
            std::vector<int> set;
            for (unknownNode* u : n->unknownNodes)
                set.push_back(u->iD);
            n->solutions.clear();
            combination(set, n->number, n->solutions);
            bool deletedPart = false;
            for (numberedNode* n2 : v)
            {
                if (n == n2)
                    continue;

                for (std::vector<int> v2 : n2->solutions)
                {
                    for (int i = 0; i < n->solutions.size(); i++)
                    {
                        if (n->solutions[i].size() == 0 || v2.size() == 0)
                            continue;
                        if (n2->number != n->number)
                            continue;
                        if (compareVects(n->solutions[i], v2))
                        {
                            deletedPart = true;
                            n->solutions.erase(n->solutions.begin() + i);
                        }
                    }
                }
            }
            if (deletedPart)
                n->solutions.push_back(std::vector<int>());
        }
}

bool bruteForce::nextBombSet(int group)
{
    for (std::vector<unknownNode*> unknownsSubset : unknowns)
        for (unknownNode* n : unknownsSubset)
            n->isBomb = false;

    for (numberedNode* n : numbered[group])
        for (int i : n->solutions[n->currSol])
            searchUnknown(i)->isBomb = true;

    numberedNode* n = numbered[group][currNode];
    n->currSol++;
    // if (n->iD == 245)
    // {
    //     std::cout << "Dumbass Node:" << std::endl;
    //     std::cout << n->currSol << " " << n->solutions.size() << std::endl;
    //     std::string a;
    //     std::cin >> a;
    // }
    if (n->currSol == n->solutions.size())
    {
        n->currSol = 0;
        if (currNode + 1 != numbered[group].size())
            currNode++;
        else
            return true;
    }
    else
        currNode = 0;

    return false;
}

bool bruteForce::isValidSolution(int group)
{
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

void bruteForce::findSafePicks()
{
    std::vector<unsigned long long int> validLongs;
    int group = 0;

    for (std::vector<unknownNode*> unknownsSubset : unknowns)
    {

    for (unsigned long long int i = 0; i < pow(2, unknownsSubset.size()); i++)
    {
        for (int j = 0; j < unknownsSubset.size() && j < 64; j++)
            if (getBitLong(i, j))
                unknownsSubset[j]->isBomb = true;
            else
                unknownsSubset[j]->isBomb = false;
        bool valid = true;
        for (numberedNode* n : numbered[group])
        {
            int bombs = 0;
            for (unknownNode* u : n->unknownNodes)
                if (u->isBomb)
                    bombs++;
            if (n->number != bombs)
            {
                valid = false;
                break;
            }
        }
        if (valid)
            validLongs.push_back(i);
    }
    unsigned long long int bombLong = 0xffffffffffffffff;
    unsigned long long int notBombLong = 0;

    for (unsigned long i : validLongs)
    {
        bombLong &= i;
        notBombLong |= i;
    }   
    for (int j = 0; j < unknownsSubset.size(); j++)
    {
        if (getBitLong(bombLong, j))
            bombs.push_back(unknownsSubset[j]->iD);

        if (!getBitLong(notBombLong, j))
            notBombs.push_back(unknownsSubset[j]->iD);
    }
    group++;
    }
}

void bruteForce::findSafePicks2()
{
    int amountOfGroups = unknowns.size();
    getValidSolutions();
    for (int group = 0; group < amountOfGroups; group++)
    {
        for (std::vector<numberedNode*> v : numbered)
            for (numberedNode* n : v)
                n->currSol = 0;
        currNode = 0;
        std::vector<numberedNode*> numberedSet = numbered[group];
        std::vector<unknownNode*> unknownSet = unknowns[group];
        std::vector<std::vector<bool>> bombTables;

        while (!nextBombSet(group))
        {
            // if (searchUnknown(276)->isBomb)
            // {
            //     std::cout << "confirmed 276" << std::endl;
            //     // std::string a;
            //     // std::cin >> a;
            // }
            // if (searchUnknown(246)->isBomb)
            // {
            //     std::cout << "confirmed 246" << std::endl;
            //     // std::string a;
            //     // std::cin >> a;
            // }

            if (!isValidSolution(group))
                continue;

            bombTables.push_back(std::vector<bool>());

            for (int i = 0; i < unknownSet.size(); i++)
                if (unknownSet[i]->isBomb)
                    bombTables[bombTables.size()-1].push_back(true);
                else
                    bombTables[bombTables.size()-1].push_back(false);
        }

        // std::cout << std::endl;
        // for (std::vector<bool> bombTable : bombTables)
        // {
        //     for (bool bomb : bombTable)
        //     {
        //         std::cout << bomb << " ";
        //     }
        //     std::cout << std::endl;
        // }
        // std::cout << "Hai" << std::endl;
        // std::string a;
        // std::cin >> a;

        std::vector<bool> bombSet;
        std::vector<bool> notBombSet;
        for (int i = 0; i < unknownSet.size(); i++)
        {
            bombSet.push_back(true);
            notBombSet.push_back(false);
        }

        for (std::vector<bool> bombTable : bombTables)
            for (int i = 0; i < unknownSet.size(); i++)
            {
                bool curr = bombTable[i];
                bombSet[i] = bombSet[i] & curr;
                notBombSet[i] = notBombSet[i] | curr;
            }
        
        for (int i = 0; i < unknownSet.size(); i++)
        {
            if (bombSet[i])
                bombs.push_back(unknownSet[i]->iD);

            if (!notBombSet[i])
                notBombs.push_back(unknownSet[i]->iD);
        }
    }
}

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