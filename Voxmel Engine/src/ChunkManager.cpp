#include "ChunkManager.h"

ChunkManager::ChunkManager()
{
	chunkSetterTest();
}

ChunkManager::~ChunkManager()
{
}

void ChunkManager::chunkMesher(GLuint& vertCount, GLuint& VAO, GLuint& VBO)
{
	vertCount = 0;

	for (unsigned int x = 0; x < 2; x++)
	{
		for (unsigned int y = 0; y < 2; y++)
		{
			for (unsigned int z = 0; z < 2; z++)
			{
				for (unsigned int i = 0; i < 36; i++)
				{
					chunkMesh.push_back(voxel[0 + (i * 5)] + (x * voxelSize * 2));
					chunkMesh.push_back(voxel[1 + ((i * 1) * 5)] + (y * voxelSize * 2));
					chunkMesh.push_back(voxel[2 + ((i * 1) * 5)] + (z * voxelSize * 2));
					vertCount += 3;
					chunkMesh.push_back(voxel[3 + ((i * 1) * 5)]);
					chunkMesh.push_back(voxel[4 + ((i * 1) * 5)]);
				}
			}
		}
	}

	//--------------------------------------------------------------------------------------------
	if (!chunkMesh.empty())
	{
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, chunkMesh.size() * sizeof(float), &chunkMesh[0], GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(0 * sizeof(float)));
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		glBindVertexArray(0);
	}
}

void ChunkManager::chunkSetterTest()
{
}
