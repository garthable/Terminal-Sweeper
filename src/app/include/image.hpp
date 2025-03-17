#pragma once

#include <GLFW/glfw3.h>
#include <cstdint>

namespace img
{

class Image
{
public:
    Image(const char* filename);
    ~Image();

    void bind(uint32_t slot = 0);
    void unbind();
    
    void render() const;

private:
    unsigned char* m_ImageBuffer;
    int32_t m_Width;
    int32_t m_Height;

    uint32_t m_ImageId;
    uint32_t m_Slot;

    bool m_Bound;
};

} // img end