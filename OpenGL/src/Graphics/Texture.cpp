#include "Texture.h"
#include <GL/glew.h>
#include <stb/stb_image.h>

Texture::Texture(const std::string& path)
{
    stbi_set_flip_vertically_on_load(true);

    int width, height, bitsPerPixel;
    unsigned char* localBuffer = stbi_load(path.c_str(), &width, &height, &bitsPerPixel, 4);

    glGenTextures(1, &m_textureBufferID);
    glBindTexture(GL_TEXTURE_2D, m_textureBufferID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    GLfloat maxAF;
    glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &maxAF);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, maxAF);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, localBuffer);

    glGenerateMipmap(GL_TEXTURE_2D);

    if (localBuffer)
        stbi_image_free(localBuffer);
}

Texture::~Texture()
{
    glDeleteTextures(1, &m_textureBufferID);
}

void Texture::bindTexture(unsigned int slot) const
{
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, m_textureBufferID);
}
