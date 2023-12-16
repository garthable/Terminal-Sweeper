#include <vector>


#ifndef PROBABILITYFINDER
#define PROBABILITYFINDER

struct probData
{
    short _solutionNodeIndex;
    float _probability;

    probData(short solutionNodeIndex, float p)
    {
        _solutionNodeIndex = solutionNodeIndex;
        _probability = p;
    }
};

struct unknownNode
{
    short _solutionNodeIndex;
    bool _isBomb;
    bool _visited;

    unknownNode(int solutionNodeIndex)
    {
        _solutionNodeIndex = solutionNodeIndex;
        _visited = false;
    }
};

struct numberedNode
{
    unsigned short _solutionNodeIndex;
    unsigned short _adjBombAmount;
    std::vector<unsigned short> _attached;
    std::vector<std::vector<unsigned short>> _combinations;

    numberedNode(unsigned short solutionNodeIndex, unsigned short adjBombAmount)
    {
        _solutionNodeIndex = solutionNodeIndex;
        _adjBombAmount = adjBombAmount;
    }
};

class probabilityFinder
{
    public:
        void addNumbered(const unsigned short&, const unsigned short&, const unsigned short&);
        void addUnknown(const unsigned short&, const unsigned short&, const unsigned short&);

        void findSafePicks();

        std::vector<probData> getProbdata();

        float getAverageAmountOfBombsUsed();
        unsigned short getMinAmountOfBombsUsed();
        unsigned short getUnknownCount();

        probabilityFinder(int);

    private:
        numberedNode* searchNumbered(const unsigned short&);
        unknownNode* searchUnknown(const unsigned short&);

        void sortNumbered(const unsigned short&, std::vector<unknownNode>&);

        bool isValid(const std::vector<numberedNode>&, const std::vector<unknownNode>&);
        void getSolutionsHelper(unsigned short, const std::vector<numberedNode>&, std::vector<unknownNode>, std::vector<std::vector<bool>>&);
        std::vector<std::vector<bool>> getSolutions(const int&);

        void findSafePicksFast(const std::vector<std::vector<std::vector<bool>>>&);
        void findSafePicksAccountingForBombCount(const std::vector<std::vector<std::vector<bool>>>&);

        float calcAverageBombs(const std::vector<std::vector<std::vector<bool>>>&);
        float calcAverageBombs(const std::vector<std::vector<bool>>&);

        int calcMinBombs(const std::vector<std::vector<bool>>&);

    private:
        std::vector<std::vector<numberedNode>> m_numberedNodesGrouped;
        std::vector<std::vector<unknownNode>> m_unknownNodesGrouped;

        std::vector<probData> m_probabilities;
        
        unsigned short m_adjBombSum;
        unsigned short m_unknownNodeAmount;
        unsigned short m_remainingBombs;
        float m_averageAmountOfBombsUsed;
        unsigned short m_minAmountOfBombsUsed;
};

#endif