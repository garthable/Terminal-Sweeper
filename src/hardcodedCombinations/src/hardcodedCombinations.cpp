#include "hardcodedCombinations.hpp"

const uint8_t* getCombinations(uint8_t r)
{
    static const uint8_t hardCodedCombinations[1032] = {0, 9, 1, 2, 3, 4, 5, 6, 7, 9, 1, 0, 2, 0, 2, 1, 3, 0, 3, 1, 3, 2, 4, 0, 4, 1, 4, 2, 4, 3, 5, 0, 5, 1, 5, 2, 5, 3, 5, 4, 6, 0, 6, 1, 6, 2, 6, 3, 6, 4, 6, 5, 7, 0, 7, 1, 7, 2, 7, 3, 7, 4, 7, 5, 7, 6, 9, 2, 1, 0, 3, 1, 0, 3, 2, 0, 3, 2, 1, 4, 1, 0, 4, 2, 0, 4, 2, 1, 4, 3, 0, 4, 3, 1, 4, 3, 2, 5, 1, 0, 5, 2, 0, 5, 2, 1, 5, 3, 0, 5, 3, 1, 5, 3, 2, 5, 4, 0, 5, 4, 1, 5, 4, 2, 5, 4, 3, 6, 1, 0, 6, 2, 0, 6, 2, 1, 6, 3, 0, 6, 3, 1, 6, 3, 2, 6, 4, 0, 6, 4, 1, 6, 4, 2, 6, 4, 3, 6, 5, 0, 6, 5, 1, 6, 5, 2, 6, 5, 3, 6, 5, 4, 7, 1, 0, 7, 2, 0, 7, 2, 1, 7, 3, 0, 7, 3, 1, 7, 3, 2, 7, 4, 0, 7, 4, 1, 7, 4, 2, 7, 4, 3, 7, 5, 0, 7, 5, 1, 7, 5, 2, 7, 5, 3, 7, 5, 4, 7, 6, 0, 7, 6, 1, 7, 6, 2, 7, 6, 3, 7, 6, 4, 7, 6, 5, 9, 3, 2, 1, 0, 4, 2, 1, 0, 4, 3, 1, 0, 4, 3, 2, 0, 4, 3, 2, 1, 5, 2, 1, 0, 5, 3, 1, 0, 5, 3, 2, 0, 5, 3, 2, 1, 5, 4, 1, 0, 5, 4, 2, 0, 5, 4, 2, 1, 5, 4, 3, 0, 5, 4, 3, 1, 5, 4, 3, 2, 6, 2, 1, 0, 6, 3, 1, 0, 6, 3, 2, 0, 6, 3, 2, 1, 6, 4, 1, 0, 6, 4, 2, 0, 6, 4, 2, 1, 6, 4, 3, 0, 6, 4, 3, 1, 6, 4, 3, 2, 6, 5, 1, 0, 6, 5, 2, 0, 6, 5, 2, 1, 6, 5, 3, 0, 6, 5, 3, 1, 6, 5, 3, 2, 6, 5, 4, 0, 6, 5, 4, 1, 6, 5, 4, 2, 6, 5, 4, 3, 7, 2, 1, 0, 7, 3, 1, 0, 7, 3, 2, 0, 7, 3, 2, 1, 7, 4, 1, 0, 7, 4, 2, 0, 7, 4, 2, 1, 7, 4, 3, 0, 7, 4, 3, 1, 7, 4, 3, 2, 7, 5, 1, 0, 7, 5, 2, 0, 7, 5, 2, 1, 7, 5, 3, 0, 7, 5, 3, 1, 7, 5, 3, 2, 7, 5, 4, 0, 7, 5, 4, 1, 7, 5, 4, 2, 7, 5, 4, 3, 7, 6, 1, 0, 7, 6, 2, 0, 7, 6, 2, 1, 7, 6, 3, 0, 7, 6, 3, 1, 7, 6, 3, 2, 7, 6, 4, 0, 7, 6, 4, 1, 7, 6, 4, 2, 7, 6, 4, 3, 7, 6, 5, 0, 7, 6, 5, 1, 7, 6, 5, 2, 7, 6, 5, 3, 7, 6, 5, 4, 9, 4, 3, 2, 1, 0, 5, 3, 2, 1, 0, 5, 4, 2, 1, 0, 5, 4, 3, 1, 0, 5, 4, 3, 2, 0, 5, 4, 3, 2, 1, 6, 3, 2, 1, 0, 6, 4, 2, 1, 0, 6, 4, 3, 1, 0, 6, 4, 3, 2, 0, 6, 4, 3, 2, 1, 6, 5, 2, 1, 0, 6, 5, 3, 1, 0, 6, 5, 3, 2, 0, 6, 5, 3, 2, 1, 6, 5, 4, 1, 0, 6, 5, 4, 2, 0, 6, 5, 4, 2, 1, 6, 5, 4, 3, 0, 6, 5, 4, 3, 1, 6, 5, 4, 3, 2, 7, 3, 2, 1, 0, 7, 4, 2, 1, 0, 7, 4, 3, 1, 0, 7, 4, 3, 2, 0, 7, 4, 3, 2, 1, 7, 5, 2, 1, 0, 7, 5, 3, 1, 0, 7, 5, 3, 2, 0, 7, 5, 3, 2, 1, 7, 5, 4, 1, 0, 7, 5, 4, 2, 0, 7, 5, 4, 2, 1, 7, 5, 4, 3, 0, 7, 5, 4, 3, 1, 7, 5, 4, 3, 2, 7, 6, 2, 1, 0, 7, 6, 3, 1, 0, 7, 6, 3, 2, 0, 7, 6, 3, 2, 1, 7, 6, 4, 1, 0, 7, 6, 4, 2, 0, 7, 6, 4, 2, 1, 7, 6, 4, 3, 0, 7, 6, 4, 3, 1, 7, 6, 4, 3, 2, 7, 6, 5, 1, 0, 7, 6, 5, 2, 0, 7, 6, 5, 2, 1, 7, 6, 5, 3, 0, 7, 6, 5, 3, 1, 7, 6, 5, 3, 2, 7, 6, 5, 4, 0, 7, 6, 5, 4, 1, 7, 6, 5, 4, 2, 7, 6, 5, 4, 3, 9, 5, 4, 3, 2, 1, 0, 6, 4, 3, 2, 1, 0, 6, 5, 3, 2, 1, 0, 6, 5, 4, 2, 1, 0, 6, 5, 4, 3, 1, 0, 6, 5, 4, 3, 2, 0, 6, 5, 4, 3, 2, 1, 7, 4, 3, 2, 1, 0, 7, 5, 3, 2, 1, 0, 7, 5, 4, 2, 1, 0, 7, 5, 4, 3, 1, 0, 7, 5, 4, 3, 2, 0, 7, 5, 4, 3, 2, 1, 7, 6, 3, 2, 1, 0, 7, 6, 4, 2, 1, 0, 7, 6, 4, 3, 1, 0, 7, 6, 4, 3, 2, 0, 7, 6, 4, 3, 2, 1, 7, 6, 5, 2, 1, 0, 7, 6, 5, 3, 1, 0, 7, 6, 5, 3, 2, 0, 7, 6, 5, 3, 2, 1, 7, 6, 5, 4, 1, 0, 7, 6, 5, 4, 2, 0, 7, 6, 5, 4, 2, 1, 7, 6, 5, 4, 3, 0, 7, 6, 5, 4, 3, 1, 7, 6, 5, 4, 3, 2, 9, 6, 5, 4, 3, 2, 1, 0, 7, 5, 4, 3, 2, 1, 0, 7, 6, 4, 3, 2, 1, 0, 7, 6, 5, 3, 2, 1, 0, 7, 6, 5, 4, 2, 1, 0, 7, 6, 5, 4, 3, 1, 0, 7, 6, 5, 4, 3, 2, 0, 7, 6, 5, 4, 3, 2, 1, 7, 6, 5, 4, 3, 2, 1, 0, 9};
    static const uint16_t rToIndex[9] = {0, 10, 67, 236, 517, 798, 967, 1023};
    return &hardCodedCombinations[rToIndex[r-1]];
}