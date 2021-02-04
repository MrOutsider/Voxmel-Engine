#ifndef CHUNK_MANAGER_H
#define CHUNK_MANAGER_H

#include <glad/glad.h>

#include <iostream>
#include <vector>

class ChunkManager
{
public:
	ChunkManager();
	~ChunkManager();

	void chunkMesher(GLuint& vertCount, GLuint& VAO, GLuint& VBO);

private:
	unsigned int chunkSize = 4;
	unsigned int chunk[64];	// chunkSize^3

	unsigned int blockX = 18;
	unsigned int blockY = 1;

	float voxelSize = 0.5f;
	float voxel[180] =
	{	// Verts												UVs
		// Back
		 (1 * voxelSize),  (1 * voxelSize), (-1 * voxelSize),	(0.0f), (1.0f),
		 (1 * voxelSize), (-1 * voxelSize), (-1 * voxelSize),	(0.0f), (0.0f),
		(-1 * voxelSize), (-1 * voxelSize), (-1 * voxelSize),	(1.0f), (0.0f),
		(-1 * voxelSize), (-1 * voxelSize), (-1 * voxelSize),	(1.0f), (0.0f),
		(-1 * voxelSize),  (1 * voxelSize), (-1 * voxelSize),	(1.0f), (1.0f),
		 (1 * voxelSize),  (1 * voxelSize), (-1 * voxelSize),	(0.0f), (1.0f),
		// Front													
		(-1 * voxelSize),  (1 * voxelSize),  (1 * voxelSize),	(0.0f), (1.0f),
		(-1 * voxelSize), (-1 * voxelSize),  (1 * voxelSize),	(0.0f), (0.0f),
		 (1 * voxelSize), (-1 * voxelSize),  (1 * voxelSize),	(1.0f), (0.0f),
		 (1 * voxelSize), (-1 * voxelSize),  (1 * voxelSize),	(1.0f), (0.0f),
		 (1 * voxelSize),  (1 * voxelSize),  (1 * voxelSize),	(1.0f), (1.0f),
		(-1 * voxelSize),  (1 * voxelSize),  (1 * voxelSize),	(0.0f), (1.0f),
		// Top														
		(-1 * voxelSize),  (1 * voxelSize), (-1 * voxelSize),	(0.0f), (1.0f),
		(-1 * voxelSize),  (1 * voxelSize),  (1 * voxelSize),	(0.0f), (0.0f),
		 (1 * voxelSize),  (1 * voxelSize),  (1 * voxelSize),	(1.0f), (0.0f),
		 (1 * voxelSize),  (1 * voxelSize),  (1 * voxelSize),	(1.0f), (0.0f),
		 (1 * voxelSize),  (1 * voxelSize), (-1 * voxelSize),	(1.0f), (1.0f),
		(-1 * voxelSize),  (1 * voxelSize), (-1 * voxelSize),	(0.0f), (1.0f),
		// Bottom													 
		 (1 * voxelSize), (-1 * voxelSize), (-1 * voxelSize),	(0.0f), (1.0f),
		 (1 * voxelSize), (-1 * voxelSize),  (1 * voxelSize),	(0.0f), (0.0f),
		(-1 * voxelSize), (-1 * voxelSize),  (1 * voxelSize),	(1.0f), (0.0f),
		(-1 * voxelSize), (-1 * voxelSize),  (1 * voxelSize),	(1.0f), (0.0f),
		(-1 * voxelSize), (-1 * voxelSize), (-1 * voxelSize),	(1.0f), (1.0f),
		(1 * voxelSize),  (-1 * voxelSize), (-1 * voxelSize),	(0.0f), (1.0f),
		// Left														 
		(-1 * voxelSize),  (1 * voxelSize), (-1 * voxelSize),	(0.0f), (1.0f),
		(-1 * voxelSize), (-1 * voxelSize), (-1 * voxelSize),	(0.0f), (0.0f),
		(-1 * voxelSize), (-1 * voxelSize),  (1 * voxelSize),	(1.0f), (0.0f),
		(-1 * voxelSize), (-1 * voxelSize),  (1 * voxelSize),	(1.0f), (0.0f),
		(-1 * voxelSize),  (1 * voxelSize),  (1 * voxelSize),	(1.0f), (1.0f),
		(-1 * voxelSize),  (1 * voxelSize), (-1 * voxelSize),	(0.0f), (1.0f),
		// Right													 
		 (1 * voxelSize),  (1 * voxelSize),  (1 * voxelSize),	(0.0f), (1.0f),
		 (1 * voxelSize), (-1 * voxelSize),  (1 * voxelSize),	(0.0f), (0.0f),
		 (1 * voxelSize), (-1 * voxelSize), (-1 * voxelSize),	(1.0f), (0.0f),
		 (1 * voxelSize), (-1 * voxelSize), (-1 * voxelSize),	(1.0f), (0.0f),
		 (1 * voxelSize),  (1 * voxelSize), (-1 * voxelSize),	(1.0f), (1.0f),
		 (1 * voxelSize),  (1 * voxelSize),  (1 * voxelSize),	(0.0f), (1.0f),
	};

	std::vector<float> chunkMesh;

	void chunkSetterTest();
};

#endif // !CHUNK_MANAGER_H
