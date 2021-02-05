#ifndef CHUNK_H
#define CHUNK_H

#include <glad/glad.h>

struct Voxel
{
	float x = 0;
	float y = 0;
	float z = 0;

	bool sides[6] = {false,  // +Z
					 false,  // -Z
					 false,  // +Y
					 false,  // -Y
					 false,  // +X
					 false}; // -X

	int lightLevel = 10;
	int AO = 0;

	unsigned int blockID = 0;
	bool opaque = false;
};

class Chunk
{
public:
	// OpenGL : Buffers
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

