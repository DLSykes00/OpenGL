#pragma once

#include <string>

class Texture
{
public:
    Texture(const std::string& path);
    ~Texture();

    void bindTexture(unsigned int slot = 0) const;

private:
    uint32_t m_textureBufferID;
};
