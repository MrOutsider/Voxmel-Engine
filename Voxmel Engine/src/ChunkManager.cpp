#include "ChunkManager.h"

ChunkManager::ChunkManager()
{
}

ChunkManager::~ChunkManager()
{
}

void ChunkManager::chunkSetterTest()
{
	for (unsigned int x = 0; x < chunkSize; x++)
	{
		if (x > ((chunkSize / 2) - 2) || x < ((chunkSize / 2) + 2))
		{
			for (unsigned int y = 0; y < chunkSize; y++)
			{
				if (y > ((chunkSize / 2) - 2) || y < ((chunkSize / 2) + 2))
				{
					for (unsigned int z = 0; z < chunkSize; z++)
					{
						if (z > ((chunkSize / 2) - 2) || z < ((chunkSize / 2) + 2))
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
	}
}

void ChunkManager::chunkMesher()
{

}
