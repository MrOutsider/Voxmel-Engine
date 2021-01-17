#include "Texture.h"

Texture::Texture(const char* textPath, int width, int height, int nrChannels)
{
	w = width;
	h = height;
	nrC = nrChannels;
	data = stbi_load("container.jpg", &w, &h, &nrC, 0);
}
