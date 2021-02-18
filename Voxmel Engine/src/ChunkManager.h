#ifndef CHUNK_MANAGER_H
#define CHUNK_MANAGER_H

#include <glad/glad.h>

#include "Chunk.h"
#include "PhysicsManager.h"
#include "Camera.h"

#include <vector>

class ChunkManager
{
public:
	ChunkManager(PhysicsManager& physicsM, std::vector<Chunk*>& loadedChunksList);
	~ChunkManager();

	void init();
	int getVoxelLoc(Chunk* chunk, int x, int y, int z);

	void addBlock(CHUNK_AABB* chunkAABB, unsigned int blockID);
	void removeBlock(AABB* voxelAABB);
private:
	PhysicsManager* physicsManager;

	std::vector<Chunk*>* loadedChunks;

	bool pInit = false;

	void generateChunk(int newX, int newY, int newZ);

	void generateMesh(Chunk* chunk);

	void setVoxelsByID(Chunk* chunk);
	void setVoxelsNeighbors(Chunk* chunk);

	Chunk* findVoxelsChunk(AABB* voxel);
};

#endif // !CHUNK_MANAGER_H

