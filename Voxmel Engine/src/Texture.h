#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>

#include <string>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

class Texture
{
public:
	Texture(const char* textPath, int width, int height, int nrChannels);

private:
	int w, h, nrC;
	unsigned char* data;
};

#endif // !TEXTURE_H

