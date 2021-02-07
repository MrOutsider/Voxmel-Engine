#ifndef CHUNK_H
#define CHUNK_H

#include <glad/glad.h>

struct Voxel
{
	unsigned int blockID = 0;
	bool tile = false;
	bool opaque = false;

	int x = 0;
	int y = 0;
	int z = 0;

	int UVoffset[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

	bool opaqueNeighbors[6] = { false,  // -Z
					 false,  // +Z
					 false,  // +Y
					 false,  // -Y
					 false,  // +X
					 false }; // -X

	int lightLevel = 0;
	// TODO : Lighting done with 24 arr[3] so per vertex into the neighboring light level makes a gradient.
	int neighborLight[6] = {  7,  // -Z
							 10,  // +Z
							 10,  // +Y
							  7,  // -Y
							 10,  // +X
							  7}; // -X
};

class Chunk
{
public:
	int x = 0;
	int y = 0;
	int z = 0;

	// OpenGL : Buffers
	bool buffersInit = false;
	GLuint VAO;
	GLuint VBO;
	unsigned int verticiesAmount;

	float voxelSize = 0.5f;

	int chunkSize = 16; // Size of strip
	Voxel chunkVoxels[4096]; // chunkSize^3

	Chunk(int newX, int newY, int newZ);
	~Chunk();

private:

};

#endif // !CHUNK_H

