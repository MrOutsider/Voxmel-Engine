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
	ChunkManager(PhysicsManager& PM, Camera& cam);
	~ChunkManager();

	void init();
	void playerInit(Camera& newPlayer);

	std::vector<Chunk*> loadedChunks;
private:
	PhysicsManager* physicsManager;
	Camera* player;
	bool pInit = false;

	void generateChunk(int newX, int newY, int newZ);

	void generateMesh(Chunk* chunk);

	void setVoxelsByID(Chunk* chunk);
	void setVoxelsNeighbors(Chunk* chunk);
	int getVert(Chunk* chunk, int x, int y, int z);
};

#endif // !CHUNK_MANAGER_H

