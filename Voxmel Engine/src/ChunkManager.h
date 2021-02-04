#ifndef CHUNK_MANAGER_H
#define CHUNK_MANAGER_H

#include "Chunk.h"

#include <vector>

class ChunkManager
{
public:
	ChunkManager();
	~ChunkManager();

	void generateChunkMesh();

private:
	std::vector<Chunk> loadedChunks;
};

#endif // !CHUNK_MANAGER_H

