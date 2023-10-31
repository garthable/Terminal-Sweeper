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
    std::vector<unknownNode*> unknownNodes;

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

        void addNumbered(int, int);
        void addUnknown(int, int, int);

        void findSafePicks();
        void findSafePicks2();

        std::vector<int> getBombs();
        std::vector<int> getNotBombs();

        bruteForce();
        ~bruteForce();

    private:
        std::vector<numberedNode*> numbered;
        std::vector<std::vector<unknownNode*>> unknowns;

        std::vector<int> bombs;
        std::vector<int> notBombs;
};

#endif