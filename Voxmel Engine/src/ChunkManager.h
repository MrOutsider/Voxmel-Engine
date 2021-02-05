#ifndef CHUNK_MANAGER_H
#define CHUNK_MANAGER_H

#include <glad/glad.h>

#include "Chunk.h"

#include <vector>

class ChunkManager
{
public:
	ChunkManager();
	~ChunkManager();

private:
	std::vector<Chunk*> loadedChunks;

	void generateChunk();
	void generateMesh(Chunk* chunk);
	void checkNeighbors(Chunk* chunk, unsigned int i);
};

#endif // !CHUNK_MANAGER_H

