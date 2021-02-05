#include "ChunkManager.h"

ChunkManager::ChunkManager()
{
}

ChunkManager::~ChunkManager()
{
}

void ChunkManager::generateChunk()
{
	Chunk* newChunk = new Chunk;
	loadedChunks.push_back(newChunk);

	unsigned int i = 0;

	for (unsigned int x = 0; x < loadedChunks.back()->chunkSize; x++)
	{
		for (unsigned int y = 0; y < loadedChunks.back()->chunkSize; y++)
		{
			for (unsigned int z = 0; z < loadedChunks.back()->chunkSize; z++)
			{
				loadedChunks.back()->chunkVoxels[i].x = x;
				loadedChunks.back()->chunkVoxels[i].y = y;
				loadedChunks.back()->chunkVoxels[i].z = z;
				loadedChunks.back()->chunkVoxels[i].blockID = 1;
				loadedChunks.back()->chunkVoxels[i].opaque = true;
				i++;
			}
		}
	}
}

void ChunkManager::generateMesh(Chunk* chunk)
{
	std::vector<float> mesh;

	for (unsigned int i = 0; i < chunk->chunkSize * chunk->chunkSize * chunk->chunkSize; i++)
	{
		switch (chunk->chunkVoxels[i].blockID)
		{
		default:
			break;

		case 1:
			checkNeighbors(chunk, i);
			// Add Mesh
			break;
		}
	}

	// OpenGL : Buffer Stuff Below
}

void ChunkManager::checkNeighbors(Chunk* chunk, unsigned int i)
{
	if (i + 1 < chunk->chunkSize * chunk->chunkSize * chunk->chunkSize) // +Z
	{
		if (chunk->chunkVoxels[i + 1].opaque == true)
		{
			chunk->chunkVoxels[i].sides[0] = true;
		}
		else
		{
			chunk->chunkVoxels[i].sides[0] = false;
		}
	}

	if (i - 1 > 0)
	{
		if (chunk->chunkVoxels[i - 1].opaque == true) // -Z
		{
			chunk->chunkVoxels[i].sides[1] = true;
		}
		else
		{
			chunk->chunkVoxels[i].sides[1] = false;
		}
	}

	if (i + chunk->chunkSize < chunk->chunkSize * chunk->chunkSize * chunk->chunkSize)
	{
		if (chunk->chunkVoxels[i + chunk->chunkSize].opaque == true) // +Y
		{
			chunk->chunkVoxels[i].sides[2] = true;
		}
		else
		{
			chunk->chunkVoxels[i].sides[2] = false;
		}
	}

	if (i - chunk->chunkSize > 0)
	{
		if (chunk->chunkVoxels[i - chunk->chunkSize].opaque == true) // -Y
		{
			chunk->chunkVoxels[i].sides[3] = true;
		}
		else
		{
			chunk->chunkVoxels[i].sides[3] = false;
		}
	}

	if (i + chunk->chunkSize * chunk->chunkSize < chunk->chunkSize * chunk->chunkSize * chunk->chunkSize)
	{
		if (chunk->chunkVoxels[i + chunk->chunkSize * chunk->chunkSize].opaque == true) // +X
		{
			chunk->chunkVoxels[i].sides[4] = true;
		}
		else
		{
			chunk->chunkVoxels[i].sides[4] = false;
		}
	}

	if (i - chunk->chunkSize * chunk->chunkSize > 0)
	{
		if (chunk->chunkVoxels[i - chunk->chunkSize * chunk->chunkSize].opaque == true) // -X
		{
			chunk->chunkVoxels[i].sides[5] = true;
		}
		else
		{
			chunk->chunkVoxels[i].sides[5] = false;
		}
	}
}
