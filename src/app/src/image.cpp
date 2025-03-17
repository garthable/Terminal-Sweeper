#include "image.hpp"
#include "stb_image.h"
#include <iostream>
#include <unordered_map>

namespace img
{

Image::Image(const char* filename) :
    m_ImageBuffer{nullptr}, m_Width{0}, m_Height{0}, m_ImageId{0}, m_Slot{0}, m_Bound{false}
{
    int32_t colorChannels;
    m_ImageBuffer = stbi_load(filename, &m_Width, &m_Height, &colorChannels, 0);
}

Image::~Image()
{
    if (m_Bound)
    {
        unbind();
    }
    delete m_ImageBuffer;
}

void Image::bind(uint32_t slot)
{
    if (m_Bound)
    {
        throw std::runtime_error("Cannot bind texture while it is still bound!");
    }
    m_Slot = slot;
    glGenTextures(1, &m_ImageId);
    glActiveTexture(m_Slot);
    glBindTexture(m_Slot, m_ImageId);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    m_Bound = true;
}

void Image::unbind()
{
    if (!m_Bound)
    {
        throw std::runtime_error("Cannot unbind texture while it is not bound!");
    }
    glBindTexture(m_Slot, 0);
    glDeleteTextures(1, &m_ImageId);
    m_Bound = false;
}

void Image::render() const
{

}

} // img end