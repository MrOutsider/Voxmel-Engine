#include "ChunkManager.h"

ChunkManager::ChunkManager()
{
}

ChunkManager::~ChunkManager()
{
}

void ChunkManager::init()
{
	for (int x = 0; x < 3; x++)
	{
		for (int y = 0; y < 3; y++)
		{
			for (int z = 0; z < 3; z++)
			{
				//generateChunk(x, y, z);
			}
		}
	}

	generateChunk(0, 0, 0);
	generateChunk(0, 0, 1);
	generateChunk(0, 0, 2);

	for (int i = 0; i < loadedChunks.size(); i++)
	{
		generateMesh(loadedChunks[i]);
	}
}

void ChunkManager::playerInit(Camera& newPlayer)
{
	player = &newPlayer;
	pInit = true;
}

void ChunkManager::generateChunk(int newX, int newY, int newZ)
{
	Chunk* newChunk = new Chunk(newX, newY, newZ);
	loadedChunks.push_back(newChunk);

	unsigned int i = 0;

	for (int x = 0; x < loadedChunks.back()->chunkSize; x++)
	{
		for (int y = 0; y < loadedChunks.back()->chunkSize; y++)
		{
			for (int z = 0; z < loadedChunks.back()->chunkSize; z++)
			{
				loadedChunks.back()->chunkVoxels[i].x = x;
				loadedChunks.back()->chunkVoxels[i].y = y;
				loadedChunks.back()->chunkVoxels[i].z = z;
				loadedChunks.back()->chunkVoxels[i].blockID = 2;
				i++;
			}
		}
	}

	loadedChunks.back()->chunkVoxels[getVert(loadedChunks.back(), 5, 8, 7)].blockID = 1;
	loadedChunks.back()->chunkVoxels[getVert(loadedChunks.back(), 6, 8, 7)].blockID = 1;
	loadedChunks.back()->chunkVoxels[getVert(loadedChunks.back(), 7, 8, 7)].blockID = 1;
	loadedChunks.back()->chunkVoxels[getVert(loadedChunks.back(), 8, 8, 7)].blockID = 1;

	loadedChunks.back()->chunkVoxels[getVert(loadedChunks.back(), 5, 7, 7)].blockID = 0;
	loadedChunks.back()->chunkVoxels[getVert(loadedChunks.back(), 6, 7, 7)].blockID = 0;
	loadedChunks.back()->chunkVoxels[getVert(loadedChunks.back(), 7, 7, 7)].blockID = 0;
	loadedChunks.back()->chunkVoxels[getVert(loadedChunks.back(), 8, 7, 7)].blockID = 0;
	loadedChunks.back()->chunkVoxels[getVert(loadedChunks.back(), 5, 6, 7)].blockID = 0;
	loadedChunks.back()->chunkVoxels[getVert(loadedChunks.back(), 6, 6, 7)].blockID = 0;
	loadedChunks.back()->chunkVoxels[getVert(loadedChunks.back(), 7, 6, 7)].blockID = 0;
	loadedChunks.back()->chunkVoxels[getVert(loadedChunks.back(), 8, 6, 7)].blockID = 0;


	loadedChunks.back()->chunkVoxels[getVert(loadedChunks.back(), 0, 7, 7)].blockID = 0;
	loadedChunks.back()->chunkVoxels[getVert(loadedChunks.back(), 1, 7, 7)].blockID = 0;
	loadedChunks.back()->chunkVoxels[getVert(loadedChunks.back(), 2, 7, 7)].blockID = 0;
	loadedChunks.back()->chunkVoxels[getVert(loadedChunks.back(), 3, 7, 7)].blockID = 0;
	loadedChunks.back()->chunkVoxels[getVert(loadedChunks.back(), 4, 7, 7)].blockID = 0;
	loadedChunks.back()->chunkVoxels[getVert(loadedChunks.back(), 5, 7, 7)].blockID = 0;
	loadedChunks.back()->chunkVoxels[getVert(loadedChunks.back(), 6, 7, 7)].blockID = 0;
	loadedChunks.back()->chunkVoxels[getVert(loadedChunks.back(), 7, 7, 7)].blockID = 0;
	loadedChunks.back()->chunkVoxels[getVert(loadedChunks.back(), 8, 7, 7)].blockID = 0;
	loadedChunks.back()->chunkVoxels[getVert(loadedChunks.back(), 9, 7, 7)].blockID = 0;
	loadedChunks.back()->chunkVoxels[getVert(loadedChunks.back(), 10, 7, 7)].blockID = 0;
	loadedChunks.back()->chunkVoxels[getVert(loadedChunks.back(), 11, 7, 7)].blockID = 0;
	loadedChunks.back()->chunkVoxels[getVert(loadedChunks.back(), 12, 7, 7)].blockID = 0;
	loadedChunks.back()->chunkVoxels[getVert(loadedChunks.back(), 13, 7, 7)].blockID = 0;
	loadedChunks.back()->chunkVoxels[getVert(loadedChunks.back(), 14, 7, 7)].blockID = 0;
	loadedChunks.back()->chunkVoxels[getVert(loadedChunks.back(), 15, 7, 7)].blockID = 0;

	loadedChunks.back()->chunkVoxels[getVert(loadedChunks.back(), 7, 7, 0)].blockID = 0;
	loadedChunks.back()->chunkVoxels[getVert(loadedChunks.back(), 7, 7, 1)].blockID = 0;
	loadedChunks.back()->chunkVoxels[getVert(loadedChunks.back(), 7, 7, 2)].blockID = 0;
	loadedChunks.back()->chunkVoxels[getVert(loadedChunks.back(), 7, 7, 3)].blockID = 0;
	loadedChunks.back()->chunkVoxels[getVert(loadedChunks.back(), 7, 7, 4)].blockID = 0;
	loadedChunks.back()->chunkVoxels[getVert(loadedChunks.back(), 7, 7, 5)].blockID = 0;
	loadedChunks.back()->chunkVoxels[getVert(loadedChunks.back(), 7, 7, 6)].blockID = 0;
	loadedChunks.back()->chunkVoxels[getVert(loadedChunks.back(), 7, 7, 7)].blockID = 0;
	loadedChunks.back()->chunkVoxels[getVert(loadedChunks.back(), 7, 7, 8)].blockID = 0;
	loadedChunks.back()->chunkVoxels[getVert(loadedChunks.back(), 7, 7, 9)].blockID = 0;
	loadedChunks.back()->chunkVoxels[getVert(loadedChunks.back(), 7, 7, 10)].blockID = 0;
	loadedChunks.back()->chunkVoxels[getVert(loadedChunks.back(), 7, 7, 11)].blockID = 0;
	loadedChunks.back()->chunkVoxels[getVert(loadedChunks.back(), 7, 7, 12)].blockID = 0;
	loadedChunks.back()->chunkVoxels[getVert(loadedChunks.back(), 7, 7, 13)].blockID = 0;
	loadedChunks.back()->chunkVoxels[getVert(loadedChunks.back(), 7, 7, 14)].blockID = 0;
	loadedChunks.back()->chunkVoxels[getVert(loadedChunks.back(), 7, 7, 15)].blockID = 0;

	loadedChunks.back()->chunkVoxels[getVert(loadedChunks.back(), 7, 0, 7)].blockID = 0;
	loadedChunks.back()->chunkVoxels[getVert(loadedChunks.back(), 7, 1, 7)].blockID = 0;
	loadedChunks.back()->chunkVoxels[getVert(loadedChunks.back(), 7, 2, 7)].blockID = 0;
	loadedChunks.back()->chunkVoxels[getVert(loadedChunks.back(), 7, 3, 7)].blockID = 0;
	loadedChunks.back()->chunkVoxels[getVert(loadedChunks.back(), 7, 4, 7)].blockID = 0;
	loadedChunks.back()->chunkVoxels[getVert(loadedChunks.back(), 7, 5, 7)].blockID = 0;
	loadedChunks.back()->chunkVoxels[getVert(loadedChunks.back(), 7, 6, 7)].blockID = 0;
	loadedChunks.back()->chunkVoxels[getVert(loadedChunks.back(), 7, 7, 7)].blockID = 0;
	loadedChunks.back()->chunkVoxels[getVert(loadedChunks.back(), 7, 8, 7)].blockID = 0;
	loadedChunks.back()->chunkVoxels[getVert(loadedChunks.back(), 7, 9, 7)].blockID = 0;
	loadedChunks.back()->chunkVoxels[getVert(loadedChunks.back(), 7, 10, 7)].blockID = 0;
	loadedChunks.back()->chunkVoxels[getVert(loadedChunks.back(), 7, 11, 7)].blockID = 0;
	loadedChunks.back()->chunkVoxels[getVert(loadedChunks.back(), 7, 12, 7)].blockID = 0;
	loadedChunks.back()->chunkVoxels[getVert(loadedChunks.back(), 7, 13, 7)].blockID = 0;
	loadedChunks.back()->chunkVoxels[getVert(loadedChunks.back(), 7, 14, 7)].blockID = 0;
	loadedChunks.back()->chunkVoxels[getVert(loadedChunks.back(), 7, 15, 7)].blockID = 0;

	setVoxelsByID(loadedChunks.back());
}

void ChunkManager::generateMesh(Chunk* chunk)
{
	chunk->verticiesAmount = 0;
	std::vector<float> mesh;
	setVoxelsNeighbors(chunk);

	for (int i = 0; i < chunk->chunkSize * chunk->chunkSize * chunk->chunkSize; i++)
	{
		if (!chunk->chunkVoxels[i].tile && chunk->chunkVoxels[i].opaque)
		{
			if (chunk->chunkVoxels[i].opaqueNeighbors[0] == false)
			{
				mesh.push_back(-1 * chunk->voxelSize + chunk->chunkVoxels[i].x);
				mesh.push_back(1 * chunk->voxelSize + chunk->chunkVoxels[i].y);
				mesh.push_back(1 * chunk->voxelSize + chunk->chunkVoxels[i].z);
				mesh.push_back((0 / 32.0f) + ((1.0f / 32.0f) * chunk->chunkVoxels[i].UVoffset[0]));
				mesh.push_back((1 / 16.0f) + ((1.0f / 16.0f) * chunk->chunkVoxels[i].UVoffset[1]));
				mesh.push_back((float)chunk->chunkVoxels[i].neighborLight[0]);

				mesh.push_back(-1 * chunk->voxelSize + chunk->chunkVoxels[i].x);
				mesh.push_back(-1 * chunk->voxelSize + chunk->chunkVoxels[i].y);
				mesh.push_back(1 * chunk->voxelSize + chunk->chunkVoxels[i].z);
				mesh.push_back((0 / 32.0f) + ((1.0f / 32.0f) * chunk->chunkVoxels[i].UVoffset[0]));
				mesh.push_back((0 / 16.0f) + ((1.0f / 16.0f) * chunk->chunkVoxels[i].UVoffset[1]));
				mesh.push_back((float)chunk->chunkVoxels[i].neighborLight[0]);

				mesh.push_back(1 * chunk->voxelSize + chunk->chunkVoxels[i].x);
				mesh.push_back(-1 * chunk->voxelSize + chunk->chunkVoxels[i].y);
				mesh.push_back(1 * chunk->voxelSize + chunk->chunkVoxels[i].z);
				mesh.push_back((1 / 32.0f) + ((1.0f / 32.0f) * chunk->chunkVoxels[i].UVoffset[0]));
				mesh.push_back((0 / 16.0f) + ((1.0f / 16.0f) * chunk->chunkVoxels[i].UVoffset[1]));
				mesh.push_back((float)chunk->chunkVoxels[i].neighborLight[0]);

				mesh.push_back(1 * chunk->voxelSize + chunk->chunkVoxels[i].x);
				mesh.push_back(-1 * chunk->voxelSize + chunk->chunkVoxels[i].y);
				mesh.push_back(1 * chunk->voxelSize + chunk->chunkVoxels[i].z);
				mesh.push_back((1 / 32.0f) + ((1.0f / 32.0f) * chunk->chunkVoxels[i].UVoffset[0]));
				mesh.push_back((0 / 16.0f) + ((1.0f / 16.0f) * chunk->chunkVoxels[i].UVoffset[1]));
				mesh.push_back((float)chunk->chunkVoxels[i].neighborLight[0]);

				mesh.push_back(1 * chunk->voxelSize + chunk->chunkVoxels[i].x);
				mesh.push_back(1 * chunk->voxelSize + chunk->chunkVoxels[i].y);
				mesh.push_back(1 * chunk->voxelSize + chunk->chunkVoxels[i].z);
				mesh.push_back((1 / 32.0f) + ((1.0f / 32.0f) * chunk->chunkVoxels[i].UVoffset[0]));
				mesh.push_back((1 / 16.0f) + ((1.0f / 16.0f) * chunk->chunkVoxels[i].UVoffset[1]));
				mesh.push_back((float)chunk->chunkVoxels[i].neighborLight[0]);

				mesh.push_back(-1 * chunk->voxelSize + chunk->chunkVoxels[i].x);
				mesh.push_back(1 * chunk->voxelSize + chunk->chunkVoxels[i].y);
				mesh.push_back(1 * chunk->voxelSize + chunk->chunkVoxels[i].z);
				mesh.push_back((0 / 32.0f) + ((1.0f / 32.0f) * chunk->chunkVoxels[i].UVoffset[0]));
				mesh.push_back((1 / 16.0f) + ((1.0f / 16.0f) * chunk->chunkVoxels[i].UVoffset[1]));
				mesh.push_back((float)chunk->chunkVoxels[i].neighborLight[0]);


				chunk->verticiesAmount += 6;
			}
			if (chunk->chunkVoxels[i].opaqueNeighbors[1] == false)
			{
				mesh.push_back(1 * chunk->voxelSize + chunk->chunkVoxels[i].x);
				mesh.push_back(1 * chunk->voxelSize + chunk->chunkVoxels[i].y);
				mesh.push_back(-1 * chunk->voxelSize + chunk->chunkVoxels[i].z);
				mesh.push_back((0 / 32.0f) + ((1.0f / 32.0f) * chunk->chunkVoxels[i].UVoffset[2]));
				mesh.push_back((1 / 16.0f) + ((1.0f / 16.0f) * chunk->chunkVoxels[i].UVoffset[3]));
				mesh.push_back((float)chunk->chunkVoxels[i].neighborLight[1]);

				mesh.push_back(1 * chunk->voxelSize + chunk->chunkVoxels[i].x);
				mesh.push_back(-1 * chunk->voxelSize + chunk->chunkVoxels[i].y);
				mesh.push_back(-1 * chunk->voxelSize + chunk->chunkVoxels[i].z);
				mesh.push_back((0 / 32.0f) + ((1.0f / 32.0f) * chunk->chunkVoxels[i].UVoffset[2]));
				mesh.push_back((0 / 16.0f) + ((1.0f / 16.0f) * chunk->chunkVoxels[i].UVoffset[3]));
				mesh.push_back((float)chunk->chunkVoxels[i].neighborLight[1]);

				mesh.push_back(-1 * chunk->voxelSize + chunk->chunkVoxels[i].x);
				mesh.push_back(-1 * chunk->voxelSize + chunk->chunkVoxels[i].y);
				mesh.push_back(-1 * chunk->voxelSize + chunk->chunkVoxels[i].z);
				mesh.push_back((1 / 32.0f) + ((1.0f / 32.0f) * chunk->chunkVoxels[i].UVoffset[2]));
				mesh.push_back((0 / 16.0f) + ((1.0f / 16.0f) * chunk->chunkVoxels[i].UVoffset[3]));
				mesh.push_back((float)chunk->chunkVoxels[i].neighborLight[1]);

				mesh.push_back(-1 * chunk->voxelSize + chunk->chunkVoxels[i].x);
				mesh.push_back(-1 * chunk->voxelSize + chunk->chunkVoxels[i].y);
				mesh.push_back(-1 * chunk->voxelSize + chunk->chunkVoxels[i].z);
				mesh.push_back((1 / 32.0f) + ((1.0f / 32.0f) * chunk->chunkVoxels[i].UVoffset[2]));
				mesh.push_back((0 / 16.0f) + ((1.0f / 16.0f) * chunk->chunkVoxels[i].UVoffset[3]));
				mesh.push_back((float)chunk->chunkVoxels[i].neighborLight[1]);

				mesh.push_back(-1 * chunk->voxelSize + chunk->chunkVoxels[i].x);
				mesh.push_back(1 * chunk->voxelSize + chunk->chunkVoxels[i].y);
				mesh.push_back(-1 * chunk->voxelSize + chunk->chunkVoxels[i].z);
				mesh.push_back((1 / 32.0f) + ((1.0f / 32.0f) * chunk->chunkVoxels[i].UVoffset[2]));
				mesh.push_back((1 / 16.0f) + ((1.0f / 16.0f) * chunk->chunkVoxels[i].UVoffset[3]));
				mesh.push_back((float)chunk->chunkVoxels[i].neighborLight[1]);

				mesh.push_back(1 * chunk->voxelSize + chunk->chunkVoxels[i].x);
				mesh.push_back(1 * chunk->voxelSize + chunk->chunkVoxels[i].y);
				mesh.push_back(-1 * chunk->voxelSize + chunk->chunkVoxels[i].z);
				mesh.push_back((0 / 32.0f) + ((1.0f / 32.0f) * chunk->chunkVoxels[i].UVoffset[2]));
				mesh.push_back((1 / 16.0f) + ((1.0f / 16.0f) * chunk->chunkVoxels[i].UVoffset[3]));
				mesh.push_back((float)chunk->chunkVoxels[i].neighborLight[1]);

				chunk->verticiesAmount += 6;
			}
			if (chunk->chunkVoxels[i].opaqueNeighbors[2] == false)
			{
				mesh.push_back(-1 * chunk->voxelSize + chunk->chunkVoxels[i].x);
				mesh.push_back( 1 * chunk->voxelSize + chunk->chunkVoxels[i].y);
				mesh.push_back(-1 * chunk->voxelSize + chunk->chunkVoxels[i].z);
				mesh.push_back((0 / 32.0f) + ((1.0f / 32.0f) * chunk->chunkVoxels[i].UVoffset[4]));
				mesh.push_back((1 / 16.0f) + ((1.0f / 16.0f) * chunk->chunkVoxels[i].UVoffset[5]));
				mesh.push_back((float)chunk->chunkVoxels[i].neighborLight[2]);

				mesh.push_back(-1 * chunk->voxelSize + chunk->chunkVoxels[i].x);
				mesh.push_back( 1 * chunk->voxelSize + chunk->chunkVoxels[i].y);
				mesh.push_back( 1 * chunk->voxelSize + chunk->chunkVoxels[i].z);
				mesh.push_back((0 / 32.0f) + ((1.0f / 32.0f) * chunk->chunkVoxels[i].UVoffset[4]));
				mesh.push_back((0 / 16.0f) + ((1.0f / 16.0f) * chunk->chunkVoxels[i].UVoffset[5]));
				mesh.push_back((float)chunk->chunkVoxels[i].neighborLight[2]);

				mesh.push_back( 1 * chunk->voxelSize + chunk->chunkVoxels[i].x);
				mesh.push_back( 1 * chunk->voxelSize + chunk->chunkVoxels[i].y);
				mesh.push_back( 1 * chunk->voxelSize + chunk->chunkVoxels[i].z);
				mesh.push_back((1 / 32.0f) + ((1.0f / 32.0f) * chunk->chunkVoxels[i].UVoffset[4]));
				mesh.push_back((0 / 16.0f) + ((1.0f / 16.0f) * chunk->chunkVoxels[i].UVoffset[5]));
				mesh.push_back((float)chunk->chunkVoxels[i].neighborLight[2]);

				mesh.push_back( 1 * chunk->voxelSize + chunk->chunkVoxels[i].x);
				mesh.push_back( 1 * chunk->voxelSize + chunk->chunkVoxels[i].y);
				mesh.push_back( 1 * chunk->voxelSize + chunk->chunkVoxels[i].z);
				mesh.push_back((1 / 32.0f) + ((1.0f / 32.0f) * chunk->chunkVoxels[i].UVoffset[4]));
				mesh.push_back((0 / 16.0f) + ((1.0f / 16.0f) * chunk->chunkVoxels[i].UVoffset[5]));
				mesh.push_back((float)chunk->chunkVoxels[i].neighborLight[2]);

				mesh.push_back( 1 * chunk->voxelSize + chunk->chunkVoxels[i].x);
				mesh.push_back( 1 * chunk->voxelSize + chunk->chunkVoxels[i].y);
				mesh.push_back(-1 * chunk->voxelSize + chunk->chunkVoxels[i].z);
				mesh.push_back((1 / 32.0f) + ((1.0f / 32.0f) * chunk->chunkVoxels[i].UVoffset[4]));
				mesh.push_back((1 / 16.0f) + ((1.0f / 16.0f) * chunk->chunkVoxels[i].UVoffset[5]));
				mesh.push_back((float)chunk->chunkVoxels[i].neighborLight[2]);

				mesh.push_back(-1 * chunk->voxelSize + chunk->chunkVoxels[i].x);
				mesh.push_back( 1 * chunk->voxelSize + chunk->chunkVoxels[i].y);
				mesh.push_back(-1 * chunk->voxelSize + chunk->chunkVoxels[i].z);
				mesh.push_back((0 / 32.0f) + ((1.0f / 32.0f) * chunk->chunkVoxels[i].UVoffset[4]));
				mesh.push_back((1 / 16.0f) + ((1.0f / 16.0f) * chunk->chunkVoxels[i].UVoffset[5]));
				mesh.push_back((float)chunk->chunkVoxels[i].neighborLight[2]);

				chunk->verticiesAmount += 6;
			}
			if (chunk->chunkVoxels[i].opaqueNeighbors[3] == false)
			{		
				mesh.push_back( 1 * chunk->voxelSize + chunk->chunkVoxels[i].x);
				mesh.push_back(-1 * chunk->voxelSize + chunk->chunkVoxels[i].y);
				mesh.push_back(-1 * chunk->voxelSize + chunk->chunkVoxels[i].z);
				mesh.push_back((0 / 32.0f) + ((1.0f / 32.0f) * chunk->chunkVoxels[i].UVoffset[6]));
				mesh.push_back((1 / 16.0f) + ((1.0f / 16.0f) * chunk->chunkVoxels[i].UVoffset[7]));
				mesh.push_back((float)chunk->chunkVoxels[i].neighborLight[3]);

				mesh.push_back( 1 * chunk->voxelSize + chunk->chunkVoxels[i].x);
				mesh.push_back(-1 * chunk->voxelSize + chunk->chunkVoxels[i].y);
				mesh.push_back( 1 * chunk->voxelSize + chunk->chunkVoxels[i].z);
				mesh.push_back((0 / 32.0f) + ((1.0f / 32.0f) * chunk->chunkVoxels[i].UVoffset[6]));
				mesh.push_back((0 / 16.0f) + ((1.0f / 16.0f) * chunk->chunkVoxels[i].UVoffset[7]));
				mesh.push_back((float)chunk->chunkVoxels[i].neighborLight[3]);

				mesh.push_back(-1 * chunk->voxelSize + chunk->chunkVoxels[i].x);
				mesh.push_back(-1 * chunk->voxelSize + chunk->chunkVoxels[i].y);
				mesh.push_back( 1 * chunk->voxelSize + chunk->chunkVoxels[i].z);
				mesh.push_back((1 / 32.0f) + ((1.0f / 32.0f) * chunk->chunkVoxels[i].UVoffset[6]));
				mesh.push_back((0 / 16.0f) + ((1.0f / 16.0f) * chunk->chunkVoxels[i].UVoffset[7]));
				mesh.push_back((float)chunk->chunkVoxels[i].neighborLight[3]);

				mesh.push_back(-1 * chunk->voxelSize + chunk->chunkVoxels[i].x);
				mesh.push_back(-1 * chunk->voxelSize + chunk->chunkVoxels[i].y);
				mesh.push_back( 1 * chunk->voxelSize + chunk->chunkVoxels[i].z);
				mesh.push_back((1 / 32.0f) + ((1.0f / 32.0f) * chunk->chunkVoxels[i].UVoffset[6]));
				mesh.push_back((0 / 16.0f) + ((1.0f / 16.0f) * chunk->chunkVoxels[i].UVoffset[7]));
				mesh.push_back((float)chunk->chunkVoxels[i].neighborLight[3]);

				mesh.push_back(-1 * chunk->voxelSize + chunk->chunkVoxels[i].x);
				mesh.push_back(-1 * chunk->voxelSize + chunk->chunkVoxels[i].y);
				mesh.push_back(-1 * chunk->voxelSize + chunk->chunkVoxels[i].z);
				mesh.push_back((1 / 32.0f) + ((1.0f / 32.0f) * chunk->chunkVoxels[i].UVoffset[6]));
				mesh.push_back((1 / 16.0f) + ((1.0f / 16.0f) * chunk->chunkVoxels[i].UVoffset[7]));
				mesh.push_back((float)chunk->chunkVoxels[i].neighborLight[3]);

				mesh.push_back( 1 * chunk->voxelSize + chunk->chunkVoxels[i].x);
				mesh.push_back(-1 * chunk->voxelSize + chunk->chunkVoxels[i].y);
				mesh.push_back(-1 * chunk->voxelSize + chunk->chunkVoxels[i].z);
				mesh.push_back((0 / 32.0f) + ((1.0f / 32.0f) * chunk->chunkVoxels[i].UVoffset[6]));
				mesh.push_back((1 / 16.0f) + ((1.0f / 16.0f) * chunk->chunkVoxels[i].UVoffset[7]));
				mesh.push_back((float)chunk->chunkVoxels[i].neighborLight[3]);

				chunk->verticiesAmount += 6;
			}
			if (chunk->chunkVoxels[i].opaqueNeighbors[4] == false)
			{	
				mesh.push_back( 1 * chunk->voxelSize + chunk->chunkVoxels[i].x);
				mesh.push_back( 1 * chunk->voxelSize + chunk->chunkVoxels[i].y);
				mesh.push_back( 1 * chunk->voxelSize + chunk->chunkVoxels[i].z);
				mesh.push_back((0 / 32.0f) + ((1.0f / 32.0f) * chunk->chunkVoxels[i].UVoffset[8]));
				mesh.push_back((1 / 16.0f) + ((1.0f / 16.0f) * chunk->chunkVoxels[i].UVoffset[9]));
				mesh.push_back((float)chunk->chunkVoxels[i].neighborLight[4]);

				mesh.push_back( 1 * chunk->voxelSize + chunk->chunkVoxels[i].x);
				mesh.push_back(-1 * chunk->voxelSize + chunk->chunkVoxels[i].y);
				mesh.push_back( 1 * chunk->voxelSize + chunk->chunkVoxels[i].z);
				mesh.push_back((0 / 32.0f) + ((1.0f / 32.0f) * chunk->chunkVoxels[i].UVoffset[8]));
				mesh.push_back((0 / 16.0f) + ((1.0f / 16.0f) * chunk->chunkVoxels[i].UVoffset[9]));
				mesh.push_back((float)chunk->chunkVoxels[i].neighborLight[4]);

				mesh.push_back( 1 * chunk->voxelSize + chunk->chunkVoxels[i].x);
				mesh.push_back(-1 * chunk->voxelSize + chunk->chunkVoxels[i].y);
				mesh.push_back(-1 * chunk->voxelSize + chunk->chunkVoxels[i].z);
				mesh.push_back((1 / 32.0f) + ((1.0f / 32.0f) * chunk->chunkVoxels[i].UVoffset[8]));
				mesh.push_back((0 / 16.0f) + ((1.0f / 16.0f) * chunk->chunkVoxels[i].UVoffset[9]));
				mesh.push_back((float)chunk->chunkVoxels[i].neighborLight[4]);

				mesh.push_back( 1 * chunk->voxelSize + chunk->chunkVoxels[i].x);
				mesh.push_back(-1 * chunk->voxelSize + chunk->chunkVoxels[i].y);
				mesh.push_back(-1 * chunk->voxelSize + chunk->chunkVoxels[i].z);
				mesh.push_back((1 / 32.0f) + ((1.0f / 32.0f) * chunk->chunkVoxels[i].UVoffset[8]));
				mesh.push_back((0 / 16.0f) + ((1.0f / 16.0f) * chunk->chunkVoxels[i].UVoffset[9]));
				mesh.push_back((float)chunk->chunkVoxels[i].neighborLight[4]);

				mesh.push_back( 1 * chunk->voxelSize + chunk->chunkVoxels[i].x);
				mesh.push_back( 1 * chunk->voxelSize + chunk->chunkVoxels[i].y);
				mesh.push_back(-1 * chunk->voxelSize + chunk->chunkVoxels[i].z);
				mesh.push_back((1 / 32.0f) + ((1.0f / 32.0f) * chunk->chunkVoxels[i].UVoffset[8]));
				mesh.push_back((1 / 16.0f) + ((1.0f / 16.0f) * chunk->chunkVoxels[i].UVoffset[9]));
				mesh.push_back((float)chunk->chunkVoxels[i].neighborLight[4]);

				mesh.push_back( 1 * chunk->voxelSize + chunk->chunkVoxels[i].x);
				mesh.push_back( 1 * chunk->voxelSize + chunk->chunkVoxels[i].y);
				mesh.push_back( 1 * chunk->voxelSize + chunk->chunkVoxels[i].z);
				mesh.push_back((0 / 32.0f) + ((1.0f / 32.0f) * chunk->chunkVoxels[i].UVoffset[8]));
				mesh.push_back((1 / 16.0f) + ((1.0f / 16.0f) * chunk->chunkVoxels[i].UVoffset[9]));
				mesh.push_back((float)chunk->chunkVoxels[i].neighborLight[4]);

				chunk->verticiesAmount += 6;
			}
			if (chunk->chunkVoxels[i].opaqueNeighbors[5] == false)
			{
				mesh.push_back(-1 * chunk->voxelSize + chunk->chunkVoxels[i].x);
				mesh.push_back( 1 * chunk->voxelSize + chunk->chunkVoxels[i].y);
				mesh.push_back(-1 * chunk->voxelSize + chunk->chunkVoxels[i].z);
				mesh.push_back((0 / 32.0f) + ((1.0f / 32.0f) * chunk->chunkVoxels[i].UVoffset[10]));
				mesh.push_back((1 / 16.0f) + ((1.0f / 16.0f) * chunk->chunkVoxels[i].UVoffset[11]));
				mesh.push_back((float)chunk->chunkVoxels[i].neighborLight[5]);

				mesh.push_back(-1 * chunk->voxelSize + chunk->chunkVoxels[i].x);
				mesh.push_back(-1 * chunk->voxelSize + chunk->chunkVoxels[i].y);
				mesh.push_back(-1 * chunk->voxelSize + chunk->chunkVoxels[i].z);
				mesh.push_back((0 / 32.0f) + ((1.0f / 32.0f) * chunk->chunkVoxels[i].UVoffset[10]));
				mesh.push_back((0 / 16.0f) + ((1.0f / 16.0f) * chunk->chunkVoxels[i].UVoffset[11]));
				mesh.push_back((float)chunk->chunkVoxels[i].neighborLight[5]);

				mesh.push_back(-1 * chunk->voxelSize + chunk->chunkVoxels[i].x);
				mesh.push_back(-1 * chunk->voxelSize + chunk->chunkVoxels[i].y);
				mesh.push_back( 1 * chunk->voxelSize + chunk->chunkVoxels[i].z);
				mesh.push_back((1 / 32.0f) + ((1.0f / 32.0f) * chunk->chunkVoxels[i].UVoffset[10]));
				mesh.push_back((0 / 16.0f) + ((1.0f / 16.0f) * chunk->chunkVoxels[i].UVoffset[11]));
				mesh.push_back((float)chunk->chunkVoxels[i].neighborLight[5]);

				mesh.push_back(-1 * chunk->voxelSize + chunk->chunkVoxels[i].x);
				mesh.push_back(-1 * chunk->voxelSize + chunk->chunkVoxels[i].y);
				mesh.push_back( 1 * chunk->voxelSize + chunk->chunkVoxels[i].z);
				mesh.push_back((1 / 32.0f) + ((1.0f / 32.0f) * chunk->chunkVoxels[i].UVoffset[10]));
				mesh.push_back((0 / 16.0f) + ((1.0f / 16.0f) * chunk->chunkVoxels[i].UVoffset[11]));
				mesh.push_back((float)chunk->chunkVoxels[i].neighborLight[5]);

				mesh.push_back(-1 * chunk->voxelSize + chunk->chunkVoxels[i].x);
				mesh.push_back( 1 * chunk->voxelSize + chunk->chunkVoxels[i].y);
				mesh.push_back( 1 * chunk->voxelSize + chunk->chunkVoxels[i].z);
				mesh.push_back((1 / 32.0f) + ((1.0f / 32.0f) * chunk->chunkVoxels[i].UVoffset[10]));
				mesh.push_back((1 / 16.0f) + ((1.0f / 16.0f) * chunk->chunkVoxels[i].UVoffset[11]));
				mesh.push_back((float)chunk->chunkVoxels[i].neighborLight[5]);

				mesh.push_back(-1 * chunk->voxelSize + chunk->chunkVoxels[i].x);
				mesh.push_back( 1 * chunk->voxelSize + chunk->chunkVoxels[i].y);
				mesh.push_back(-1 * chunk->voxelSize + chunk->chunkVoxels[i].z);
				mesh.push_back((0 / 32.0f) + ((1.0f / 32.0f) * chunk->chunkVoxels[i].UVoffset[10]));
				mesh.push_back((1 / 16.0f) + ((1.0f / 16.0f) * chunk->chunkVoxels[i].UVoffset[11]));
				mesh.push_back((float)chunk->chunkVoxels[i].neighborLight[5]);

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

		glBindBuffer(GL_ARRAY_BUFFER, chunk->VBO);
		glBufferData(GL_ARRAY_BUFFER, mesh.size() * sizeof(float), &mesh[0], GL_DYNAMIC_DRAW);

		glBindVertexArray(chunk->VAO);
		// Vertex Positions
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		// Vertex UVs
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		// Light Levels
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(5 * sizeof(float)));

		glBindVertexArray(0);
	}
}

void ChunkManager::setVoxelsNeighbors(Chunk* chunk)
{
	Chunk* zPos = nullptr;
	Chunk* zNeg = nullptr;
	Chunk* yPos = nullptr;
	Chunk* yNeg = nullptr;
	Chunk* xPos = nullptr;
	Chunk* xNeg = nullptr;

	for (int i = 0; i < loadedChunks.size(); i++)
	{
		if (loadedChunks[i]->x == chunk->x && loadedChunks[i]->y == chunk->y && loadedChunks[i]->z == chunk->z + 1)
		{
			zPos = loadedChunks[i];
		}
		else if (loadedChunks[i]->x == chunk->x && loadedChunks[i]->y == chunk->y && loadedChunks[i]->z == chunk->z - 1)
		{
			zNeg = loadedChunks[i];
		}
		else if (loadedChunks[i]->x == chunk->x && loadedChunks[i]->y == chunk->y + 1 && loadedChunks[i]->z == chunk->z)
		{
			yPos = loadedChunks[i];
		}
		else if (loadedChunks[i]->x == chunk->x && loadedChunks[i]->y == chunk->y - 1 && loadedChunks[i]->z == chunk->z)
		{
			yNeg = loadedChunks[i];
		}
		else if (loadedChunks[i]->x == chunk->x + 1 && loadedChunks[i]->y == chunk->y && loadedChunks[i]->z == chunk->z)
		{
			xPos = loadedChunks[i];
		}
		else if (loadedChunks[i]->x == chunk->x - 1 && loadedChunks[i]->y == chunk->y && loadedChunks[i]->z == chunk->z)
		{
			xNeg = loadedChunks[i];
		}
	}

	for (int x = 0; x < chunk->chunkSize; x++)
	{
		for (int y = 0; y < chunk->chunkSize; y++)
		{
			for (int z = 0; z < chunk->chunkSize; z++)
			{
				int k = getVert(chunk, x, y, z);
				int maxSize = chunk->chunkSize * chunk->chunkSize * chunk->chunkSize;

				chunk->chunkVoxels[k].opaqueNeighbors[0] = true;
				chunk->chunkVoxels[k].opaqueNeighbors[1] = true;
				chunk->chunkVoxels[k].opaqueNeighbors[2] = true;
				chunk->chunkVoxels[k].opaqueNeighbors[3] = true;
				chunk->chunkVoxels[k].opaqueNeighbors[4] = true;
				chunk->chunkVoxels[k].opaqueNeighbors[5] = true;

				// +Z
				if (k + 1 < maxSize)
				{
					if (chunk->chunkVoxels[k + 1].opaque && chunk->chunkVoxels[k + 1].z != 0)
					{
						chunk->chunkVoxels[k].opaqueNeighbors[0] = true;
					}
					else
					{
						chunk->chunkVoxels[k].opaqueNeighbors[0] = false;
					}
				}
				else if (zPos != nullptr)
				{
					chunk->chunkVoxels[k].opaqueNeighbors[0] = false;
				}
				else
				{
					chunk->chunkVoxels[k].opaqueNeighbors[0] = false;
				}


				// -Z
				if (k - 1 > -1)
				{
					if (chunk->chunkVoxels[k - 1].opaque && chunk->chunkVoxels[k - 1].z != chunk->chunkSize - 1)
					{
						chunk->chunkVoxels[k].opaqueNeighbors[1] = true;
					}
					else
					{
						chunk->chunkVoxels[k].opaqueNeighbors[1] = false;
					}
				}
				else if (zNeg != nullptr)
				{
					chunk->chunkVoxels[k].opaqueNeighbors[1] = false;
				}
				else
				{
					chunk->chunkVoxels[k].opaqueNeighbors[1] = false;
				}

				// +Y
				if (k + chunk->chunkSize < maxSize)
				{
					if (chunk->chunkVoxels[k + chunk->chunkSize].opaque && chunk->chunkVoxels[k + chunk->chunkSize].y != 0)
					{
						chunk->chunkVoxels[k].opaqueNeighbors[2] = true;
					}
					else
					{
						chunk->chunkVoxels[k].opaqueNeighbors[2] = false;
					}
				}
				// -Y
				if (k - chunk->chunkSize > -1)
				{
					if (chunk->chunkVoxels[k - chunk->chunkSize].opaque && chunk->chunkVoxels[k - chunk->chunkSize].y != chunk->chunkSize - 1)
					{
						chunk->chunkVoxels[k].opaqueNeighbors[3] = true;
					}
					else
					{
						chunk->chunkVoxels[k].opaqueNeighbors[3] = false;
					}
				}
				// +X
				if (k + chunk->chunkSize * chunk->chunkSize < maxSize)
				{
					if (chunk->chunkVoxels[k + chunk->chunkSize * chunk->chunkSize].opaque && chunk->chunkVoxels[k + chunk->chunkSize * chunk->chunkSize].x != 0)
					{
						chunk->chunkVoxels[k].opaqueNeighbors[4] = true;
					}
					else
					{
						chunk->chunkVoxels[k].opaqueNeighbors[4] = false;
					}
				}
				// -X
				if (k - chunk->chunkSize * chunk->chunkSize > -1)
				{
					if (chunk->chunkVoxels[k - chunk->chunkSize * chunk->chunkSize].opaque && chunk->chunkVoxels[k - chunk->chunkSize * chunk->chunkSize].x != chunk->chunkSize - 1)
					{
						chunk->chunkVoxels[k].opaqueNeighbors[5] = true;
					}
					else
					{
						chunk->chunkVoxels[k].opaqueNeighbors[5] = false;
					}
				}
				//----------------------------------------------------------------------------
			}
		}
	}

	/*if (i < chunk->chunkSize * chunk->chunkSize * chunk->chunkSize) // Z
	{
		if (chunk->chunkVoxels[i + 1].opaque)
		{
			if (chunk->chunkVoxels[i].z == chunk->chunkSize - 1)
			{
				chunk->chunkVoxels[i].sides[0] = false; // Look at nxt chunk
			}
			else
			{
				chunk->chunkVoxels[i].sides[0] = true;
			}
		}
		else
		{
			chunk->chunkVoxels[i].sides[0] = false;
		}
	}
	else if (chunk->chunkVoxels[i].z == chunk->chunkSize - 1)
	{
		chunk->chunkVoxels[i].sides[0] = false; // Look at nxt chunk
	}
	else
	{
		chunk->chunkVoxels[i].sides[0] = true;
	}

	if (i > -1)
	{
		if (chunk->chunkVoxels[i - 1].opaque) // -Z
		{
			if (chunk->chunkVoxels[i].z == 0)
			{
				chunk->chunkVoxels[i].sides[1] = false; // Look at nxt chunk
			}
			else
			{
				chunk->chunkVoxels[i].sides[1] = true;
			}
		}
		else
		{
			chunk->chunkVoxels[i].sides[1] = false;
		}
	}
	else if (chunk->chunkVoxels[i].z == 0)
	{
		chunk->chunkVoxels[i].sides[1] = false; // Look at nxt chunk
	}
	else
	{
		chunk->chunkVoxels[i].sides[1] = true;
	}

	if (i + chunk->chunkSize < chunk->chunkSize * chunk->chunkSize * chunk->chunkSize)
	{
		if (chunk->chunkVoxels[i + chunk->chunkSize].opaque) // +Y
		{
			if (chunk->chunkVoxels[i].y == chunk->chunkSize - 1)
			{
				chunk->chunkVoxels[i].sides[2] = false; // Look at nxt chunk
			}
			else
			{
				chunk->chunkVoxels[i].sides[2] = true;
			}
		}
		else
		{
			chunk->chunkVoxels[i].sides[2] = false;
		}
	}
	else if (chunk->chunkVoxels[i].y == chunk->chunkSize - 1)
	{
		chunk->chunkVoxels[i].sides[2] = false; // Look at nxt chunk
	}
	else
	{
		chunk->chunkVoxels[i].sides[2] = true;
	}

	if (i - 16 > -1)
	{
		if (chunk->chunkVoxels[i - chunk->chunkSize].opaque) // -Y
		{
			if (chunk->chunkVoxels[i].y == 0)
			{
				chunk->chunkVoxels[i].sides[3] = false; // Look at nxt chunk
			}
			else
			{
				chunk->chunkVoxels[i].sides[3] = true;
			}
		}
		else
		{
			chunk->chunkVoxels[i].sides[3] = false;
		}
	}
	else if (chunk->chunkVoxels[i].y == 0)
	{
		chunk->chunkVoxels[i].sides[3] = false; // Look at nxt chunk
	}
	else
	{
		chunk->chunkVoxels[i].sides[3] = true;
	}

	if (i + chunk->chunkSize * chunk->chunkSize < chunk->chunkSize * chunk->chunkSize * chunk->chunkSize)
	{
		if (chunk->chunkVoxels[i + chunk->chunkSize * chunk->chunkSize].opaque) // +X
		{
			if (chunk->chunkVoxels[i].x == chunk->chunkSize - 1)
			{
				chunk->chunkVoxels[i].sides[4] = false; // Look at nxt chunk
			}
			else
			{
				chunk->chunkVoxels[i].sides[4] = true;
			}
		}
		else
		{
			chunk->chunkVoxels[i].sides[4] = false;
		}
	}
	else if (chunk->chunkVoxels[i].x == chunk->chunkSize - 1)
	{
		chunk->chunkVoxels[i].sides[4] = false; // Look at nxt chunk
	}
	else
	{
		chunk->chunkVoxels[i].sides[4] = true;
	}

	if (i - chunk->chunkSize * chunk->chunkSize > -1)
	{
		if (chunk->chunkVoxels[i - chunk->chunkSize * chunk->chunkSize].opaque) // -X
		{
			if (chunk->chunkVoxels[i].x == 0)
			{
				chunk->chunkVoxels[i].sides[5] = false; // Look at nxt chunk
			}
			else
			{
				chunk->chunkVoxels[i].sides[5] = true;
			}
		}
		else
		{
			chunk->chunkVoxels[i].sides[5] = false;
		}
	}
	else if (chunk->chunkVoxels[i].x == 0)
	{
		chunk->chunkVoxels[i].sides[5] = false; // Look at nxt chunk
	}
	else
	{
		chunk->chunkVoxels[i].sides[5] = true;
	}*/
}

int ChunkManager::getVert(Chunk* chunk, int x, int y, int z)
{
	int i = z + y * chunk->chunkSize + x * chunk->chunkSize * chunk->chunkSize;
	return i;
}

void ChunkManager::setVoxelsByID(Chunk* chunk)
{
	for (unsigned int i = 0; i < chunk->chunkSize * chunk->chunkSize * chunk->chunkSize; i++)
	{
		switch (chunk->chunkVoxels[i].blockID)
		{
		default:
			break;

		case 0:
			// AIR
			chunk->chunkVoxels[i].tile = false;
			chunk->chunkVoxels[i].opaque = false;
			break;

		case 1:
			// BEDROCK
			chunk->chunkVoxels[i].tile = false;
			chunk->chunkVoxels[i].opaque = true;
			for (int n = 0; n < 12; n++)
			{
				chunk->chunkVoxels[i].UVoffset[n] = 0;
				chunk->chunkVoxels[i].UVoffset[n + 1] = 14;
				n++;
			}
			break;

		case 2:
			// STONE
			chunk->chunkVoxels[i].tile = false;
			chunk->chunkVoxels[i].opaque = true;
			for (int n = 0; n < 12; n++)
			{
				chunk->chunkVoxels[i].UVoffset[n] = 19;
				chunk->chunkVoxels[i].UVoffset[n + 1] = 15;
				n++;
			}
			break;

		case 3:
			// DIRT
			chunk->chunkVoxels[i].tile = false;
			chunk->chunkVoxels[i].opaque = true;
			for (int n = 0; n < 12; n++)
			{
				chunk->chunkVoxels[i].UVoffset[n] = 18;
				chunk->chunkVoxels[i].UVoffset[n + 1] = 14;
				n++;
			}
			break;
		}
	}
}