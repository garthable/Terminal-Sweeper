#include <cstdint>
#include <functional>

namespace util
{

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

} // util end