#include <vector>

#ifndef BRUTEFORCE
#define BRUTEFORCE

struct unknownNode
{
    int iD;
    int freq;
    bool isBomb;

    unknownNode(int _iD)
    {
        iD = _iD;
    }
};

struct numberedNode
{
    int iD;
    int number;
    int currSol;
    std::vector<unknownNode*> unknownNodes;
    std::vector<std::vector<int>> solutions;

    numberedNode(int _iD, int _number)
    {
        iD = _iD;
        number = _number;
        currSol = 0;
    }
};

class bruteForce
{
    public:
        numberedNode* searchNumbered(int);
        unknownNode* searchUnknown(int);

        void addNumbered(int, int, int);
        void addUnknown(int, int, int);

        void getSolutions();
        void removeSolutions();

        bool validUpperCheck(std::vector<int>, int);
        bool validBelowCheck(std::vector<int>, numberedNode*, int);

        void getStats();
        bool nextBombSet(int);
        bool isValidSolution(int);

        void findSafePicks();
        void findSafePicks2();

        std::vector<int> getBombs();
        std::vector<int> getNotBombs();

        bruteForce();
        ~bruteForce();

    private:
        std::vector<std::vector<numberedNode*>> numbered;
        std::vector<std::vector<unknownNode*>> unknowns;

        std::vector<int> bombs;
        std::vector<int> notBombs;
        int currNode;

        int iteration;
        unsigned long summation;
};

#endif