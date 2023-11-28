#include "solverUtil.cpp"
#include "solver.h"

void solver::DFSHelper(solverNode*& curr, const unsigned short& group, std::vector<solverNode*>& set)
{
    curr->visited = true;
    curr->group = group;

    for (const unsigned short& index : curr->adjNodes)
    {
        solverNode*& n = m_nodes[index];
        if (curr->discovered && n->discovered)
            continue;
        if (n->visited)
            continue;

        bool shouldContinue = true;

        for (solverNode*& compare : set)
            if (n == compare)
                shouldContinue = false;

        if (shouldContinue || (!(curr->discovered || n->discovered) && !shareNumbered(curr, n, set)))
            continue;

        DFSHelper(n, group, set);
    }
}
void solver::DFSGrouping(std::vector<solverNode*>& set)
{
    unsigned short group = 0;
    for (solverNode*& n : m_nodes)
    {
        n->visited = false;
        n->group = 0;
    }

    for (solverNode*& curr : set)
    {
        if (curr->visited)
            continue;

        DFSHelper(curr, group, set);
        group++;
    }
}
bool solver::shareNumbered(solverNode*& n1, solverNode*& n2, std::vector<solverNode*>& set)
{
    for (const unsigned short& index1 : n1->adjNodes)
    {
        solverNode*& a1 = m_nodes[index1];
        for (const unsigned short& index2 : n2->adjNodes)
        {
            solverNode*& a2 = m_nodes[index2];
            for (solverNode*& s : set)
                if (a1->discovered && a1 == a2 && a1 == s)
                    return true;  
        }
    }
    return false;
}