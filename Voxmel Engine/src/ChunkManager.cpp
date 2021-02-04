#include "ChunkManager.h"

ChunkManager::ChunkManager()
{
	chunkSetterTest();
}

ChunkManager::~ChunkManager()
{
}

void ChunkManager::chunkMesher(GLuint& vertCount, GLuint& VAO , GLuint& VBO)
{
	chunkMesh.clear();
	vertCount = 0;

	for (unsigned int x = 0; x < chunkSize; x++)
	{
		for (unsigned int y = 0; y < chunkSize; y++)
		{
			for (unsigned int z = 0; z < chunkSize; z++)
			{
				switch (chunk[z + y + x])
				{
				default:
					std::cout << "Block Setter Error" << std::endl;
					break;

				case 0:
					break;

				case 1:
					for (unsigned int i = 0; i < 36; i++)
					{
						chunkMesh.push_back(voxel[0 + (i * 5)]);
						chunkMesh.push_back(voxel[1 + ((i * 1) * 5)]);
						chunkMesh.push_back(voxel[2 + ((i * 1) * 5)]);
						vertCount += 3;
						chunkMesh.push_back(voxel[3 + ((i * 1) * 5)]);
						chunkMesh.push_back(voxel[4 + ((i * 1) * 5)]);
					}
					break;
				}
			}
		}
	}

	/*for (unsigned int i = 0; i < 50; i++)
	{
		std::cout << "X : " << chunkMesh[0 + (i * 5)] << std::endl;
		std::cout << "Y : " << chunkMesh[1 + ((i * 1) * 5)] << std::endl;
		std::cout << "Z : " << chunkMesh[2 + ((i * 1) * 5)] << std::endl;
		std::cout << "UV1 : " << chunkMesh[3 + ((i * 1) * 5)] << std::endl;
		std::cout << "UV2 : " << chunkMesh[4 + ((i * 1) * 5)] << std::endl;
	}*/

	/*for (size_t i = 0; i < 30; i++)
	{
		int n = 0;
		std::cout << n + (i * 5) << std::endl;
		n++;
		std::cout << n + ((i * 1) * 5) << std::endl;
		n++;				 
		std::cout << n + ((i * 1) * 5) << std::endl;
		n++;				 
		std::cout << n + ((i * 1) * 5) << std::endl;
		n++;				 
		std::cout << n + ((i * 1) * 5) << std::endl;
		n++;
	}*/

	//--------------------------------------------------------------------------------------------
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

void ChunkManager::chunkSetterTest()
{
	for (unsigned int x = 0; x < chunkSize; x++)
	{
		if (x > ((chunkSize / 2) - 1) || x < ((chunkSize / 2) + 1))
		{
			for (unsigned int y = 0; y < chunkSize; y++)
			{
				if (y > ((chunkSize / 2) - 1) || y < ((chunkSize / 2) + 1))
				{
					for (unsigned int z = 0; z < chunkSize; z++)
					{
						if (z > ((chunkSize / 2) - 1) || z < ((chunkSize / 2) + 1))
						{
							chunk[z + y + x] = 1;
						}
						else
						{
							chunk[z + y + x] = 0;
						}
					}
				}
				else
				{
					for (unsigned int z = 0; z < chunkSize; z++)
					{
						chunk[z + y + x] = 0;
					}
				}
			}
		}
		else
		{
			for (unsigned int y = 0; y < chunkSize; y++)
			{
				for (unsigned int z = 0; z < chunkSize; z++)
				{
					chunk[z + y + x] = 0;
				}
			}
		}
	}

	/*for (unsigned int x = 0; x < chunkSize; x++)
	{
		if (x > ((chunkSize / 2) - 1) || x < ((chunkSize / 2) + 1))
		{
			for (unsigned int y = 0; y < chunkSize; y++)
			{
				if (y > ((chunkSize / 2) - 1) || y < ((chunkSize / 2) + 1))
				{
					for (unsigned int z = 0; z < chunkSize; z++)
					{
						if (z > ((chunkSize / 2) - 1) || z < ((chunkSize / 2) + 1))
						{
							chunk[z + ((y * chunkSize) + (x * chunkSize))] = 1;
						}
						else
						{
							chunk[z + ((y * chunkSize) + (x * chunkSize))] = 0;
						}
					}
				}
				else
				{
					for (unsigned int z = 0; z < chunkSize; z++)
					{
						chunk[z + ((y * chunkSize) + (x * chunkSize))] = 0;
					}
				}
			}
		}
		else
		{
			for (unsigned int y = 0; y < chunkSize; y++)
			{
				for (unsigned int z = 0; z < chunkSize; z++)
				{
					chunk[z + ((y * chunkSize) + (x * chunkSize))] = 0;
				}
			}
		}
	}*/
}
