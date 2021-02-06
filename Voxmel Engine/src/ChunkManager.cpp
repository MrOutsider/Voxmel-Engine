#include "ChunkManager.h"

ChunkManager::ChunkManager()
{
}

ChunkManager::~ChunkManager()
{
}

void ChunkManager::init()
{
	generateChunk();
	generateMesh(loadedChunks.back());
}

void ChunkManager::generateChunk()
{
	Chunk* newChunk = new Chunk;
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
				loadedChunks.back()->chunkVoxels[i].blockID = 1;
				loadedChunks.back()->chunkVoxels[i].UVoffset[0] = 19;
				loadedChunks.back()->chunkVoxels[i].UVoffset[1] = 15;
				loadedChunks.back()->chunkVoxels[i].tile = false;
				loadedChunks.back()->chunkVoxels[i].opaque = true;
				i++;
			}
		}
	}

	loadedChunks.back()->chunkVoxels[1130].opaque = false;

	loadedChunks.back()->chunkVoxels[1190].opaque = false;
	loadedChunks.back()->chunkVoxels[1191].opaque = false;
	loadedChunks.back()->chunkVoxels[1190 + 16 * 16].opaque = false;
	loadedChunks.back()->chunkVoxels[1191 + 16 * 16].opaque = false;

	loadedChunks.back()->chunkVoxels[1190 + 16].opaque = false;
	loadedChunks.back()->chunkVoxels[1191 + 16].opaque = false;
	loadedChunks.back()->chunkVoxels[(1190 + 16) + 16 * 16].opaque = false;
	loadedChunks.back()->chunkVoxels[(1191 + 16) + 16 * 16].opaque = false;
}

void ChunkManager::generateMesh(Chunk* chunk)
{
	chunk->verticiesAmount = 0;
	std::vector<float> mesh;

	for (int i = 0; i < chunk->chunkSize * chunk->chunkSize * chunk->chunkSize; i++)
	{
		if (!chunk->chunkVoxels[i].tile && chunk->chunkVoxels[i].opaque)
		{
			// Assign UV Offsets();
			checkNeighbors(chunk, i);

			if (chunk->chunkVoxels[i].sides[0] == false)
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
			if (chunk->chunkVoxels[i].sides[1] == false)
			{
				mesh.push_back(1 * chunk->voxelSize + chunk->chunkVoxels[i].x);
				mesh.push_back(1 * chunk->voxelSize + chunk->chunkVoxels[i].y);
				mesh.push_back(-1 * chunk->voxelSize + chunk->chunkVoxels[i].z);
				mesh.push_back((0 / 32.0f) + ((1.0f / 32.0f) * chunk->chunkVoxels[i].UVoffset[0]));
				mesh.push_back((1 / 16.0f) + ((1.0f / 16.0f) * chunk->chunkVoxels[i].UVoffset[1]));
				mesh.push_back((float)chunk->chunkVoxels[i].neighborLight[1]);

				mesh.push_back(1 * chunk->voxelSize + chunk->chunkVoxels[i].x);
				mesh.push_back(-1 * chunk->voxelSize + chunk->chunkVoxels[i].y);
				mesh.push_back(-1 * chunk->voxelSize + chunk->chunkVoxels[i].z);
				mesh.push_back((0 / 32.0f) + ((1.0f / 32.0f) * chunk->chunkVoxels[i].UVoffset[0]));
				mesh.push_back((0 / 16.0f) + ((1.0f / 16.0f) * chunk->chunkVoxels[i].UVoffset[1]));
				mesh.push_back((float)chunk->chunkVoxels[i].neighborLight[1]);

				mesh.push_back(-1 * chunk->voxelSize + chunk->chunkVoxels[i].x);
				mesh.push_back(-1 * chunk->voxelSize + chunk->chunkVoxels[i].y);
				mesh.push_back(-1 * chunk->voxelSize + chunk->chunkVoxels[i].z);
				mesh.push_back((1 / 32.0f) + ((1.0f / 32.0f) * chunk->chunkVoxels[i].UVoffset[0]));
				mesh.push_back((0 / 16.0f) + ((1.0f / 16.0f) * chunk->chunkVoxels[i].UVoffset[1]));
				mesh.push_back((float)chunk->chunkVoxels[i].neighborLight[1]);

				mesh.push_back(-1 * chunk->voxelSize + chunk->chunkVoxels[i].x);
				mesh.push_back(-1 * chunk->voxelSize + chunk->chunkVoxels[i].y);
				mesh.push_back(-1 * chunk->voxelSize + chunk->chunkVoxels[i].z);
				mesh.push_back((1 / 32.0f) + ((1.0f / 32.0f) * chunk->chunkVoxels[i].UVoffset[0]));
				mesh.push_back((0 / 16.0f) + ((1.0f / 16.0f) * chunk->chunkVoxels[i].UVoffset[1]));
				mesh.push_back((float)chunk->chunkVoxels[i].neighborLight[1]);

				mesh.push_back(-1 * chunk->voxelSize + chunk->chunkVoxels[i].x);
				mesh.push_back(1 * chunk->voxelSize + chunk->chunkVoxels[i].y);
				mesh.push_back(-1 * chunk->voxelSize + chunk->chunkVoxels[i].z);
				mesh.push_back((1 / 32.0f) + ((1.0f / 32.0f) * chunk->chunkVoxels[i].UVoffset[0]));
				mesh.push_back((1 / 16.0f) + ((1.0f / 16.0f) * chunk->chunkVoxels[i].UVoffset[1]));
				mesh.push_back((float)chunk->chunkVoxels[i].neighborLight[1]);

				mesh.push_back(1 * chunk->voxelSize + chunk->chunkVoxels[i].x);
				mesh.push_back(1 * chunk->voxelSize + chunk->chunkVoxels[i].y);
				mesh.push_back(-1 * chunk->voxelSize + chunk->chunkVoxels[i].z);
				mesh.push_back((0 / 32.0f) + ((1.0f / 32.0f) * chunk->chunkVoxels[i].UVoffset[0]));
				mesh.push_back((1 / 16.0f) + ((1.0f / 16.0f) * chunk->chunkVoxels[i].UVoffset[1]));
				mesh.push_back((float)chunk->chunkVoxels[i].neighborLight[1]);

				chunk->verticiesAmount += 6;
			}
			if (chunk->chunkVoxels[i].sides[2] == false)
			{
				mesh.push_back(-1 * chunk->voxelSize + chunk->chunkVoxels[i].x);
				mesh.push_back( 1 * chunk->voxelSize + chunk->chunkVoxels[i].y);
				mesh.push_back(-1 * chunk->voxelSize + chunk->chunkVoxels[i].z);
				mesh.push_back((0 / 32.0f) + ((1.0f / 32.0f) * chunk->chunkVoxels[i].UVoffset[0]));
				mesh.push_back((1 / 16.0f) + ((1.0f / 16.0f) * chunk->chunkVoxels[i].UVoffset[1]));
				mesh.push_back((float)chunk->chunkVoxels[i].neighborLight[2]);

				mesh.push_back(-1 * chunk->voxelSize + chunk->chunkVoxels[i].x);
				mesh.push_back( 1 * chunk->voxelSize + chunk->chunkVoxels[i].y);
				mesh.push_back( 1 * chunk->voxelSize + chunk->chunkVoxels[i].z);
				mesh.push_back((0 / 32.0f) + ((1.0f / 32.0f) * chunk->chunkVoxels[i].UVoffset[0]));
				mesh.push_back((0 / 16.0f) + ((1.0f / 16.0f) * chunk->chunkVoxels[i].UVoffset[1]));
				mesh.push_back((float)chunk->chunkVoxels[i].neighborLight[2]);

				mesh.push_back( 1 * chunk->voxelSize + chunk->chunkVoxels[i].x);
				mesh.push_back( 1 * chunk->voxelSize + chunk->chunkVoxels[i].y);
				mesh.push_back( 1 * chunk->voxelSize + chunk->chunkVoxels[i].z);
				mesh.push_back((1 / 32.0f) + ((1.0f / 32.0f) * chunk->chunkVoxels[i].UVoffset[0]));
				mesh.push_back((0 / 16.0f) + ((1.0f / 16.0f) * chunk->chunkVoxels[i].UVoffset[1]));
				mesh.push_back((float)chunk->chunkVoxels[i].neighborLight[2]);

				mesh.push_back( 1 * chunk->voxelSize + chunk->chunkVoxels[i].x);
				mesh.push_back( 1 * chunk->voxelSize + chunk->chunkVoxels[i].y);
				mesh.push_back( 1 * chunk->voxelSize + chunk->chunkVoxels[i].z);
				mesh.push_back((1 / 32.0f) + ((1.0f / 32.0f) * chunk->chunkVoxels[i].UVoffset[0]));
				mesh.push_back((0 / 16.0f) + ((1.0f / 16.0f) * chunk->chunkVoxels[i].UVoffset[1]));
				mesh.push_back((float)chunk->chunkVoxels[i].neighborLight[2]);

				mesh.push_back( 1 * chunk->voxelSize + chunk->chunkVoxels[i].x);
				mesh.push_back( 1 * chunk->voxelSize + chunk->chunkVoxels[i].y);
				mesh.push_back(-1 * chunk->voxelSize + chunk->chunkVoxels[i].z);
				mesh.push_back((1 / 32.0f) + ((1.0f / 32.0f) * chunk->chunkVoxels[i].UVoffset[0]));
				mesh.push_back((1 / 16.0f) + ((1.0f / 16.0f) * chunk->chunkVoxels[i].UVoffset[1]));
				mesh.push_back((float)chunk->chunkVoxels[i].neighborLight[2]);

				mesh.push_back(-1 * chunk->voxelSize + chunk->chunkVoxels[i].x);
				mesh.push_back( 1 * chunk->voxelSize + chunk->chunkVoxels[i].y);
				mesh.push_back(-1 * chunk->voxelSize + chunk->chunkVoxels[i].z);
				mesh.push_back((0 / 32.0f) + ((1.0f / 32.0f) * chunk->chunkVoxels[i].UVoffset[0]));
				mesh.push_back((1 / 16.0f) + ((1.0f / 16.0f) * chunk->chunkVoxels[i].UVoffset[1]));
				mesh.push_back((float)chunk->chunkVoxels[i].neighborLight[2]);

				chunk->verticiesAmount += 6;
			}
			if (chunk->chunkVoxels[i].sides[3] == false)
			{		
				mesh.push_back( 1 * chunk->voxelSize + chunk->chunkVoxels[i].x);
				mesh.push_back(-1 * chunk->voxelSize + chunk->chunkVoxels[i].y);
				mesh.push_back(-1 * chunk->voxelSize + chunk->chunkVoxels[i].z);
				mesh.push_back((0 / 32.0f) + ((1.0f / 32.0f) * chunk->chunkVoxels[i].UVoffset[0]));
				mesh.push_back((1 / 16.0f) + ((1.0f / 16.0f) * chunk->chunkVoxels[i].UVoffset[1]));
				mesh.push_back((float)chunk->chunkVoxels[i].neighborLight[3]);

				mesh.push_back( 1 * chunk->voxelSize + chunk->chunkVoxels[i].x);
				mesh.push_back(-1 * chunk->voxelSize + chunk->chunkVoxels[i].y);
				mesh.push_back( 1 * chunk->voxelSize + chunk->chunkVoxels[i].z);
				mesh.push_back((0 / 32.0f) + ((1.0f / 32.0f) * chunk->chunkVoxels[i].UVoffset[0]));
				mesh.push_back((0 / 16.0f) + ((1.0f / 16.0f) * chunk->chunkVoxels[i].UVoffset[1]));
				mesh.push_back((float)chunk->chunkVoxels[i].neighborLight[3]);

				mesh.push_back(-1 * chunk->voxelSize + chunk->chunkVoxels[i].x);
				mesh.push_back(-1 * chunk->voxelSize + chunk->chunkVoxels[i].y);
				mesh.push_back( 1 * chunk->voxelSize + chunk->chunkVoxels[i].z);
				mesh.push_back((1 / 32.0f) + ((1.0f / 32.0f) * chunk->chunkVoxels[i].UVoffset[0]));
				mesh.push_back((0 / 16.0f) + ((1.0f / 16.0f) * chunk->chunkVoxels[i].UVoffset[1]));
				mesh.push_back((float)chunk->chunkVoxels[i].neighborLight[3]);

				mesh.push_back(-1 * chunk->voxelSize + chunk->chunkVoxels[i].x);
				mesh.push_back(-1 * chunk->voxelSize + chunk->chunkVoxels[i].y);
				mesh.push_back( 1 * chunk->voxelSize + chunk->chunkVoxels[i].z);
				mesh.push_back((1 / 32.0f) + ((1.0f / 32.0f) * chunk->chunkVoxels[i].UVoffset[0]));
				mesh.push_back((0 / 16.0f) + ((1.0f / 16.0f) * chunk->chunkVoxels[i].UVoffset[1]));
				mesh.push_back((float)chunk->chunkVoxels[i].neighborLight[3]);

				mesh.push_back(-1 * chunk->voxelSize + chunk->chunkVoxels[i].x);
				mesh.push_back(-1 * chunk->voxelSize + chunk->chunkVoxels[i].y);
				mesh.push_back(-1 * chunk->voxelSize + chunk->chunkVoxels[i].z);
				mesh.push_back((1 / 32.0f) + ((1.0f / 32.0f) * chunk->chunkVoxels[i].UVoffset[0]));
				mesh.push_back((1 / 16.0f) + ((1.0f / 16.0f) * chunk->chunkVoxels[i].UVoffset[1]));
				mesh.push_back((float)chunk->chunkVoxels[i].neighborLight[3]);

				mesh.push_back( 1 * chunk->voxelSize + chunk->chunkVoxels[i].x);
				mesh.push_back(-1 * chunk->voxelSize + chunk->chunkVoxels[i].y);
				mesh.push_back(-1 * chunk->voxelSize + chunk->chunkVoxels[i].z);
				mesh.push_back((0 / 32.0f) + ((1.0f / 32.0f) * chunk->chunkVoxels[i].UVoffset[0]));
				mesh.push_back((1 / 16.0f) + ((1.0f / 16.0f) * chunk->chunkVoxels[i].UVoffset[1]));
				mesh.push_back((float)chunk->chunkVoxels[i].neighborLight[3]);

				chunk->verticiesAmount += 6;
			}
			if (chunk->chunkVoxels[i].sides[4] == false)
			{	
				mesh.push_back( 1 * chunk->voxelSize + chunk->chunkVoxels[i].x);
				mesh.push_back( 1 * chunk->voxelSize + chunk->chunkVoxels[i].y);
				mesh.push_back( 1 * chunk->voxelSize + chunk->chunkVoxels[i].z);
				mesh.push_back((0 / 32.0f) + ((1.0f / 32.0f) * chunk->chunkVoxels[i].UVoffset[0]));
				mesh.push_back((1 / 16.0f) + ((1.0f / 16.0f) * chunk->chunkVoxels[i].UVoffset[1]));
				mesh.push_back((float)chunk->chunkVoxels[i].neighborLight[4]);

				mesh.push_back( 1 * chunk->voxelSize + chunk->chunkVoxels[i].x);
				mesh.push_back(-1 * chunk->voxelSize + chunk->chunkVoxels[i].y);
				mesh.push_back( 1 * chunk->voxelSize + chunk->chunkVoxels[i].z);
				mesh.push_back((0 / 32.0f) + ((1.0f / 32.0f) * chunk->chunkVoxels[i].UVoffset[0]));
				mesh.push_back((0 / 16.0f) + ((1.0f / 16.0f) * chunk->chunkVoxels[i].UVoffset[1]));
				mesh.push_back((float)chunk->chunkVoxels[i].neighborLight[4]);

				mesh.push_back( 1 * chunk->voxelSize + chunk->chunkVoxels[i].x);
				mesh.push_back(-1 * chunk->voxelSize + chunk->chunkVoxels[i].y);
				mesh.push_back(-1 * chunk->voxelSize + chunk->chunkVoxels[i].z);
				mesh.push_back((1 / 32.0f) + ((1.0f / 32.0f) * chunk->chunkVoxels[i].UVoffset[0]));
				mesh.push_back((0 / 16.0f) + ((1.0f / 16.0f) * chunk->chunkVoxels[i].UVoffset[1]));
				mesh.push_back((float)chunk->chunkVoxels[i].neighborLight[4]);

				mesh.push_back( 1 * chunk->voxelSize + chunk->chunkVoxels[i].x);
				mesh.push_back(-1 * chunk->voxelSize + chunk->chunkVoxels[i].y);
				mesh.push_back(-1 * chunk->voxelSize + chunk->chunkVoxels[i].z);
				mesh.push_back((1 / 32.0f) + ((1.0f / 32.0f) * chunk->chunkVoxels[i].UVoffset[0]));
				mesh.push_back((0 / 16.0f) + ((1.0f / 16.0f) * chunk->chunkVoxels[i].UVoffset[1]));
				mesh.push_back((float)chunk->chunkVoxels[i].neighborLight[4]);

				mesh.push_back( 1 * chunk->voxelSize + chunk->chunkVoxels[i].x);
				mesh.push_back( 1 * chunk->voxelSize + chunk->chunkVoxels[i].y);
				mesh.push_back(-1 * chunk->voxelSize + chunk->chunkVoxels[i].z);
				mesh.push_back((1 / 32.0f) + ((1.0f / 32.0f) * chunk->chunkVoxels[i].UVoffset[0]));
				mesh.push_back((1 / 16.0f) + ((1.0f / 16.0f) * chunk->chunkVoxels[i].UVoffset[1]));
				mesh.push_back((float)chunk->chunkVoxels[i].neighborLight[4]);

				mesh.push_back( 1 * chunk->voxelSize + chunk->chunkVoxels[i].x);
				mesh.push_back( 1 * chunk->voxelSize + chunk->chunkVoxels[i].y);
				mesh.push_back( 1 * chunk->voxelSize + chunk->chunkVoxels[i].z);
				mesh.push_back((0 / 32.0f) + ((1.0f / 32.0f) * chunk->chunkVoxels[i].UVoffset[0]));
				mesh.push_back((1 / 16.0f) + ((1.0f / 16.0f) * chunk->chunkVoxels[i].UVoffset[1]));
				mesh.push_back((float)chunk->chunkVoxels[i].neighborLight[4]);

				chunk->verticiesAmount += 6;
			}
			if (chunk->chunkVoxels[i].sides[5] == false)
			{
				mesh.push_back(-1 * chunk->voxelSize + chunk->chunkVoxels[i].x);
				mesh.push_back( 1 * chunk->voxelSize + chunk->chunkVoxels[i].y);
				mesh.push_back(-1 * chunk->voxelSize + chunk->chunkVoxels[i].z);
				mesh.push_back((0 / 32.0f) + ((1.0f / 32.0f) * chunk->chunkVoxels[i].UVoffset[0]));
				mesh.push_back((1 / 16.0f) + ((1.0f / 16.0f) * chunk->chunkVoxels[i].UVoffset[1]));
				mesh.push_back((float)chunk->chunkVoxels[i].neighborLight[5]);

				mesh.push_back(-1 * chunk->voxelSize + chunk->chunkVoxels[i].x);
				mesh.push_back(-1 * chunk->voxelSize + chunk->chunkVoxels[i].y);
				mesh.push_back(-1 * chunk->voxelSize + chunk->chunkVoxels[i].z);
				mesh.push_back((0 / 32.0f) + ((1.0f / 32.0f) * chunk->chunkVoxels[i].UVoffset[0]));
				mesh.push_back((0 / 16.0f) + ((1.0f / 16.0f) * chunk->chunkVoxels[i].UVoffset[1]));
				mesh.push_back((float)chunk->chunkVoxels[i].neighborLight[5]);

				mesh.push_back(-1 * chunk->voxelSize + chunk->chunkVoxels[i].x);
				mesh.push_back(-1 * chunk->voxelSize + chunk->chunkVoxels[i].y);
				mesh.push_back( 1 * chunk->voxelSize + chunk->chunkVoxels[i].z);
				mesh.push_back((1 / 32.0f) + ((1.0f / 32.0f) * chunk->chunkVoxels[i].UVoffset[0]));
				mesh.push_back((0 / 16.0f) + ((1.0f / 16.0f) * chunk->chunkVoxels[i].UVoffset[1]));
				mesh.push_back((float)chunk->chunkVoxels[i].neighborLight[5]);

				mesh.push_back(-1 * chunk->voxelSize + chunk->chunkVoxels[i].x);
				mesh.push_back(-1 * chunk->voxelSize + chunk->chunkVoxels[i].y);
				mesh.push_back( 1 * chunk->voxelSize + chunk->chunkVoxels[i].z);
				mesh.push_back((1 / 32.0f) + ((1.0f / 32.0f) * chunk->chunkVoxels[i].UVoffset[0]));
				mesh.push_back((0 / 16.0f) + ((1.0f / 16.0f) * chunk->chunkVoxels[i].UVoffset[1]));
				mesh.push_back((float)chunk->chunkVoxels[i].neighborLight[5]);

				mesh.push_back(-1 * chunk->voxelSize + chunk->chunkVoxels[i].x);
				mesh.push_back( 1 * chunk->voxelSize + chunk->chunkVoxels[i].y);
				mesh.push_back( 1 * chunk->voxelSize + chunk->chunkVoxels[i].z);
				mesh.push_back((1 / 32.0f) + ((1.0f / 32.0f) * chunk->chunkVoxels[i].UVoffset[0]));
				mesh.push_back((1 / 16.0f) + ((1.0f / 16.0f) * chunk->chunkVoxels[i].UVoffset[1]));
				mesh.push_back((float)chunk->chunkVoxels[i].neighborLight[5]);

				mesh.push_back(-1 * chunk->voxelSize + chunk->chunkVoxels[i].x);
				mesh.push_back( 1 * chunk->voxelSize + chunk->chunkVoxels[i].y);
				mesh.push_back(-1 * chunk->voxelSize + chunk->chunkVoxels[i].z);
				mesh.push_back((0 / 32.0f) + ((1.0f / 32.0f) * chunk->chunkVoxels[i].UVoffset[0]));
				mesh.push_back((1 / 16.0f) + ((1.0f / 16.0f) * chunk->chunkVoxels[i].UVoffset[1]));
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
		glBufferData(GL_ARRAY_BUFFER, mesh.size() * sizeof(float), &mesh[0], GL_STATIC_DRAW);

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

void ChunkManager::checkNeighbors(Chunk* chunk, int i)
{
	if (i < chunk->chunkSize * chunk->chunkSize * chunk->chunkSize) // Z
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
	}
}
