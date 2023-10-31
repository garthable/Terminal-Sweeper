#include "bruteForceLogic.h"
#include "util.h"

numberedNode* bruteForce::searchNumbered(int iD)
{
    for (numberedNode* n : numbered)
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

void bruteForce::addNumbered(int iD, int number)
{
    if (searchNumbered(iD))
        return;

    numbered.push_back(new numberedNode(iD, number));
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

void bruteForce::findSafePicks()
{
    std::cout << "called" << std::endl;
    std::vector<unsigned long long int> validLongs;

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
        for (numberedNode* n : numbered)
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

    std::cout << bombLong << " " << notBombLong << std::endl;
    std::string a;
    std::cin >> a;
    std::cout << "4" << std::endl;
    for (int j = 0; j < unknownsSubset.size(); j++)
    {
        if (getBitLong(bombLong, j))
            bombs.push_back(unknownsSubset[j]->iD);

        if (!getBitLong(notBombLong, j))
            notBombs.push_back(unknownsSubset[j]->iD);
    }
    }
    std::cout << "exited" << std::endl;
}

void bruteForce::findSafePicks2()
{
    for (std::vector<unknownNode*> unknownsSubset : unknowns)
    {
    int max = 0;
    std::vector<int> set;

    for (numberedNode* n : numbered)
    {
        set.push_back(n->iD);
        max += n->number;
    }

    int min = max/2;
    std::vector<std::vector<bool>> validsets;


    for (int r = min; r < max+1 && r < unknownsSubset.size(); r++)
    {
        std::vector<std::vector<int>> subset;
        combination(set, r, subset);
        for (std::vector<int> curr : subset)
        {
            for (unknownNode* n : unknownsSubset)
                n->isBomb = false;
            for (int currId : curr)
            {
                unknownNode* n = searchUnknown(currId);
                n->isBomb = true;
            }
        }
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
    
}