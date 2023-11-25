#include <vector>


#ifndef BRUTEFORCE
#define BRUTEFORCE

struct probData
{
    short iD;
    float probability;

    probData(short i, float p)
    {
        iD = i;
        probability = p;
    }
};

struct unknownNode
{
    short iD;
    bool isBomb;
    bool visited;

    unknownNode(int _iD)
    {
        iD = _iD;
        visited = false;
    }
};

struct numberedNode
{
    short iD;
    short number;
    std::vector<int> attached;
    std::vector<std::vector<int>> combinations;

    numberedNode(int _iD, int _number)
    {
        iD = _iD;
        number = _number;
    }
};

class bruteForce
{
    public:
        numberedNode* searchNumbered(int);
        unknownNode* searchUnknown(int);

        void addNumbered(int, int, int);
        void addUnknown(int, int, int);

        void sortNumbered(int, std::vector<unknownNode>);

        bool isValidUpper(const std::vector<numberedNode>&, const std::vector<unknownNode>&);
        bool isValid(const std::vector<numberedNode>&, const std::vector<unknownNode>&);
        void getSolutionsHelper(int, const std::vector<numberedNode>&, std::vector<unknownNode>, std::vector<std::vector<bool>>&);
        std::vector<std::vector<bool>> getSolutions(int);

        void findSafePicks();
        void findSafePicksFast();
        void findSafePicksBombCount();

        float getProbability(int);

        bruteForce(int);
        ~bruteForce();

    private:
        std::vector<std::vector<numberedNode>> numbered;
        std::vector<std::vector<unknownNode>> unknowns;

        std::vector<probData> probabilities;
        
        int numberCount;
        int bombCount;
};

#endif