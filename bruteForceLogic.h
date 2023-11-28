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
    unsigned short iD;
    unsigned short number;
    std::vector<unsigned short> attached;
    std::vector<std::vector<unsigned short>> combinations;

    numberedNode(int _iD, int _number)
    {
        iD = _iD;
        number = _number;
    }
};

class bruteForce
{
    public:
        numberedNode* searchNumbered(const unsigned short&);
        unknownNode* searchUnknown(const unsigned short&);

        void addNumbered(const unsigned short&, const unsigned short&, const unsigned short&);
        void addUnknown(const unsigned short&, const unsigned short&, const unsigned short&);

        void sortNumbered(const unsigned short&, std::vector<unknownNode>&);

        bool isValid(const std::vector<numberedNode>&, const std::vector<unknownNode>&);
        void getSolutionsHelper(unsigned short, const std::vector<numberedNode>&, std::vector<unknownNode>, std::vector<std::vector<bool>>&);
        std::vector<std::vector<bool>> getSolutions(const int&);

        void findSafePicks();
        void findSafePicksFast(const std::vector<std::vector<std::vector<bool>>>&);
        void findSafePicksBombCount(const std::vector<std::vector<std::vector<bool>>>&);

        std::vector<probData> getProbdata();

        bruteForce(int);
        ~bruteForce();

    private:
        std::vector<std::vector<numberedNode>> numbered;
        std::vector<std::vector<unknownNode>> unknowns;

        std::vector<probData> probabilities;
        
        int numberCount;
        int unknownCount;
        int bombCount;
};

#endif