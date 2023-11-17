#include <vector>
#include <cmath>
#include <iterator>
#include <iostream>

#ifndef UTIL
#define UTIL

#define uprint(x) std::cout << x << std::endl

bool compareVects(std::vector<int> vector1, std::vector<int> vector2)
{
    for(int a : vector1)
    {
        bool found = false;
        for(int b : vector2)
            if (a == b)
                found = true;
        if (!found)
            return false;
    }
    return true;
}

bool removeInterectionVects(std::vector<int>& set, std::vector<int>& subset)
{
    if (set.size() < subset.size())
        return false;

    bool isSubset = false;
    for (int i : subset)
    {
        for (int j : set)
            if (i == j)
                isSubset = true;
                
        if (!isSubset)
            return false;
    }

    bool deleted = false;
    for (int i = 0; i < subset.size(); i++)
    {
        for (int j = 0; j < set.size(); j++)
        {
            if (set[j] == subset[i])
            {
                set.erase(set.begin() + j);
                deleted = true;
            }
        }
    }
    return deleted;
}

/* arr[] ---> Input Array 
r ---> Size of a combination to be printed 
index ---> Current index in data[] 
data[] ---> Temporary array to store current combination 
i ---> index of current element in arr[] */
void combinationUtil(std::vector<int> arr, int r, 
                    int index, std::vector<int> data, int i, std::vector<std::vector<int>>& subsets) 
{ 
    // Current combination is ready, print it 
    if (index == r) 
    {
        for (std::vector<int> a : subsets)
            if (compareVects(a, data))
                goto loopExit;

        subsets.push_back(std::vector<int>());

        for (int j = 0; j < r; j++)
            subsets[subsets.size() - 1].push_back(data[j]); 

        loopExit:
        return; 
    } 
 
    // When no more elements are there to put in data[] 
    if (i >= arr.size()) 
        return; 
 
    // current is included, put next at next location 
    data[index] = arr[i]; 
    combinationUtil(arr, r, index + 1, data, i + 1, subsets); 
 
    // current is excluded, replace it with next (Note that 
    // i+1 is passed, but index is not changed) 
    combinationUtil(arr, r, index, data, i + 1, subsets); 
} 

void combination(std::vector<int> arr, int r, std::vector<std::vector<int>>& subsets)
{
    std::vector<int> data;
    for (int i = 0; i < r; i++)
        data.push_back(0);
    combinationUtil(arr, r, 0, data, 0, subsets);
}

void combinationHardcoded(std::vector<int> arr, int r, std::vector<std::vector<int>>& subsets)
{
    int s = (arr.size()-1);
    int v = s*8 + (r-1); 

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

bool getBitByte(unsigned char byte, int position) // position in range 0-7
{
    return (byte >> position) & 0x1;
}

bool getBitLong(unsigned long _long, int position)
{
    return (_long >> position) & 0x1;
}

#endif