#include <vector>
#include <cmath>
#include <iterator>
#include <iostream>

#define uprint(x) std::cout << x << std::endl

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


void combinationHardcoded(const std::vector<unsigned short>& arr, const int& r, std::vector<std::vector<unsigned short>>& subsets)
{
    unsigned short s = (arr.size()-1);
    unsigned short v = s*8 + (r-1); 

    switch (v)
    {
    case 0:
        subsets = {{arr[0]}};
        break;

    case 8:
        subsets = {{arr[0]}, {arr[1]}};
        break;

    case 9:
        subsets = {{arr[0], arr[1]}};
        break;

    case 16:
        subsets = {{arr[0]}, {arr[1]}, {arr[2]}};
        break;

    case 17:
        subsets = {{arr[0], arr[1]}, {arr[0], arr[2]}, {arr[1], arr[2]}};
        break;

    case 18:
        subsets = {{arr[0], arr[1], arr[2]}};
        break;

    case 24:
        subsets = {{arr[0]}, {arr[1]}, {arr[2]}, {arr[3]}};
        break;

    case 25:
        subsets = {{arr[0], arr[1]}, {arr[0], arr[2]}, {arr[0], arr[3]}, {arr[1], arr[2]}, {arr[1], arr[3]}, {arr[2], arr[3]}};
        break;

    case 26:
        subsets = {{arr[0], arr[1], arr[2]}, {arr[0], arr[1], arr[3]}, {arr[0], arr[2], arr[3]}, {arr[1], arr[2], arr[3]}};
        break;

    case 27:
        subsets = {{arr[0], arr[1], arr[2], arr[3]}};
        break;

    case 32:
        subsets = {{arr[0]}, {arr[1]}, {arr[2]}, {arr[3]}, {arr[4]}};
        break;

    case 33:
        subsets = {{arr[0], arr[1]}, {arr[0], arr[2]}, {arr[0], arr[3]}, {arr[0], arr[4]}, {arr[1], arr[2]}, {arr[1], arr[3]}, {arr[1], arr[4]}, {arr[2], arr[3]}, {arr[2], arr[4]}, {arr[3], arr[4]}};
        break;

    case 34:
        subsets = {{arr[0], arr[1], arr[2]}, {arr[0], arr[1], arr[3]}, {arr[0], arr[1], arr[4]}, {arr[0], arr[2], arr[3]}, {arr[0], arr[2], arr[4]}, {arr[0], arr[3], arr[4]}, {arr[1], arr[2], arr[3]}, {arr[1], arr[2], arr[4]}, {arr[1], arr[3], arr[4]}, {arr[2], arr[3], arr[4]}};
        break;

    case 35:
        subsets = {{arr[0], arr[1], arr[2], arr[3]}, {arr[0], arr[1], arr[2], arr[4]}, {arr[0], arr[1], arr[3], arr[4]}, {arr[0], arr[2], arr[3], arr[4]}, {arr[1], arr[2], arr[3], arr[4]}};
        break;

    case 36:
        subsets = {{arr[0], arr[1], arr[2], arr[3], arr[4]}};
        break;

    case 40:
        subsets = {{arr[0]}, {arr[1]}, {arr[2]}, {arr[3]}, {arr[4]}, {arr[5]}};
        break;

    case 41:
        subsets = {{arr[0], arr[1]}, {arr[0], arr[2]}, {arr[0], arr[3]}, {arr[0], arr[4]}, {arr[0], arr[5]}, {arr[1], arr[2]}, {arr[1], arr[3]}, {arr[1], arr[4]}, {arr[1], arr[5]}, {arr[2], arr[3]}, {arr[2], arr[4]}, {arr[2], arr[5]}, {arr[3], arr[4]}, {arr[3], arr[5]}, {arr[4], arr[5]}};
        break;

    case 42:
        subsets = {{arr[0], arr[1], arr[2]}, {arr[0], arr[1], arr[3]}, {arr[0], arr[1], arr[4]}, {arr[0], arr[1], arr[5]}, {arr[0], arr[2], arr[3]}, {arr[0], arr[2], arr[4]}, {arr[0], arr[2], arr[5]}, {arr[0], arr[3], arr[4]}, {arr[0], arr[3], arr[5]}, {arr[0], arr[4], arr[5]}, {arr[1], arr[2], arr[3]}, {arr[1], arr[2], arr[4]}, {arr[1], arr[2], arr[5]}, {arr[1], arr[3], arr[4]}, {arr[1], arr[3], arr[5]}, {arr[1], arr[4], arr[5]}, {arr[2], arr[3], arr[4]}, {arr[2], arr[3], arr[5]}, {arr[2], arr[4], arr[5]}, {arr[3], arr[4], arr[5]}};
        break;

    case 43:
        subsets = {{arr[0], arr[1], arr[2], arr[3]}, {arr[0], arr[1], arr[2], arr[4]}, {arr[0], arr[1], arr[2], arr[5]}, {arr[0], arr[1], arr[3], arr[4]}, {arr[0], arr[1], arr[3], arr[5]}, {arr[0], arr[1], arr[4], arr[5]}, {arr[0], arr[2], arr[3], arr[4]}, {arr[0], arr[2], arr[3], arr[5]}, {arr[0], arr[2], arr[4], arr[5]}, {arr[0], arr[3], arr[4], arr[5]}, {arr[1], arr[2], arr[3], arr[4]}, {arr[1], arr[2], arr[3], arr[5]}, {arr[1], arr[2], arr[4], arr[5]}, {arr[1], arr[3], arr[4], arr[5]}, {arr[2], arr[3], arr[4], arr[5]}};
        break;

    case 44:
        subsets = {{arr[0], arr[1], arr[2], arr[3], arr[4]}, {arr[0], arr[1], arr[2], arr[3], arr[5]}, {arr[0], arr[1], arr[2], arr[4], arr[5]}, {arr[0], arr[1], arr[3], arr[4], arr[5]}, {arr[0], arr[2], arr[3], arr[4], arr[5]}, {arr[1], arr[2], arr[3], arr[4], arr[5]}};
        break;

    case 45:
        subsets = {{arr[0], arr[1], arr[2], arr[3], arr[4], arr[5]}};
        break;

    case 48:
        subsets = {{arr[0]}, {arr[1]}, {arr[2]}, {arr[3]}, {arr[4]}, {arr[5]}, {arr[6]}};
        break;

    case 49:
        subsets = {{arr[0], arr[1]}, {arr[0], arr[2]}, {arr[0], arr[3]}, {arr[0], arr[4]}, {arr[0], arr[5]}, {arr[0], arr[6]}, {arr[1], arr[2]}, {arr[1], arr[3]}, {arr[1], arr[4]}, {arr[1], arr[5]}, {arr[1], arr[6]}, {arr[2], arr[3]}, {arr[2], arr[4]}, {arr[2], arr[5]}, {arr[2], arr[6]}, {arr[3], arr[4]}, {arr[3], arr[5]}, {arr[3], arr[6]}, {arr[4], arr[5]}, {arr[4], arr[6]}, {arr[5], arr[6]}};
        break;

    case 50:
        subsets = {{arr[0], arr[1], arr[2]}, {arr[0], arr[1], arr[3]}, {arr[0], arr[1], arr[4]}, {arr[0], arr[1], arr[5]}, {arr[0], arr[1], arr[6]}, {arr[0], arr[2], arr[3]}, {arr[0], arr[2], arr[4]}, {arr[0], arr[2], arr[5]}, {arr[0], arr[2], arr[6]}, {arr[0], arr[3], arr[4]}, {arr[0], arr[3], arr[5]}, {arr[0], arr[3], arr[6]}, {arr[0], arr[4], arr[5]}, {arr[0], arr[4], arr[6]}, {arr[0], arr[5], arr[6]}, {arr[1], arr[2], arr[3]}, {arr[1], arr[2], arr[4]}, {arr[1], arr[2], arr[5]}, {arr[1], arr[2], arr[6]}, {arr[1], arr[3], arr[4]}, {arr[1], arr[3], arr[5]}, {arr[1], arr[3], arr[6]}, {arr[1], arr[4], arr[5]}, {arr[1], arr[4], arr[6]}, {arr[1], arr[5], arr[6]}, {arr[2], arr[3], arr[4]}, {arr[2], arr[3], arr[5]}, {arr[2], arr[3], arr[6]}, {arr[2], arr[4], arr[5]}, {arr[2], arr[4], arr[6]}, {arr[2], arr[5], arr[6]}, {arr[3], arr[4], arr[5]}, {arr[3], arr[4], arr[6]}, {arr[3], arr[5], arr[6]}, {arr[4], arr[5], arr[6]}};
        break;

    case 51:
        subsets = {{arr[0], arr[1], arr[2], arr[3]}, {arr[0], arr[1], arr[2], arr[4]}, {arr[0], arr[1], arr[2], arr[5]}, {arr[0], arr[1], arr[2], arr[6]}, {arr[0], arr[1], arr[3], arr[4]}, {arr[0], arr[1], arr[3], arr[5]}, {arr[0], arr[1], arr[3], arr[6]}, {arr[0], arr[1], arr[4], arr[5]}, {arr[0], arr[1], arr[4], arr[6]}, {arr[0], arr[1], arr[5], arr[6]}, {arr[0], arr[2], arr[3], arr[4]}, {arr[0], arr[2], arr[3], arr[5]}, {arr[0], arr[2], arr[3], arr[6]}, {arr[0], arr[2], arr[4], arr[5]}, {arr[0], arr[2], arr[4], arr[6]}, {arr[0], arr[2], arr[5], arr[6]}, {arr[0], arr[3], arr[4], arr[5]}, {arr[0], arr[3], arr[4], arr[6]}, {arr[0], arr[3], arr[5], arr[6]}, {arr[0], arr[4], arr[5], arr[6]}, {arr[1], arr[2], arr[3], arr[4]}, {arr[1], arr[2], arr[3], arr[5]}, {arr[1], arr[2], arr[3], arr[6]}, {arr[1], arr[2], arr[4], arr[5]}, {arr[1], arr[2], arr[4], arr[6]}, {arr[1], arr[2], arr[5], arr[6]}, {arr[1], arr[3], arr[4], arr[5]}, {arr[1], arr[3], arr[4], arr[6]}, {arr[1], arr[3], arr[5], arr[6]}, {arr[1], arr[4], arr[5], arr[6]}, {arr[2], arr[3], arr[4], arr[5]}, {arr[2], arr[3], arr[4], arr[6]}, {arr[2], arr[3], arr[5], arr[6]}, {arr[2], arr[4], arr[5], arr[6]}, {arr[3], arr[4], arr[5], arr[6]}};
        break;

    case 52:
        subsets = {{arr[0], arr[1], arr[2], arr[3], arr[4]}, {arr[0], arr[1], arr[2], arr[3], arr[5]}, {arr[0], arr[1], arr[2], arr[3], arr[6]}, {arr[0], arr[1], arr[2], arr[4], arr[5]}, {arr[0], arr[1], arr[2], arr[4], arr[6]}, {arr[0], arr[1], arr[2], arr[5], arr[6]}, {arr[0], arr[1], arr[3], arr[4], arr[5]}, {arr[0], arr[1], arr[3], arr[4], arr[6]}, {arr[0], arr[1], arr[3], arr[5], arr[6]}, {arr[0], arr[1], arr[4], arr[5], arr[6]}, {arr[0], arr[2], arr[3], arr[4], arr[5]}, {arr[0], arr[2], arr[3], arr[4], arr[6]}, {arr[0], arr[2], arr[3], arr[5], arr[6]}, {arr[0], arr[2], arr[4], arr[5], arr[6]}, {arr[0], arr[3], arr[4], arr[5], arr[6]}, {arr[1], arr[2], arr[3], arr[4], arr[5]}, {arr[1], arr[2], arr[3], arr[4], arr[6]}, {arr[1], arr[2], arr[3], arr[5], arr[6]}, {arr[1], arr[2], arr[4], arr[5], arr[6]}, {arr[1], arr[3], arr[4], arr[5], arr[6]}, {arr[2], arr[3], arr[4], arr[5], arr[6]}};
        break;

    case 53:
        subsets = {{arr[0], arr[1], arr[2], arr[3], arr[4], arr[5]}, {arr[0], arr[1], arr[2], arr[3], arr[4], arr[6]}, {arr[0], arr[1], arr[2], arr[3], arr[5], arr[6]}, {arr[0], arr[1], arr[2], arr[4], arr[5], arr[6]}, {arr[0], arr[1], arr[3], arr[4], arr[5], arr[6]}, {arr[0], arr[2], arr[3], arr[4], arr[5], arr[6]}, {arr[1], arr[2], arr[3], arr[4], arr[5], arr[6]}};
        break;

    case 54:
        subsets = {{arr[0], arr[1], arr[2], arr[3], arr[4], arr[5], arr[6]}};
        break;

    case 56:
        subsets = {{arr[0]}, {arr[1]}, {arr[2]}, {arr[3]}, {arr[4]}, {arr[5]}, {arr[6]}, {arr[7]}};
        break;

    case 57:
        subsets = {{arr[0], arr[1]}, {arr[0], arr[2]}, {arr[0], arr[3]}, {arr[0], arr[4]}, {arr[0], arr[5]}, {arr[0], arr[6]}, {arr[0], arr[7]}, {arr[1], arr[2]}, {arr[1], arr[3]}, {arr[1], arr[4]}, {arr[1], arr[5]}, {arr[1], arr[6]}, {arr[1], arr[7]}, {arr[2], arr[3]}, {arr[2], arr[4]}, {arr[2], arr[5]}, {arr[2], arr[6]}, {arr[2], arr[7]}, {arr[3], arr[4]}, {arr[3], arr[5]}, {arr[3], arr[6]}, {arr[3], arr[7]}, {arr[4], arr[5]}, {arr[4], arr[6]}, {arr[4], arr[7]}, {arr[5], arr[6]}, {arr[5], arr[7]}, {arr[6], arr[7]}};
        break;

    case 58:
        subsets = {{arr[0], arr[1], arr[2]}, {arr[0], arr[1], arr[3]}, {arr[0], arr[1], arr[4]}, {arr[0], arr[1], arr[5]}, {arr[0], arr[1], arr[6]}, {arr[0], arr[1], arr[7]}, {arr[0], arr[2], arr[3]}, {arr[0], arr[2], arr[4]}, {arr[0], arr[2], arr[5]}, {arr[0], arr[2], arr[6]}, {arr[0], arr[2], arr[7]}, {arr[0], arr[3], arr[4]}, {arr[0], arr[3], arr[5]}, {arr[0], arr[3], arr[6]}, {arr[0], arr[3], arr[7]}, {arr[0], arr[4], arr[5]}, {arr[0], arr[4], arr[6]}, {arr[0], arr[4], arr[7]}, {arr[0], arr[5], arr[6]}, {arr[0], arr[5], arr[7]}, {arr[0], arr[6], arr[7]}, {arr[1], arr[2], arr[3]}, {arr[1], arr[2], arr[4]}, {arr[1], arr[2], arr[5]}, {arr[1], arr[2], arr[6]}, {arr[1], arr[2], arr[7]}, {arr[1], arr[3], arr[4]}, {arr[1], arr[3], arr[5]}, {arr[1], arr[3], arr[6]}, {arr[1], arr[3], arr[7]}, {arr[1], arr[4], arr[5]}, {arr[1], arr[4], arr[6]}, {arr[1], arr[4], arr[7]}, {arr[1], arr[5], arr[6]}, {arr[1], arr[5], arr[7]}, {arr[1], arr[6], arr[7]}, {arr[2], arr[3], arr[4]}, {arr[2], arr[3], arr[5]}, {arr[2], arr[3], arr[6]}, {arr[2], arr[3], arr[7]}, {arr[2], arr[4], arr[5]}, {arr[2], arr[4], arr[6]}, {arr[2], arr[4], arr[7]}, {arr[2], arr[5], arr[6]}, {arr[2], arr[5], arr[7]}, {arr[2], arr[6], arr[7]}, {arr[3], arr[4], arr[5]}, {arr[3], arr[4], arr[6]}, {arr[3], arr[4], arr[7]}, {arr[3], arr[5], arr[6]}, {arr[3], arr[5], arr[7]}, {arr[3], arr[6], arr[7]}, {arr[4], arr[5], arr[6]}, {arr[4], arr[5], arr[7]}, {arr[4], arr[6], arr[7]}, {arr[5], arr[6], arr[7]}};
        break;

    case 59:
        subsets = {{arr[0], arr[1], arr[2], arr[3]}, {arr[0], arr[1], arr[2], arr[4]}, {arr[0], arr[1], arr[2], arr[5]}, {arr[0], arr[1], arr[2], arr[6]}, {arr[0], arr[1], arr[2], arr[7]}, {arr[0], arr[1], arr[3], arr[4]}, {arr[0], arr[1], arr[3], arr[5]}, {arr[0], arr[1], arr[3], arr[6]}, {arr[0], arr[1], arr[3], arr[7]}, {arr[0], arr[1], arr[4], arr[5]}, {arr[0], arr[1], arr[4], arr[6]}, {arr[0], arr[1], arr[4], arr[7]}, {arr[0], arr[1], arr[5], arr[6]}, {arr[0], arr[1], arr[5], arr[7]}, {arr[0], arr[1], arr[6], arr[7]}, {arr[0], arr[2], arr[3], arr[4]}, {arr[0], arr[2], arr[3], arr[5]}, {arr[0], arr[2], arr[3], arr[6]}, {arr[0], arr[2], arr[3], arr[7]}, {arr[0], arr[2], arr[4], arr[5]}, {arr[0], arr[2], arr[4], arr[6]}, {arr[0], arr[2], arr[4], arr[7]}, {arr[0], arr[2], arr[5], arr[6]}, {arr[0], arr[2], arr[5], arr[7]}, {arr[0], arr[2], arr[6], arr[7]}, {arr[0], arr[3], arr[4], arr[5]}, {arr[0], arr[3], arr[4], arr[6]}, {arr[0], arr[3], arr[4], arr[7]}, {arr[0], arr[3], arr[5], arr[6]}, {arr[0], arr[3], arr[5], arr[7]}, {arr[0], arr[3], arr[6], arr[7]}, {arr[0], arr[4], arr[5], arr[6]}, {arr[0], arr[4], arr[5], arr[7]}, {arr[0], arr[4], arr[6], arr[7]}, {arr[0], arr[5], arr[6], arr[7]}, {arr[1], arr[2], arr[3], arr[4]}, {arr[1], arr[2], arr[3], arr[5]}, {arr[1], arr[2], arr[3], arr[6]}, {arr[1], arr[2], arr[3], arr[7]}, {arr[1], arr[2], arr[4], arr[5]}, {arr[1], arr[2], arr[4], arr[6]}, {arr[1], arr[2], arr[4], arr[7]}, {arr[1], arr[2], arr[5], arr[6]}, {arr[1], arr[2], arr[5], arr[7]}, {arr[1], arr[2], arr[6], arr[7]}, {arr[1], arr[3], arr[4], arr[5]}, {arr[1], arr[3], arr[4], arr[6]}, {arr[1], arr[3], arr[4], arr[7]}, {arr[1], arr[3], arr[5], arr[6]}, {arr[1], arr[3], arr[5], arr[7]}, {arr[1], arr[3], arr[6], arr[7]}, {arr[1], arr[4], arr[5], arr[6]}, {arr[1], arr[4], arr[5], arr[7]}, {arr[1], arr[4], arr[6], arr[7]}, {arr[1], arr[5], arr[6], arr[7]}, {arr[2], arr[3], arr[4], arr[5]}, {arr[2], arr[3], arr[4], arr[6]}, {arr[2], arr[3], arr[4], arr[7]}, {arr[2], arr[3], arr[5], arr[6]}, {arr[2], arr[3], arr[5], arr[7]}, {arr[2], arr[3], arr[6], arr[7]}, {arr[2], arr[4], arr[5], arr[6]}, {arr[2], arr[4], arr[5], arr[7]}, {arr[2], arr[4], arr[6], arr[7]}, {arr[2], arr[5], arr[6], arr[7]}, {arr[3], arr[4], arr[5], arr[6]}, {arr[3], arr[4], arr[5], arr[7]}, {arr[3], arr[4], arr[6], arr[7]}, {arr[3], arr[5], arr[6], arr[7]}, {arr[4], arr[5], arr[6], arr[7]}};
        break;

    case 60:
        subsets = {{arr[0], arr[1], arr[2], arr[3], arr[4]}, {arr[0], arr[1], arr[2], arr[3], arr[5]}, {arr[0], arr[1], arr[2], arr[3], arr[6]}, {arr[0], arr[1], arr[2], arr[3], arr[7]}, {arr[0], arr[1], arr[2], arr[4], arr[5]}, {arr[0], arr[1], arr[2], arr[4], arr[6]}, {arr[0], arr[1], arr[2], arr[4], arr[7]}, {arr[0], arr[1], arr[2], arr[5], arr[6]}, {arr[0], arr[1], arr[2], arr[5], arr[7]}, {arr[0], arr[1], arr[2], arr[6], arr[7]}, {arr[0], arr[1], arr[3], arr[4], arr[5]}, {arr[0], arr[1], arr[3], arr[4], arr[6]}, {arr[0], arr[1], arr[3], arr[4], arr[7]}, {arr[0], arr[1], arr[3], arr[5], arr[6]}, {arr[0], arr[1], arr[3], arr[5], arr[7]}, {arr[0], arr[1], arr[3], arr[6], arr[7]}, {arr[0], arr[1], arr[4], arr[5], arr[6]}, {arr[0], arr[1], arr[4], arr[5], arr[7]}, {arr[0], arr[1], arr[4], arr[6], arr[7]}, {arr[0], arr[1], arr[5], arr[6], arr[7]}, {arr[0], arr[2], arr[3], arr[4], arr[5]}, {arr[0], arr[2], arr[3], arr[4], arr[6]}, {arr[0], arr[2], arr[3], arr[4], arr[7]}, {arr[0], arr[2], arr[3], arr[5], arr[6]}, {arr[0], arr[2], arr[3], arr[5], arr[7]}, {arr[0], arr[2], arr[3], arr[6], arr[7]}, {arr[0], arr[2], arr[4], arr[5], arr[6]}, {arr[0], arr[2], arr[4], arr[5], arr[7]}, {arr[0], arr[2], arr[4], arr[6], arr[7]}, {arr[0], arr[2], arr[5], arr[6], arr[7]}, {arr[0], arr[3], arr[4], arr[5], arr[6]}, {arr[0], arr[3], arr[4], arr[5], arr[7]}, {arr[0], arr[3], arr[4], arr[6], arr[7]}, {arr[0], arr[3], arr[5], arr[6], arr[7]}, {arr[0], arr[4], arr[5], arr[6], arr[7]}, {arr[1], arr[2], arr[3], arr[4], arr[5]}, {arr[1], arr[2], arr[3], arr[4], arr[6]}, {arr[1], arr[2], arr[3], arr[4], arr[7]}, {arr[1], arr[2], arr[3], arr[5], arr[6]}, {arr[1], arr[2], arr[3], arr[5], arr[7]}, {arr[1], arr[2], arr[3], arr[6], arr[7]}, {arr[1], arr[2], arr[4], arr[5], arr[6]}, {arr[1], arr[2], arr[4], arr[5], arr[7]}, {arr[1], arr[2], arr[4], arr[6], arr[7]}, {arr[1], arr[2], arr[5], arr[6], arr[7]}, {arr[1], arr[3], arr[4], arr[5], arr[6]}, {arr[1], arr[3], arr[4], arr[5], arr[7]}, {arr[1], arr[3], arr[4], arr[6], arr[7]}, {arr[1], arr[3], arr[5], arr[6], arr[7]}, {arr[1], arr[4], arr[5], arr[6], arr[7]}, {arr[2], arr[3], arr[4], arr[5], arr[6]}, {arr[2], arr[3], arr[4], arr[5], arr[7]}, {arr[2], arr[3], arr[4], arr[6], arr[7]}, {arr[2], arr[3], arr[5], arr[6], arr[7]}, {arr[2], arr[4], arr[5], arr[6], arr[7]}, {arr[3], arr[4], arr[5], arr[6], arr[7]}};
        break;

    case 61:
        subsets = {{arr[0], arr[1], arr[2], arr[3], arr[4], arr[5]}, {arr[0], arr[1], arr[2], arr[3], arr[4], arr[6]}, {arr[0], arr[1], arr[2], arr[3], arr[4], arr[7]}, {arr[0], arr[1], arr[2], arr[3], arr[5], arr[6]}, {arr[0], arr[1], arr[2], arr[3], arr[5], arr[7]}, {arr[0], arr[1], arr[2], arr[3], arr[6], arr[7]}, {arr[0], arr[1], arr[2], arr[4], arr[5], arr[6]}, {arr[0], arr[1], arr[2], arr[4], arr[5], arr[7]}, {arr[0], arr[1], arr[2], arr[4], arr[6], arr[7]}, {arr[0], arr[1], arr[2], arr[5], arr[6], arr[7]}, {arr[0], arr[1], arr[3], arr[4], arr[5], arr[6]}, {arr[0], arr[1], arr[3], arr[4], arr[5], arr[7]}, {arr[0], arr[1], arr[3], arr[4], arr[6], arr[7]}, {arr[0], arr[1], arr[3], arr[5], arr[6], arr[7]}, {arr[0], arr[1], arr[4], arr[5], arr[6], arr[7]}, {arr[0], arr[2], arr[3], arr[4], arr[5], arr[6]}, {arr[0], arr[2], arr[3], arr[4], arr[5], arr[7]}, {arr[0], arr[2], arr[3], arr[4], arr[6], arr[7]}, {arr[0], arr[2], arr[3], arr[5], arr[6], arr[7]}, {arr[0], arr[2], arr[4], arr[5], arr[6], arr[7]}, {arr[0], arr[3], arr[4], arr[5], arr[6], arr[7]}, {arr[1], arr[2], arr[3], arr[4], arr[5], arr[6]}, {arr[1], arr[2], arr[3], arr[4], arr[5], arr[7]}, {arr[1], arr[2], arr[3], arr[4], arr[6], arr[7]}, {arr[1], arr[2], arr[3], arr[5], arr[6], arr[7]}, {arr[1], arr[2], arr[4], arr[5], arr[6], arr[7]}, {arr[1], arr[3], arr[4], arr[5], arr[6], arr[7]}, {arr[2], arr[3], arr[4], arr[5], arr[6], arr[7]}};
        break;

    case 62:
        subsets = {{arr[0], arr[1], arr[2], arr[3], arr[4], arr[5], arr[6]}, {arr[0], arr[1], arr[2], arr[3], arr[4], arr[5], arr[7]}, {arr[0], arr[1], arr[2], arr[3], arr[4], arr[6], arr[7]}, {arr[0], arr[1], arr[2], arr[3], arr[5], arr[6], arr[7]}, {arr[0], arr[1], arr[2], arr[4], arr[5], arr[6], arr[7]}, {arr[0], arr[1], arr[3], arr[4], arr[5], arr[6], arr[7]}, {arr[0], arr[2], arr[3], arr[4], arr[5], arr[6], arr[7]}, {arr[1], arr[2], arr[3], arr[4], arr[5], arr[6], arr[7]}};
        break;

    case 63:
        subsets = {{arr[0], arr[1], arr[2], arr[3], arr[4], arr[5], arr[6], arr[7]}};
        break;
    default:
        subsets = {{}};
        break;
    }
}

unsigned short combinationValueHardcoded(const std::vector<unsigned short>& arr, const unsigned short& r)
{
    unsigned short s = (arr.size()-1);
    unsigned short v = s*8 + (r-1); 

    switch (v)
    {
    case 0:
        return 1;
        break;

    case 8:
        return 2;
        break;

    case 9:
        return 1;
        break;

    case 16:
        return 3;
        break;

    case 17:
        return 3;
        break;

    case 18:
        return 1;
        break;

    case 24:
        return 4;
        break;

    case 25:
        return 6;
        break;

    case 26:
        return 4;
        break;

    case 27:
        return 1;
        break;

    case 32:
        return 5;
        break;

    case 33:
        return 10;
        break;

    case 34:
        return 10;
        break;

    case 35:
        return 5;
        break;

    case 36:
        return 1;
        break;

    case 40:
        return 6;
        break;

    case 41:
        return 15;
        break;

    case 42:
        return 20;
        break;

    case 43:
        return 15;
        break;

    case 44:
        return 6;
        break;

    case 45:
        return 1;
        break;

    case 48:
        return 7;
        break;

    case 49:
        return 21;
        break;

    case 50:
        return 35;
        break;

    case 51:
        return 35;
        break;

    case 52:
        return 21;
        break;

    case 53:
        return 7;
        break;

    case 54:
        return 1;
        break;

    case 56:
        return 8;
        break;

    case 57:
        return 28;
        break;

    case 58:
        return 56;
        break;

    case 59:
        return 70;
        break;

    case 60:
        return 56;
        break;

    case 61:
        return 28;
        break;

    case 62:
        return 8;
        break;

    case 63:
        return 1;
        break;
    
    default:
        return 0;
        break;
    }
}
