#include "Texture.h"
#include "../Dependencies/stb_image/stb_image.h"

#include <GL/glew.h>
#include <iostream>

Texture::Texture(const std::string& path)
	: filePath(path), localBuffer(nullptr), width(0), height(0), bitsPerPixel(0)
{
	stbi_set_flip_vertically_on_load(1);
	
	localBuffer = stbi_load(path.c_str(), &width, &height, &bitsPerPixel, 4);

	glGenTextures(1, &textureBufferID);
	glBindTexture(GL_TEXTURE_2D, textureBufferID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	std::cout << "Width: " << width << "\nHeight: " << height << "\nBPP: " << bitsPerPixel << std::endl;

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, localBuffer);
	
	glBindTexture(GL_TEXTURE_2D, 0);

	if (localBuffer)
		stbi_image_free(localBuffer);
}

Texture::~Texture()
{
	glDeleteTextures(1, &textureBufferID);
}

void Texture::bindTexture(unsigned int slot) const
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, textureBufferID);
}

void Texture::unbindTexture()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
