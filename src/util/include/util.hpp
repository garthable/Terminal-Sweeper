#include <cstdint>
#include <functional>

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