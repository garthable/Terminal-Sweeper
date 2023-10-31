#include "solver.h"
#include "util.h"

#ifndef INCONGRUENCY
#define INCONGRUENCY

struct incongruencySubset
{
    bool enabled;
    int congruent;
    std::vector<int> subset;
    std::vector<incongruencySubset*> incongruentSubsets;

    incongruencySubset(std::vector<int> _subset)
    {
        subset = _subset;
        congruent++;
    }
};

struct incongruencySet
{
    solverNode* node;
    bool fufilled;
    std::vector<int> set;
    std::vector<incongruencySubset*> incongruencySubsets;

    incongruencySet(solverNode* _node, std::vector<int> _set)
    {
        node = _node;
        set = _set;
    }
};

class incongruency
{
    public:
        incongruencySet* searchSet(std::vector<int>);
        incongruencySubset* searchSubset(std::vector<int>);

        incongruencySet* addSet(int, solverNode*, std::vector<int>);
        incongruencySubset* addSubset(std::vector<int>, incongruencySet*);

        bool validSet(incongruencySet*);
        bool allSetsValid();
        bool enable(incongruencySubset*);

        void addNodes(std::vector<solverNode*>);
        void findIncongruencies();
        void reset();
        void clear();

        void getValidCombinations();

        std::vector<int> findBombs();

        std::vector<int> testIncogs(std::vector<solverNode*>);

        incongruency();
        ~incongruency();

    private:
        std::vector<incongruencySet*> incongruencySets[8];
        std::vector<incongruencySubset*> incongruencySubsets[8];

        std::vector<incongruencySet*> incongruencySetsNonSegregated;
        std::vector<incongruencySubset*> incongruencySubsetsNonSegregated;
        
        std::vector<int> noBomb;
};

#endif