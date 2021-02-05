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
		if (!chunk->chunkVoxels[i].tile)
		{
			checkNeighbors(chunk, i);
			// Add Mesh
			if (!chunk->chunkVoxels[i].sides[0])
			{
				mesh.push_back(0.0f);
				mesh.push_back(0.0f);
				mesh.push_back(0.0f);
				mesh.push_back(0.0f);
				mesh.push_back(0.0f);

				mesh.push_back(0.0f);
				mesh.push_back(0.0f);
				mesh.push_back(0.0f);
				mesh.push_back(0.0f);
				mesh.push_back(0.0f);

				mesh.push_back(0.0f);
				mesh.push_back(0.0f);
				mesh.push_back(0.0f);
				mesh.push_back(0.0f);
				mesh.push_back(0.0f);

				mesh.push_back(0.0f);
				mesh.push_back(0.0f);
				mesh.push_back(0.0f);
				mesh.push_back(0.0f);
				mesh.push_back(0.0f);

				mesh.push_back(0.0f);
				mesh.push_back(0.0f);
				mesh.push_back(0.0f);
				mesh.push_back(0.0f);
				mesh.push_back(0.0f);

				mesh.push_back(0.0f);
				mesh.push_back(0.0f);
				mesh.push_back(0.0f);
				mesh.push_back(0.0f);
				mesh.push_back(0.0f);

				chunk->verticiesAmount += 6;
			}
			if (!chunk->chunkVoxels[i].sides[1])
			{
				mesh.push_back(0.0f);
				mesh.push_back(0.0f);
				mesh.push_back(0.0f);
				mesh.push_back(0.0f);
				mesh.push_back(0.0f);

				mesh.push_back(0.0f);
				mesh.push_back(0.0f);
				mesh.push_back(0.0f);
				mesh.push_back(0.0f);
				mesh.push_back(0.0f);

				mesh.push_back(0.0f);
				mesh.push_back(0.0f);
				mesh.push_back(0.0f);
				mesh.push_back(0.0f);
				mesh.push_back(0.0f);

				mesh.push_back(0.0f);
				mesh.push_back(0.0f);
				mesh.push_back(0.0f);
				mesh.push_back(0.0f);
				mesh.push_back(0.0f);

				mesh.push_back(0.0f);
				mesh.push_back(0.0f);
				mesh.push_back(0.0f);
				mesh.push_back(0.0f);
				mesh.push_back(0.0f);

				mesh.push_back(0.0f);
				mesh.push_back(0.0f);
				mesh.push_back(0.0f);
				mesh.push_back(0.0f);
				mesh.push_back(0.0f);

				chunk->verticiesAmount += 6;
			}
			if (!chunk->chunkVoxels[i].sides[2])
			{
				mesh.push_back(0.0f);
				mesh.push_back(0.0f);
				mesh.push_back(0.0f);
				mesh.push_back(0.0f);
				mesh.push_back(0.0f);

				mesh.push_back(0.0f);
				mesh.push_back(0.0f);
				mesh.push_back(0.0f);
				mesh.push_back(0.0f);
				mesh.push_back(0.0f);

				mesh.push_back(0.0f);
				mesh.push_back(0.0f);
				mesh.push_back(0.0f);
				mesh.push_back(0.0f);
				mesh.push_back(0.0f);

				mesh.push_back(0.0f);
				mesh.push_back(0.0f);
				mesh.push_back(0.0f);
				mesh.push_back(0.0f);
				mesh.push_back(0.0f);

				mesh.push_back(0.0f);
				mesh.push_back(0.0f);
				mesh.push_back(0.0f);
				mesh.push_back(0.0f);
				mesh.push_back(0.0f);

				mesh.push_back(0.0f);
				mesh.push_back(0.0f);
				mesh.push_back(0.0f);
				mesh.push_back(0.0f);
				mesh.push_back(0.0f);

				chunk->verticiesAmount += 6;
			}
			if (!chunk->chunkVoxels[i].sides[3])
			{
				mesh.push_back(0.0f);
				mesh.push_back(0.0f);
				mesh.push_back(0.0f);
				mesh.push_back(0.0f);
				mesh.push_back(0.0f);

				mesh.push_back(0.0f);
				mesh.push_back(0.0f);
				mesh.push_back(0.0f);
				mesh.push_back(0.0f);
				mesh.push_back(0.0f);

				mesh.push_back(0.0f);
				mesh.push_back(0.0f);
				mesh.push_back(0.0f);
				mesh.push_back(0.0f);
				mesh.push_back(0.0f);

				mesh.push_back(0.0f);
				mesh.push_back(0.0f);
				mesh.push_back(0.0f);
				mesh.push_back(0.0f);
				mesh.push_back(0.0f);

				mesh.push_back(0.0f);
				mesh.push_back(0.0f);
				mesh.push_back(0.0f);
				mesh.push_back(0.0f);
				mesh.push_back(0.0f);

				mesh.push_back(0.0f);
				mesh.push_back(0.0f);
				mesh.push_back(0.0f);
				mesh.push_back(0.0f);
				mesh.push_back(0.0f);

				chunk->verticiesAmount += 6;
			}
			if (!chunk->chunkVoxels[i].sides[4])
			{
				mesh.push_back(0.0f);
				mesh.push_back(0.0f);
				mesh.push_back(0.0f);
				mesh.push_back(0.0f);
				mesh.push_back(0.0f);

				mesh.push_back(0.0f);
				mesh.push_back(0.0f);
				mesh.push_back(0.0f);
				mesh.push_back(0.0f);
				mesh.push_back(0.0f);

				mesh.push_back(0.0f);
				mesh.push_back(0.0f);
				mesh.push_back(0.0f);
				mesh.push_back(0.0f);
				mesh.push_back(0.0f);

				mesh.push_back(0.0f);
				mesh.push_back(0.0f);
				mesh.push_back(0.0f);
				mesh.push_back(0.0f);
				mesh.push_back(0.0f);

				mesh.push_back(0.0f);
				mesh.push_back(0.0f);
				mesh.push_back(0.0f);
				mesh.push_back(0.0f);
				mesh.push_back(0.0f);

				mesh.push_back(0.0f);
				mesh.push_back(0.0f);
				mesh.push_back(0.0f);
				mesh.push_back(0.0f);
				mesh.push_back(0.0f);

				chunk->verticiesAmount += 6;
			}
			if (!chunk->chunkVoxels[i].sides[5])
			{
				mesh.push_back(0.0f);
				mesh.push_back(0.0f);
				mesh.push_back(0.0f);
				mesh.push_back(0.0f);
				mesh.push_back(0.0f);

				mesh.push_back(0.0f);
				mesh.push_back(0.0f);
				mesh.push_back(0.0f);
				mesh.push_back(0.0f);
				mesh.push_back(0.0f);

				mesh.push_back(0.0f);
				mesh.push_back(0.0f);
				mesh.push_back(0.0f);
				mesh.push_back(0.0f);
				mesh.push_back(0.0f);

				mesh.push_back(0.0f);
				mesh.push_back(0.0f);
				mesh.push_back(0.0f);
				mesh.push_back(0.0f);
				mesh.push_back(0.0f);

				mesh.push_back(0.0f);
				mesh.push_back(0.0f);
				mesh.push_back(0.0f);
				mesh.push_back(0.0f);
				mesh.push_back(0.0f);

				mesh.push_back(0.0f);
				mesh.push_back(0.0f);
				mesh.push_back(0.0f);
				mesh.push_back(0.0f);
				mesh.push_back(0.0f);

				chunk->verticiesAmount += 6;
			}
		}
	}

	if (!mesh.empty())
	{
		// OpenGL : Buffer Stuff Below
		if (!chunk->buffersInit)
		{
			glGenVertexArrays(1, &chunk->VAO);
			glGenBuffers(1, &chunk->VBO);
			chunk->buffersInit = true;
		}

		glBindVertexArray(chunk->VAO);
		glBindBuffer(GL_ARRAY_BUFFER, chunk->VBO);

		glBufferData(GL_ARRAY_BUFFER, mesh.size() * sizeof(float), &mesh[0], GL_DYNAMIC_DRAW);

		// Vertex Positions
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float), (void*)0);
		// Vertex UVs
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float), (void*)(3 * sizeof(float)));

		glBindVertexArray(0);
	}
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
