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
	chunkMesh.clear();
	vertCount = 0;

	for (unsigned int x = 0; x < chunkSize; x++)
	{
		for (unsigned int y = 0; y < chunkSize; y++)
		{
			for (unsigned int z = 0; z < chunkSize; z++)
			{
				switch (chunk[x * chunkSize * chunkSize + y * chunkSize + z])
				{
				default:
					std::cout << "Block Setter Error" << std::endl;
					break;

				case 0: // AIR
					break;

				case 1: // STONE
					for (unsigned int i = 0; i < 36; i++)
					{
						chunkMesh.push_back(voxel[0 + (i * 5)]		 + (float)x);
						chunkMesh.push_back(voxel[1 + ((i * 1) * 5)] + (float)y);
						chunkMesh.push_back(voxel[2 + ((i * 1) * 5)] + (float)z);
						vertCount += 3;
						chunkMesh.push_back(voxel[3 + ((i * 1) * 5)]);
						chunkMesh.push_back(voxel[4 + ((i * 1) * 5)]);
					}
					break;
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
		glBufferData(GL_ARRAY_BUFFER, chunkMesh.size(), &chunkMesh[0], GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(0 * sizeof(float)));
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		glBindVertexArray(0);
	}
}

void ChunkManager::chunkSetterTest()
{
	for (unsigned int x = 0; x < chunkSize; x++)
	{
		for (unsigned int y = 0; y < chunkSize; y++)
		{
			for (unsigned int z = 0; z < chunkSize; z++)
			{
				switch (x * chunkSize * chunkSize + y * chunkSize + z)
				{
				default:
					chunk[x * chunkSize * chunkSize + y * chunkSize + z] = 0;
					break;

				case 0:
					chunk[x * chunkSize * chunkSize + y * chunkSize + z] = 1;
					break;

				case 1:
					chunk[x * chunkSize * chunkSize + y * chunkSize + z] = 1;
					break;
				}
			}
		}
	}
}
