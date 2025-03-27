#pragma once

#include <cstdint>
#include <functional>
#include <cmath>
#include <initializer_list>

namespace util
{

#define UTIL_WRAP_ONE_ADD(x, modAmount) \
do \
{ \
    x = ((x + 1) % modAmount)*(x < (x + 1));\
} \
while(0)
#define UTIL_WRAP_ONE_SUB(x, modAmount)\
do\
{\
    x = (((x - 1) % modAmount)*(x > (x - 1))) + ((modAmount - 1)*(x <= (x - 1)));\
} \
while(0)

/**
 * @brief Runs func on adjacent elements of index i
 * 
 * @tparam ARRAY object that behaves as an array
 * @tparam OBJECT object in array
 * @param i index of array to center around
 * @param width width
 * @param size size of array
 * @param out array that is modified by function
 * @param func lambda function that modifies array
 */
template<typename ARRAY, typename OBJECT>
inline void applyFuncToAdjObjects(const int32_t i, const int32_t width, const int32_t size, ARRAY& out, std::function<void(OBJECT&)> func)
{
    static constexpr int32_t offsetsX[8] =
    {
        -1,  0, 1,
        -1,     1,
        -1, -0, 1
    };
    const int32_t offsetsY[8] =
    {
         width,  width,  width,
         0,              0,
        -width, -width, -width
    };

    const int32_t x = i % width;

    for (uint8_t j = 0; j < 8; j++)
    {
        int32_t newX = x + offsetsX[j];
        if (newX >= width || newX < 0)
        {
            continue;
        }
        int32_t offset = offsetsX[j] + offsetsY[j];
        int32_t newI = i + offset;
        if (newI >= size || newI < 0)
        {
            continue;
        }
        func(out[newI]);
    }
}

/**
 * @brief Runs func on adjacent elements of index i. Overload that grants lambda function access to index.
 * 
 * @tparam ARRAY object that behaves as an array
 * @tparam OBJECT object in array
 * @param i index of array to center around
 * @param width width
 * @param size size of array
 * @param out array that is modified by function
 * @param func lambda function that modifies array
 */
template<typename ARRAY, typename OBJECT>
inline void applyFuncToAdjObjects(const int32_t i, const int32_t width, const int32_t size, ARRAY& out, std::function<void(int32_t, OBJECT&)> func)
{
    static constexpr int32_t offsetsX[8] =
    {
        -1,  0, 1,
        -1,     1,
        -1, -0, 1
    };
    const int32_t offsetsY[8] =
    {
         width,  width,  width,
         0,              0,
        -width, -width, -width
    };

    const int32_t x = i % width;

    for (uint8_t j = 0; j < 8; j++)
    {
        int32_t newX = x + offsetsX[j];
        if (newX >= width || newX < 0)
        {
            continue;
        }
        int32_t offset = offsetsX[j] + offsetsY[j];
        int32_t newI = i + offset;
        if (newI >= size || newI < 0)
        {
            continue;
        }
        func(newI, out[newI]);
    }
}

/**
 * @brief Runs func on adjacent elements of index i
 * 
 * @tparam ARRAY object that behaves as an array
 * @tparam OBJECT object in array
 * @param i index of array to center around
 * @param width width
 * @param size size of array
 * @param in array that is modified by function
 * @param func lambda function that modifies array
 */
template<typename ARRAY, typename OBJECT>
inline void applyFuncToAdjObjects(const int32_t i, const int32_t width, const int32_t size, const ARRAY& in, std::function<void(const OBJECT&)> func)
{
    static constexpr int32_t offsetsX[8] =
    {
        -1,  0, 1,
        -1,     1,
        -1, -0, 1
    };
    const int32_t offsetsY[8] =
    {
         width,  width,  width,
         0,              0,
        -width, -width, -width
    };

    const int32_t x = i % width;

    for (uint8_t j = 0; j < 8; j++)
    {
        int32_t newX = x + offsetsX[j];
        if (newX >= width || newX < 0)
        {
            continue;
        }
        int32_t offset = offsetsX[j] + offsetsY[j];
        int32_t newI = i + offset;
        if (newI >= size || newI < 0)
        {
            continue;
        }
        func(in[newI]);
    }
}

/**
 * @brief Runs func on adjacent elements of index i. Overload that grants lambda function access to index.
 * 
 * @tparam ARRAY object that behaves as an array
 * @tparam OBJECT object in array
 * @param i index of array to center around
 * @param width width
 * @param size size of array
 * @param in array that is modified by function
 * @param func lambda function that modifies array
 */
template<typename ARRAY, typename OBJECT>
inline void applyFuncToAdjObjects(const int32_t i, const int32_t width, const int32_t size, const ARRAY& in, std::function<void(int32_t, const OBJECT&)> func)
{
    static constexpr int32_t offsetsX[8] =
    {
        -1,  0, 1,
        -1,     1,
        -1, -0, 1
    };
    const int32_t offsetsY[8] =
    {
         width,  width,  width,
         0,              0,
        -width, -width, -width
    };

    const int32_t x = i % width;

    for (uint8_t j = 0; j < 8; j++)
    {
        int32_t newX = x + offsetsX[j];
        if (newX >= width || newX < 0)
        {
            continue;
        }
        int32_t offset = offsetsX[j] + offsetsY[j];
        int32_t newI = i + offset;
        if (newI >= size || newI < 0)
        {
            continue;
        }
        func(newI, in[newI]);
    }
}

/**
 * @brief Checks if index is one chebyshev distance away from center
 * 
 * @param width width of array
 * @param center center to check around
 * @param i index
 * @return true 
 * @return false 
 */
inline bool isIndexNear(int32_t width, int32_t center, int32_t i)
{
    int32_t centerX = center % width;
    int32_t centerY = center / width;
    int32_t indexX = i % width;
    int32_t indexY = i / width;

    int32_t diffX = abs(centerX - indexX);
    int32_t diffY = abs(centerY - indexY);

    return diffX <= 1 && diffY <= 1;
}

/**
 * @brief Multiplies uint8_t's to uint16_t. Prevents overflow
 * 
 * @param a 
 * @param b 
 * @return uint16_t 
 */
inline uint16_t multUi8sToUi16(uint8_t a, uint8_t b)
{
    return static_cast<uint16_t>(a)*static_cast<uint16_t>(b);
}

/**
 * @brief Multiplies int8_t's to int16_t. Prevents overflow
 * 
 * @param a 
 * @param b 
 * @return int16_t 
 */
inline int16_t multI8sToI16(int8_t a, int8_t b)
{
    return static_cast<int16_t>(a)*static_cast<int16_t>(b);
}

/**
 * @brief Converts abc...XYZ to number
 * 
 * @param c letter char
 * @return uint8_t 
 */
inline uint8_t letterToUI8(char c)
{
    if (97 <= c && c <= 122)
    {
        return static_cast<int8_t>(c) - 97;
    }
    else if (65 <= c && c <= 90)
    {
        return static_cast<int8_t>(c) - 65 + 26;
    }
    return 255;
}

/**
 * @brief Converts number to abc...XYZ
 * 
 * @param val number
 * @return uint8_t 
 */
inline char uI8ToLetter(uint8_t val)
{
    if (val <= 25)
    {
        return static_cast<int16_t>(val) + 97;
    }
    else if (26 <= val && val <= 51)
    {
        return static_cast<int16_t>(val) + 65 - 26;
    }
    return 255;
}

/**
 * @brief Get length of const char
 * 
 * @param string 
 * @return constexpr size_t 
 */
inline constexpr size_t getLenStr(const char* string)
{
    return *string ? 1 + getLenStr(string + 1) : 0;
}

/**
 * @brief Find char string of the largest size.
 * 
 * @param strings 
 * @return constexpr size_t 
 */
inline constexpr size_t getMaxLenStr(std::initializer_list<const char*> strings)
{
    size_t maxLength = 0;
    for (size_t i = 0; i < strings.size(); i++)
    {
        const char* string = *(strings.begin() + i);
        size_t length = getLenStr(string);
        if (length > maxLength)
        {
            maxLength = length;
        }
    }
    return maxLength;
}

} // util end