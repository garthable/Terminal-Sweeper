#include "util.h"

unsigned short getBombCount(const std::vector<bool>& v)
{
    unsigned short bombCount = 0;
    for (const bool& b : v)
        bombCount += b;
    return bombCount;
}

unsigned short findMaxInVector(const std::vector<std::vector<bool>>& input)
{
    unsigned short max = 0;
    for (const std::vector<bool>& v : input)
    {
        unsigned short bCount = getBombCount(v);
        if (bCount > max)
            max = bCount;
    }
    return max;
}

unsigned short findMaxAmountBetweenVectors(const std::vector<std::vector<std::vector<bool>>>& input)
{
    unsigned short sum;
    for (const std::vector<std::vector<bool>>& v : input)
        sum += findMaxInVector(v);
    return sum;
}

inline std::vector<bool> combineBoolVectors(const std::vector<bool>& A, const std::vector<bool>& B)
{
    std::vector<bool> AB;
    AB.reserve( A.size() + B.size() ); // preallocate memory

    for (const bool& isBomb : A)
        AB.push_back(isBomb);
    
    for (const bool& isBomb : B)
        AB.push_back(isBomb);

    return AB;
}

std::vector<std::vector<bool>> combineSolutions(const std::vector<std::vector<bool>> &a, const std::vector<std::vector<bool>> &b, const unsigned short& max)
{
    if (a.size() == 0)
        return b;
    else if (b.size() == 0)
        return a;
    
    std::vector<std::vector<bool>> combined;
    combined.reserve(a.size() * b.size());
    for (const std::vector<bool>& va : a)
    {
        unsigned short vaBombCount = getBombCount(va);
        for (const std::vector<bool>& vb : b)
        {
            unsigned short vbBombCount = getBombCount(vb);
            if (max < vbBombCount + vaBombCount)
                continue;

            combined.push_back(combineBoolVectors(va, vb));
        }
    }

    return combined;
}

std::vector<std::vector<bool>> combineAll(const std::vector<std::vector<std::vector<bool>>>& p_vectors, const unsigned short& max)
{
    std::vector<std::vector<bool>> r_combined;
    int totalSize = 1;
    for (const std::vector<std::vector<bool>>& vector : p_vectors)
        totalSize *= vector.size();
    r_combined.reserve(totalSize);
    for (const std::vector<std::vector<bool>>& vector : p_vectors)
        r_combined = combineSolutions(r_combined, vector, max);
    return r_combined;
}
