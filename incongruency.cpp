#include "incongruency.h"

std::vector<int> incongruency::testIncogs(std::vector<solverNode*> nodes)
{
    clear();
    addNodes(nodes);
    findIncongruencies();
    getValidCombinations();
    return findBombs();
}

incongruencySet* incongruency::searchSet(std::vector<int> set)
{
    for (incongruencySet* incogSet : incongruencySets[set.size() - 1])
        if (compareVects(set, incogSet->set))
            return incogSet;

    return nullptr;
}

incongruencySubset* incongruency::searchSubset(std::vector<int> subSet)
{
    for (incongruencySubset* incogSubset : incongruencySubsets[subSet.size()-1])
        if (compareVects(subSet, incogSubset->subset))
            return incogSubset;
            
    return nullptr;
}

incongruencySet* incongruency::addSet(int _r, solverNode* node, std::vector<int> _set)
{
    incongruencySet* set = new incongruencySet(node, _set);
    incongruencySets[_r-1].push_back(set);
    incongruencySetsNonSegregated.push_back(set);
    return set;
}

incongruencySubset* incongruency::addSubset(std::vector<int> _subset, incongruencySet* parentSet)
{
    incongruencySubset* subset = searchSubset(_subset);
    if (!subset)
    {
        subset = new incongruencySubset(_subset);
        incongruencySubsets[_subset.size()-1].push_back(subset);
        incongruencySubsetsNonSegregated.push_back(subset);
    }
    parentSet->incongruencySubsets.push_back(subset);
    return subset;
}

bool incongruency::validSet(incongruencySet* set)
{
    int i = 0;
    for (incongruencySubset* subset : set->incongruencySubsets)
        if (subset->enabled)
            i++;
    if (i == 1)
        return true;
    return false;
}

bool incongruency::allSetsValid()
{
    for (int i = 0; i < 8; i++)
        for (incongruencySet* set : incongruencySets[i])
            if (!validSet(set))
                return false;
    return true;
}

void incongruency::addNodes(std::vector<solverNode*> solverNodes)
{
    for(solverNode* n : solverNodes)
    {
        std::vector<int> set;
        int flagged = 0;
        for(solverNode* a : n->adjNodes)
            if (!a->discovered && !a->flagged)
                set.push_back(a->x + a->y*SIZEX);
            else if (a->flagged)    
                flagged++; 

        if (set.empty())
            continue;

        int r = n->adjBombs - flagged;
        incongruencySet* incogSet = addSet(r, n, set);
        std::vector<std::vector<int>> subsets;
        combination(set, r, subsets);

        for (std::vector<int> v : subsets)
            addSubset(v, incogSet);
    }
}

void incongruency::findIncongruencies()
{
    for (int i = 0; i < 8; i++)
        for (incongruencySet* set : incongruencySets[i])
        {
            for (incongruencySubset* subsetA : set->incongruencySubsets)
            {
                for (incongruencySubset* subsetB : set->incongruencySubsets)
                {
                    if (compareVects(subsetA->subset, subsetB->subset))
                        continue;
                    
                    subsetA->incongruentSubsets.push_back(subsetB);
                }
                for (int r = 0; r < subsetA->subset.size()-1; r++)
                {
                    std::vector<std::vector<int>> output;
                    combination(subsetA->subset, r, output);
                    for (std::vector<int> subset : output)
                    {
                        incongruencySubset* inSubsetA = searchSubset(subset);

                        if (!inSubsetA)
                        {
                            continue;
                        }

                        for (incongruencySubset* incog : inSubsetA->incongruentSubsets)
                            subsetA->incongruentSubsets.push_back(incog);
                    }
                }
            }
        }
}

bool incongruency::enable(incongruencySubset* subset)
{
    for (incongruencySubset* disabledSubset : subset->incongruentSubsets)
        if (disabledSubset->enabled)
            return false;

    subset->enabled = true;
    return true;
}

void incongruency::reset()
{
    for (int i = 0; i < 8; i++)
    {
        for (incongruencySet* set : incongruencySets[i])
            set->fufilled = false;
        for (incongruencySubset* subset : incongruencySubsets[i])
            subset->enabled = false;
    }
}

void incongruency::getValidCombinations()
{
    //Check via sets only compare to sets that are within 2 units away.
    for (incongruencySet* setA : incongruencySetsNonSegregated)
        for (incongruencySet* setB : incongruencySetsNonSegregated)
        {
            if (abs(setA->node->x - setB->node->x) > 2 || abs(setA->node->y - setB->node->y) > 2)
                continue;

            for (incongruencySubset* subsetA : setA->incongruencySubsets)
                for (incongruencySubset* subsetB : setB->incongruencySubsets)
                    for (incongruencySubset* invalidSubset : subsetA->incongruentSubsets)
                        if (!compareVects(subsetB->subset, invalidSubset->subset))
                            subsetA->congruent++;
        }
    
    //Find all valid combinations here
    for (incongruencySubset* subset : incongruencySubsetsNonSegregated)
    {
        if (subset->congruent != 0 && subset->subset.size() != 1 || subset->incongruentSubsets.size() < 6)
            continue;
        
        for (int a : subset->subset)
            noBomb.push_back(a);
    }
}

std::vector<int> incongruency::findBombs()
{
    return noBomb;
}

void incongruency::clear()
{
    for (int i = 0; i < 8; i++)
    {
        for (incongruencySet* set : incongruencySets[i])
            delete set;
        for (incongruencySubset* subset : incongruencySubsets[i])
            delete subset;
        
        incongruencySubsetsNonSegregated.clear();
        incongruencySetsNonSegregated.clear();
        incongruencySets[i].clear();
        incongruencySubsets[i].clear();
        noBomb.clear();
    }
}

incongruency::incongruency()
{

}
incongruency::~incongruency()
{
    clear();
}