#pragma once

#include <string>

class Texture
{
public:
    Texture(const std::string& path);
    ~Texture();

    void bindTexture(unsigned int slot = 0) const;

private:
    unsigned int m_textureBufferID;
};
