#pragma once

#include <string>

class Texture
{
private:
	std::string filePath;
	unsigned int textureBufferID;
	unsigned char* localBuffer;
	int width, height, bitsPerPixel;

public:
	Texture(const std::string& path);
	~Texture();

	void bindTexture(unsigned int slot = 0) const;
	void unbindTexture();
};