#ifndef CHUNK_MANAGER_H
#define CHUNK_MANAGER_H

#include <glad/glad.h>

#include "Chunk.h"
#include "PhysicsManager.h"
#include "Camera.h"

#include <vector>

#include <iostream>

class ChunkManager
{
public:
	ChunkManager(PhysicsManager& PM);
	~ChunkManager();

	void init();
	int getVoxelLoc(Chunk* chunk, int x, int y, int z);

	void addBlock(CHUNK_AABB& chunkAABB, unsigned int blockID);
	void removeBlock(CHUNK_AABB& chunkAABB, AABB& voxelAABB);

	std::vector<Chunk*> loadedChunks;
private:
	PhysicsManager* physicsManager;
	bool pInit = false;

	void generateChunk(int newX, int newY, int newZ);

	void generateMesh(Chunk* chunk);

	void setVoxelsByID(Chunk* chunk);
	void setVoxelsNeighbors(Chunk* chunk);
};

#endif // !CHUNK_MANAGER_H

