#ifndef CHUNK_H
#define CHUNK_H

#include <glad/glad.h>

struct Voxel
{
	unsigned int x = 0;
	unsigned int y = 0;
	unsigned int z = 0;

	float UVoffset[2] = {0.0f, 0.0f};

	bool sides[6] = {false,  // +Z
					 false,  // -Z
					 false,  // +Y
					 false,  // -Y
					 false,  // +X
					 false}; // -X

	int lightLevel = 10;
	int AO = 0;

	unsigned int blockID = 0;
	bool tile = false;
	bool opaque = false;
};

class Chunk
{
public:
	// OpenGL : Buffers
	bool buffersInit = false;
	GLuint VAO;
	GLuint VBO;
	unsigned int verticiesAmount;

	unsigned int chunkSize = 16;

	Voxel chunkVoxels[4096]; // 16^3

	Chunk();
	~Chunk();

private:

};

#endif // !CHUNK_H

