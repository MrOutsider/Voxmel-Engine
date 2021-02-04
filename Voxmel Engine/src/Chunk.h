#ifndef CHUNK_H
#define CHUNK_H

#include <glad/glad.h>

struct Voxel
{
	float x;
	float y;
	float z;

	unsigned int blockID;
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

