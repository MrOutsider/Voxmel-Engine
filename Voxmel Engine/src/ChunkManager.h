#ifndef CHUNK_MANAGER_H
#define CHUNK_MANAGER_H

#include <glad/glad.h>

#include "Chunk.h"

#include <vector>

#include <iostream>

class ChunkManager
{
public:
	ChunkManager();
	~ChunkManager();

	void init();

	std::vector<Chunk*> loadedChunks;
private:
	//std::vector<Chunk*> loadedChunks;

	void generateChunk(); // All ID = 1
	void generateMesh(Chunk* chunk);
	void checkNeighbors(Chunk* chunk, int i);
};

#endif // !CHUNK_MANAGER_H

