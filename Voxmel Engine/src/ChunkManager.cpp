#include "ChunkManager.h"

ChunkManager::ChunkManager(PhysicsManager& PM)
{
	physicsManager = &PM;
}

ChunkManager::~ChunkManager()
{
}

void ChunkManager::init()
{

	for (int x = 0; x < 3; x++)
	{
		for (int y = 0; y < 2; y++)
		{
			for (int z = 0; z < 3; z++)
			{
				generateChunk(x, y, z);
			}
		}
	}

	for (int i = 0; i < loadedChunks.size(); i++)
	{
		generateMesh(loadedChunks[i]);
	}

	for (unsigned int i = 0; i < loadedChunks.size(); i++)
	{
		for (unsigned int n = 0; n < loadedChunks[i]->chunkSize * loadedChunks[i]->chunkSize * loadedChunks[i]->chunkSize; n++)
		{
			loadedChunks[i]->chunkAABB.voxelBoxList.push_back(&loadedChunks[i]->chunkVoxels[n].aabb);
		}

		loadedChunks[i]->chunkAABB.ID = physicsManager->assignID();
		physicsManager->chunkBoxList.push_back(&loadedChunks[i]->chunkAABB);
	}
}

void ChunkManager::generateChunk(int newX, int newY, int newZ)
{
	Chunk* newChunk = new Chunk(newX, newY, newZ);
	loadedChunks.push_back(newChunk);

	loadedChunks.back()->chunkAABB.typeOfContainer = loadedChunks.back()->chunkAABB.CHUNK;

	loadedChunks.back()->chunkAABB.chunkX = newX;
	loadedChunks.back()->chunkAABB.chunkY = newY;
	loadedChunks.back()->chunkAABB.chunkZ = newZ;

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
				loadedChunks.back()->chunkVoxels[i].blockID = 0;
				loadedChunks.back()->chunkVoxels[i].aabb.voxelID = i;
				loadedChunks.back()->chunkVoxels[i].aabb.typeOfContainer = loadedChunks.back()->chunkVoxels[i].aabb.VOXEL;
				i++;
			}
		}
	}

	for (int x = 0; x < 3; x++)
	{
		for (int y = 0; y < 3; y++)
		{
			for (int z = 0; z < 3; z++)
			{
				loadedChunks.back()->chunkVoxels[getVoxelLoc(loadedChunks.back(), x + loadedChunks.back()->chunkSize * 0.5f, y + loadedChunks.back()->chunkSize * 0.5f, z + loadedChunks.back()->chunkSize * 0.5f)].blockID = 1;
			}
		}
	}

	loadedChunks.back()->chunkVoxels[getVoxelLoc(loadedChunks.back(), 9, 8, 9)].blockID = 0;
	loadedChunks.back()->chunkVoxels[getVoxelLoc(loadedChunks.back(), 9, 9, 9)].blockID = 0;
	loadedChunks.back()->chunkVoxels[getVoxelLoc(loadedChunks.back(), 9, 10, 9)].blockID = 0;
	loadedChunks.back()->chunkVoxels[getVoxelLoc(loadedChunks.back(), 8, 9, 9)].blockID = 0;
	loadedChunks.back()->chunkVoxels[getVoxelLoc(loadedChunks.back(), 10, 9, 9)].blockID = 0;
	loadedChunks.back()->chunkVoxels[getVoxelLoc(loadedChunks.back(), 9, 9, 8)].blockID = 0;
	loadedChunks.back()->chunkVoxels[getVoxelLoc(loadedChunks.back(), 9, 9, 10)].blockID = 0;

	loadedChunks.back()->chunkVoxels[getVoxelLoc(loadedChunks.back(), 0, 9, 9)].blockID = 2;

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
				mesh.push_back(-1 * chunk->voxelSizeHalf + chunk->chunkVoxels[i].x * chunk->voxelSizeHalf * 2);
				mesh.push_back( 1 * chunk->voxelSizeHalf + chunk->chunkVoxels[i].y * chunk->voxelSizeHalf * 2);
				mesh.push_back( 1 * chunk->voxelSizeHalf + chunk->chunkVoxels[i].z * chunk->voxelSizeHalf * 2);
				mesh.push_back((0 / 32.0f) + ((1.0f / 32.0f) * chunk->chunkVoxels[i].UVoffset[0]));
				mesh.push_back((1 / 16.0f) + ((1.0f / 16.0f) * chunk->chunkVoxels[i].UVoffset[1]));
				mesh.push_back((float)chunk->chunkVoxels[i].neighborLight[0]);

				mesh.push_back(-1 * chunk->voxelSizeHalf + chunk->chunkVoxels[i].x * chunk->voxelSizeHalf * 2);
				mesh.push_back(-1 * chunk->voxelSizeHalf + chunk->chunkVoxels[i].y * chunk->voxelSizeHalf * 2);
				mesh.push_back( 1 * chunk->voxelSizeHalf + chunk->chunkVoxels[i].z * chunk->voxelSizeHalf * 2);
				mesh.push_back((0 / 32.0f) + ((1.0f / 32.0f) * chunk->chunkVoxels[i].UVoffset[0]));
				mesh.push_back((0 / 16.0f) + ((1.0f / 16.0f) * chunk->chunkVoxels[i].UVoffset[1]));
				mesh.push_back((float)chunk->chunkVoxels[i].neighborLight[0]);

				mesh.push_back( 1 * chunk->voxelSizeHalf + chunk->chunkVoxels[i].x * chunk->voxelSizeHalf * 2);
				mesh.push_back(-1 * chunk->voxelSizeHalf + chunk->chunkVoxels[i].y * chunk->voxelSizeHalf * 2);
				mesh.push_back( 1 * chunk->voxelSizeHalf + chunk->chunkVoxels[i].z * chunk->voxelSizeHalf * 2);
				mesh.push_back((1 / 32.0f) + ((1.0f / 32.0f) * chunk->chunkVoxels[i].UVoffset[0]));
				mesh.push_back((0 / 16.0f) + ((1.0f / 16.0f) * chunk->chunkVoxels[i].UVoffset[1]));
				mesh.push_back((float)chunk->chunkVoxels[i].neighborLight[0]);

				mesh.push_back( 1 * chunk->voxelSizeHalf + chunk->chunkVoxels[i].x * chunk->voxelSizeHalf * 2);
				mesh.push_back(-1 * chunk->voxelSizeHalf + chunk->chunkVoxels[i].y * chunk->voxelSizeHalf * 2);
				mesh.push_back( 1 * chunk->voxelSizeHalf + chunk->chunkVoxels[i].z * chunk->voxelSizeHalf * 2);
				mesh.push_back((1 / 32.0f) + ((1.0f / 32.0f) * chunk->chunkVoxels[i].UVoffset[0]));
				mesh.push_back((0 / 16.0f) + ((1.0f / 16.0f) * chunk->chunkVoxels[i].UVoffset[1]));
				mesh.push_back((float)chunk->chunkVoxels[i].neighborLight[0]);

				mesh.push_back( 1 * chunk->voxelSizeHalf + chunk->chunkVoxels[i].x * chunk->voxelSizeHalf * 2);
				mesh.push_back( 1 * chunk->voxelSizeHalf + chunk->chunkVoxels[i].y * chunk->voxelSizeHalf * 2);
				mesh.push_back( 1 * chunk->voxelSizeHalf + chunk->chunkVoxels[i].z * chunk->voxelSizeHalf * 2);
				mesh.push_back((1 / 32.0f) + ((1.0f / 32.0f) * chunk->chunkVoxels[i].UVoffset[0]));
				mesh.push_back((1 / 16.0f) + ((1.0f / 16.0f) * chunk->chunkVoxels[i].UVoffset[1]));
				mesh.push_back((float)chunk->chunkVoxels[i].neighborLight[0]);

				mesh.push_back(-1 * chunk->voxelSizeHalf + chunk->chunkVoxels[i].x * chunk->voxelSizeHalf * 2);
				mesh.push_back( 1 * chunk->voxelSizeHalf + chunk->chunkVoxels[i].y * chunk->voxelSizeHalf * 2);
				mesh.push_back( 1 * chunk->voxelSizeHalf + chunk->chunkVoxels[i].z * chunk->voxelSizeHalf * 2);
				mesh.push_back((0 / 32.0f) + ((1.0f / 32.0f) * chunk->chunkVoxels[i].UVoffset[0]));
				mesh.push_back((1 / 16.0f) + ((1.0f / 16.0f) * chunk->chunkVoxels[i].UVoffset[1]));
				mesh.push_back((float)chunk->chunkVoxels[i].neighborLight[0]);


				chunk->verticiesAmount += 6;
			}
			if (chunk->chunkVoxels[i].opaqueNeighbors[1] == false)
			{
				mesh.push_back( 1 * chunk->voxelSizeHalf + chunk->chunkVoxels[i].x * chunk->voxelSizeHalf * 2);
				mesh.push_back( 1 * chunk->voxelSizeHalf + chunk->chunkVoxels[i].y * chunk->voxelSizeHalf * 2);
				mesh.push_back(-1 * chunk->voxelSizeHalf + chunk->chunkVoxels[i].z * chunk->voxelSizeHalf * 2);
				mesh.push_back((0 / 32.0f) + ((1.0f / 32.0f) * chunk->chunkVoxels[i].UVoffset[2]));
				mesh.push_back((1 / 16.0f) + ((1.0f / 16.0f) * chunk->chunkVoxels[i].UVoffset[3]));
				mesh.push_back((float)chunk->chunkVoxels[i].neighborLight[1]);

				mesh.push_back( 1 * chunk->voxelSizeHalf + chunk->chunkVoxels[i].x * chunk->voxelSizeHalf * 2);
				mesh.push_back(-1 * chunk->voxelSizeHalf + chunk->chunkVoxels[i].y * chunk->voxelSizeHalf * 2);
				mesh.push_back(-1 * chunk->voxelSizeHalf + chunk->chunkVoxels[i].z * chunk->voxelSizeHalf * 2);
				mesh.push_back((0 / 32.0f) + ((1.0f / 32.0f) * chunk->chunkVoxels[i].UVoffset[2]));
				mesh.push_back((0 / 16.0f) + ((1.0f / 16.0f) * chunk->chunkVoxels[i].UVoffset[3]));
				mesh.push_back((float)chunk->chunkVoxels[i].neighborLight[1]);

				mesh.push_back(-1 * chunk->voxelSizeHalf + chunk->chunkVoxels[i].x * chunk->voxelSizeHalf * 2);
				mesh.push_back(-1 * chunk->voxelSizeHalf + chunk->chunkVoxels[i].y * chunk->voxelSizeHalf * 2);
				mesh.push_back(-1 * chunk->voxelSizeHalf + chunk->chunkVoxels[i].z * chunk->voxelSizeHalf * 2);
				mesh.push_back((1 / 32.0f) + ((1.0f / 32.0f) * chunk->chunkVoxels[i].UVoffset[2]));
				mesh.push_back((0 / 16.0f) + ((1.0f / 16.0f) * chunk->chunkVoxels[i].UVoffset[3]));
				mesh.push_back((float)chunk->chunkVoxels[i].neighborLight[1]);

				mesh.push_back(-1 * chunk->voxelSizeHalf + chunk->chunkVoxels[i].x * chunk->voxelSizeHalf * 2);
				mesh.push_back(-1 * chunk->voxelSizeHalf + chunk->chunkVoxels[i].y * chunk->voxelSizeHalf * 2);
				mesh.push_back(-1 * chunk->voxelSizeHalf + chunk->chunkVoxels[i].z * chunk->voxelSizeHalf * 2);
				mesh.push_back((1 / 32.0f) + ((1.0f / 32.0f) * chunk->chunkVoxels[i].UVoffset[2]));
				mesh.push_back((0 / 16.0f) + ((1.0f / 16.0f) * chunk->chunkVoxels[i].UVoffset[3]));
				mesh.push_back((float)chunk->chunkVoxels[i].neighborLight[1]);

				mesh.push_back(-1 * chunk->voxelSizeHalf + chunk->chunkVoxels[i].x * chunk->voxelSizeHalf * 2);
				mesh.push_back( 1 * chunk->voxelSizeHalf + chunk->chunkVoxels[i].y * chunk->voxelSizeHalf * 2);
				mesh.push_back(-1 * chunk->voxelSizeHalf + chunk->chunkVoxels[i].z * chunk->voxelSizeHalf * 2);
				mesh.push_back((1 / 32.0f) + ((1.0f / 32.0f) * chunk->chunkVoxels[i].UVoffset[2]));
				mesh.push_back((1 / 16.0f) + ((1.0f / 16.0f) * chunk->chunkVoxels[i].UVoffset[3]));
				mesh.push_back((float)chunk->chunkVoxels[i].neighborLight[1]);

				mesh.push_back( 1 * chunk->voxelSizeHalf + chunk->chunkVoxels[i].x * chunk->voxelSizeHalf * 2);
				mesh.push_back( 1 * chunk->voxelSizeHalf + chunk->chunkVoxels[i].y * chunk->voxelSizeHalf * 2);
				mesh.push_back(-1 * chunk->voxelSizeHalf + chunk->chunkVoxels[i].z * chunk->voxelSizeHalf * 2);
				mesh.push_back((0 / 32.0f) + ((1.0f / 32.0f) * chunk->chunkVoxels[i].UVoffset[2]));
				mesh.push_back((1 / 16.0f) + ((1.0f / 16.0f) * chunk->chunkVoxels[i].UVoffset[3]));
				mesh.push_back((float)chunk->chunkVoxels[i].neighborLight[1]);

				chunk->verticiesAmount += 6;
			}
			if (chunk->chunkVoxels[i].opaqueNeighbors[2] == false)
			{
				mesh.push_back(-1 * chunk->voxelSizeHalf + chunk->chunkVoxels[i].x * chunk->voxelSizeHalf * 2);
				mesh.push_back( 1 * chunk->voxelSizeHalf + chunk->chunkVoxels[i].y * chunk->voxelSizeHalf * 2);
				mesh.push_back(-1 * chunk->voxelSizeHalf + chunk->chunkVoxels[i].z * chunk->voxelSizeHalf * 2);
				mesh.push_back((0 / 32.0f) + ((1.0f / 32.0f) * chunk->chunkVoxels[i].UVoffset[4]));
				mesh.push_back((1 / 16.0f) + ((1.0f / 16.0f) * chunk->chunkVoxels[i].UVoffset[5]));
				mesh.push_back((float)chunk->chunkVoxels[i].neighborLight[2]);

				mesh.push_back(-1 * chunk->voxelSizeHalf + chunk->chunkVoxels[i].x * chunk->voxelSizeHalf * 2);
				mesh.push_back( 1 * chunk->voxelSizeHalf + chunk->chunkVoxels[i].y * chunk->voxelSizeHalf * 2);
				mesh.push_back( 1 * chunk->voxelSizeHalf + chunk->chunkVoxels[i].z * chunk->voxelSizeHalf * 2);
				mesh.push_back((0 / 32.0f) + ((1.0f / 32.0f) * chunk->chunkVoxels[i].UVoffset[4]));
				mesh.push_back((0 / 16.0f) + ((1.0f / 16.0f) * chunk->chunkVoxels[i].UVoffset[5]));
				mesh.push_back((float)chunk->chunkVoxels[i].neighborLight[2]);

				mesh.push_back( 1 * chunk->voxelSizeHalf + chunk->chunkVoxels[i].x * chunk->voxelSizeHalf * 2);
				mesh.push_back( 1 * chunk->voxelSizeHalf + chunk->chunkVoxels[i].y * chunk->voxelSizeHalf * 2);
				mesh.push_back( 1 * chunk->voxelSizeHalf + chunk->chunkVoxels[i].z * chunk->voxelSizeHalf * 2);
				mesh.push_back((1 / 32.0f) + ((1.0f / 32.0f) * chunk->chunkVoxels[i].UVoffset[4]));
				mesh.push_back((0 / 16.0f) + ((1.0f / 16.0f) * chunk->chunkVoxels[i].UVoffset[5]));
				mesh.push_back((float)chunk->chunkVoxels[i].neighborLight[2]);

				mesh.push_back( 1 * chunk->voxelSizeHalf + chunk->chunkVoxels[i].x * chunk->voxelSizeHalf * 2);
				mesh.push_back( 1 * chunk->voxelSizeHalf + chunk->chunkVoxels[i].y * chunk->voxelSizeHalf * 2);
				mesh.push_back( 1 * chunk->voxelSizeHalf + chunk->chunkVoxels[i].z * chunk->voxelSizeHalf * 2);
				mesh.push_back((1 / 32.0f) + ((1.0f / 32.0f) * chunk->chunkVoxels[i].UVoffset[4]));
				mesh.push_back((0 / 16.0f) + ((1.0f / 16.0f) * chunk->chunkVoxels[i].UVoffset[5]));
				mesh.push_back((float)chunk->chunkVoxels[i].neighborLight[2]);

				mesh.push_back( 1 * chunk->voxelSizeHalf + chunk->chunkVoxels[i].x * chunk->voxelSizeHalf * 2);
				mesh.push_back( 1 * chunk->voxelSizeHalf + chunk->chunkVoxels[i].y * chunk->voxelSizeHalf * 2);
				mesh.push_back(-1 * chunk->voxelSizeHalf + chunk->chunkVoxels[i].z * chunk->voxelSizeHalf * 2);
				mesh.push_back((1 / 32.0f) + ((1.0f / 32.0f) * chunk->chunkVoxels[i].UVoffset[4]));
				mesh.push_back((1 / 16.0f) + ((1.0f / 16.0f) * chunk->chunkVoxels[i].UVoffset[5]));
				mesh.push_back((float)chunk->chunkVoxels[i].neighborLight[2]);

				mesh.push_back(-1 * chunk->voxelSizeHalf + chunk->chunkVoxels[i].x * chunk->voxelSizeHalf * 2);
				mesh.push_back( 1 * chunk->voxelSizeHalf + chunk->chunkVoxels[i].y * chunk->voxelSizeHalf * 2);
				mesh.push_back(-1 * chunk->voxelSizeHalf + chunk->chunkVoxels[i].z * chunk->voxelSizeHalf * 2);
				mesh.push_back((0 / 32.0f) + ((1.0f / 32.0f) * chunk->chunkVoxels[i].UVoffset[4]));
				mesh.push_back((1 / 16.0f) + ((1.0f / 16.0f) * chunk->chunkVoxels[i].UVoffset[5]));
				mesh.push_back((float)chunk->chunkVoxels[i].neighborLight[2]);

				chunk->verticiesAmount += 6;
			}
			if (chunk->chunkVoxels[i].opaqueNeighbors[3] == false)
			{		
				mesh.push_back( 1 * chunk->voxelSizeHalf + chunk->chunkVoxels[i].x * chunk->voxelSizeHalf * 2);
				mesh.push_back(-1 * chunk->voxelSizeHalf + chunk->chunkVoxels[i].y * chunk->voxelSizeHalf * 2);
				mesh.push_back(-1 * chunk->voxelSizeHalf + chunk->chunkVoxels[i].z * chunk->voxelSizeHalf * 2);
				mesh.push_back((0 / 32.0f) + ((1.0f / 32.0f) * chunk->chunkVoxels[i].UVoffset[6]));
				mesh.push_back((1 / 16.0f) + ((1.0f / 16.0f) * chunk->chunkVoxels[i].UVoffset[7]));
				mesh.push_back((float)chunk->chunkVoxels[i].neighborLight[3]);

				mesh.push_back( 1 * chunk->voxelSizeHalf + chunk->chunkVoxels[i].x * chunk->voxelSizeHalf * 2);
				mesh.push_back(-1 * chunk->voxelSizeHalf + chunk->chunkVoxels[i].y * chunk->voxelSizeHalf * 2);
				mesh.push_back( 1 * chunk->voxelSizeHalf + chunk->chunkVoxels[i].z * chunk->voxelSizeHalf * 2);
				mesh.push_back((0 / 32.0f) + ((1.0f / 32.0f) * chunk->chunkVoxels[i].UVoffset[6]));
				mesh.push_back((0 / 16.0f) + ((1.0f / 16.0f) * chunk->chunkVoxels[i].UVoffset[7]));
				mesh.push_back((float)chunk->chunkVoxels[i].neighborLight[3]);

				mesh.push_back(-1 * chunk->voxelSizeHalf + chunk->chunkVoxels[i].x * chunk->voxelSizeHalf * 2);
				mesh.push_back(-1 * chunk->voxelSizeHalf + chunk->chunkVoxels[i].y * chunk->voxelSizeHalf * 2);
				mesh.push_back( 1 * chunk->voxelSizeHalf + chunk->chunkVoxels[i].z * chunk->voxelSizeHalf * 2);
				mesh.push_back((1 / 32.0f) + ((1.0f / 32.0f) * chunk->chunkVoxels[i].UVoffset[6]));
				mesh.push_back((0 / 16.0f) + ((1.0f / 16.0f) * chunk->chunkVoxels[i].UVoffset[7]));
				mesh.push_back((float)chunk->chunkVoxels[i].neighborLight[3]);

				mesh.push_back(-1 * chunk->voxelSizeHalf + chunk->chunkVoxels[i].x * chunk->voxelSizeHalf * 2);
				mesh.push_back(-1 * chunk->voxelSizeHalf + chunk->chunkVoxels[i].y * chunk->voxelSizeHalf * 2);
				mesh.push_back( 1 * chunk->voxelSizeHalf + chunk->chunkVoxels[i].z * chunk->voxelSizeHalf * 2);
				mesh.push_back((1 / 32.0f) + ((1.0f / 32.0f) * chunk->chunkVoxels[i].UVoffset[6]));
				mesh.push_back((0 / 16.0f) + ((1.0f / 16.0f) * chunk->chunkVoxels[i].UVoffset[7]));
				mesh.push_back((float)chunk->chunkVoxels[i].neighborLight[3]);

				mesh.push_back(-1 * chunk->voxelSizeHalf + chunk->chunkVoxels[i].x * chunk->voxelSizeHalf * 2);
				mesh.push_back(-1 * chunk->voxelSizeHalf + chunk->chunkVoxels[i].y * chunk->voxelSizeHalf * 2);
				mesh.push_back(-1 * chunk->voxelSizeHalf + chunk->chunkVoxels[i].z * chunk->voxelSizeHalf * 2);
				mesh.push_back((1 / 32.0f) + ((1.0f / 32.0f) * chunk->chunkVoxels[i].UVoffset[6]));
				mesh.push_back((1 / 16.0f) + ((1.0f / 16.0f) * chunk->chunkVoxels[i].UVoffset[7]));
				mesh.push_back((float)chunk->chunkVoxels[i].neighborLight[3]);

				mesh.push_back( 1 * chunk->voxelSizeHalf + chunk->chunkVoxels[i].x * chunk->voxelSizeHalf * 2);
				mesh.push_back(-1 * chunk->voxelSizeHalf + chunk->chunkVoxels[i].y * chunk->voxelSizeHalf * 2);
				mesh.push_back(-1 * chunk->voxelSizeHalf + chunk->chunkVoxels[i].z * chunk->voxelSizeHalf * 2);
				mesh.push_back((0 / 32.0f) + ((1.0f / 32.0f) * chunk->chunkVoxels[i].UVoffset[6]));
				mesh.push_back((1 / 16.0f) + ((1.0f / 16.0f) * chunk->chunkVoxels[i].UVoffset[7]));
				mesh.push_back((float)chunk->chunkVoxels[i].neighborLight[3]);

				chunk->verticiesAmount += 6;
			}
			if (chunk->chunkVoxels[i].opaqueNeighbors[4] == false)
			{	
				mesh.push_back( 1 * chunk->voxelSizeHalf + chunk->chunkVoxels[i].x * chunk->voxelSizeHalf * 2);
				mesh.push_back( 1 * chunk->voxelSizeHalf + chunk->chunkVoxels[i].y * chunk->voxelSizeHalf * 2);
				mesh.push_back( 1 * chunk->voxelSizeHalf + chunk->chunkVoxels[i].z * chunk->voxelSizeHalf * 2);
				mesh.push_back((0 / 32.0f) + ((1.0f / 32.0f) * chunk->chunkVoxels[i].UVoffset[8]));
				mesh.push_back((1 / 16.0f) + ((1.0f / 16.0f) * chunk->chunkVoxels[i].UVoffset[9]));
				mesh.push_back((float)chunk->chunkVoxels[i].neighborLight[4]);

				mesh.push_back( 1 * chunk->voxelSizeHalf + chunk->chunkVoxels[i].x * chunk->voxelSizeHalf * 2);
				mesh.push_back(-1 * chunk->voxelSizeHalf + chunk->chunkVoxels[i].y * chunk->voxelSizeHalf * 2);
				mesh.push_back( 1 * chunk->voxelSizeHalf + chunk->chunkVoxels[i].z * chunk->voxelSizeHalf * 2);
				mesh.push_back((0 / 32.0f) + ((1.0f / 32.0f) * chunk->chunkVoxels[i].UVoffset[8]));
				mesh.push_back((0 / 16.0f) + ((1.0f / 16.0f) * chunk->chunkVoxels[i].UVoffset[9]));
				mesh.push_back((float)chunk->chunkVoxels[i].neighborLight[4]);

				mesh.push_back( 1 * chunk->voxelSizeHalf + chunk->chunkVoxels[i].x * chunk->voxelSizeHalf * 2);
				mesh.push_back(-1 * chunk->voxelSizeHalf + chunk->chunkVoxels[i].y * chunk->voxelSizeHalf * 2);
				mesh.push_back(-1 * chunk->voxelSizeHalf + chunk->chunkVoxels[i].z * chunk->voxelSizeHalf * 2);
				mesh.push_back((1 / 32.0f) + ((1.0f / 32.0f) * chunk->chunkVoxels[i].UVoffset[8]));
				mesh.push_back((0 / 16.0f) + ((1.0f / 16.0f) * chunk->chunkVoxels[i].UVoffset[9]));
				mesh.push_back((float)chunk->chunkVoxels[i].neighborLight[4]);

				mesh.push_back( 1 * chunk->voxelSizeHalf + chunk->chunkVoxels[i].x * chunk->voxelSizeHalf * 2);
				mesh.push_back(-1 * chunk->voxelSizeHalf + chunk->chunkVoxels[i].y * chunk->voxelSizeHalf * 2);
				mesh.push_back(-1 * chunk->voxelSizeHalf + chunk->chunkVoxels[i].z * chunk->voxelSizeHalf * 2);
				mesh.push_back((1 / 32.0f) + ((1.0f / 32.0f) * chunk->chunkVoxels[i].UVoffset[8]));
				mesh.push_back((0 / 16.0f) + ((1.0f / 16.0f) * chunk->chunkVoxels[i].UVoffset[9]));
				mesh.push_back((float)chunk->chunkVoxels[i].neighborLight[4]);

				mesh.push_back( 1 * chunk->voxelSizeHalf + chunk->chunkVoxels[i].x * chunk->voxelSizeHalf * 2);
				mesh.push_back( 1 * chunk->voxelSizeHalf + chunk->chunkVoxels[i].y * chunk->voxelSizeHalf * 2);
				mesh.push_back(-1 * chunk->voxelSizeHalf + chunk->chunkVoxels[i].z * chunk->voxelSizeHalf * 2);
				mesh.push_back((1 / 32.0f) + ((1.0f / 32.0f) * chunk->chunkVoxels[i].UVoffset[8]));
				mesh.push_back((1 / 16.0f) + ((1.0f / 16.0f) * chunk->chunkVoxels[i].UVoffset[9]));
				mesh.push_back((float)chunk->chunkVoxels[i].neighborLight[4]);

				mesh.push_back( 1 * chunk->voxelSizeHalf + chunk->chunkVoxels[i].x * chunk->voxelSizeHalf * 2);
				mesh.push_back( 1 * chunk->voxelSizeHalf + chunk->chunkVoxels[i].y * chunk->voxelSizeHalf * 2);
				mesh.push_back( 1 * chunk->voxelSizeHalf + chunk->chunkVoxels[i].z * chunk->voxelSizeHalf * 2);
				mesh.push_back((0 / 32.0f) + ((1.0f / 32.0f) * chunk->chunkVoxels[i].UVoffset[8]));
				mesh.push_back((1 / 16.0f) + ((1.0f / 16.0f) * chunk->chunkVoxels[i].UVoffset[9]));
				mesh.push_back((float)chunk->chunkVoxels[i].neighborLight[4]);

				chunk->verticiesAmount += 6;
			}
			if (chunk->chunkVoxels[i].opaqueNeighbors[5] == false)
			{
				mesh.push_back(-1 * chunk->voxelSizeHalf + chunk->chunkVoxels[i].x * chunk->voxelSizeHalf * 2);
				mesh.push_back( 1 * chunk->voxelSizeHalf + chunk->chunkVoxels[i].y * chunk->voxelSizeHalf * 2);
				mesh.push_back(-1 * chunk->voxelSizeHalf + chunk->chunkVoxels[i].z * chunk->voxelSizeHalf * 2);
				mesh.push_back((0 / 32.0f) + ((1.0f / 32.0f) * chunk->chunkVoxels[i].UVoffset[10]));
				mesh.push_back((1 / 16.0f) + ((1.0f / 16.0f) * chunk->chunkVoxels[i].UVoffset[11]));
				mesh.push_back((float)chunk->chunkVoxels[i].neighborLight[5]);

				mesh.push_back(-1 * chunk->voxelSizeHalf + chunk->chunkVoxels[i].x * chunk->voxelSizeHalf * 2);
				mesh.push_back(-1 * chunk->voxelSizeHalf + chunk->chunkVoxels[i].y * chunk->voxelSizeHalf * 2);
				mesh.push_back(-1 * chunk->voxelSizeHalf + chunk->chunkVoxels[i].z * chunk->voxelSizeHalf * 2);
				mesh.push_back((0 / 32.0f) + ((1.0f / 32.0f) * chunk->chunkVoxels[i].UVoffset[10]));
				mesh.push_back((0 / 16.0f) + ((1.0f / 16.0f) * chunk->chunkVoxels[i].UVoffset[11]));
				mesh.push_back((float)chunk->chunkVoxels[i].neighborLight[5]);

				mesh.push_back(-1 * chunk->voxelSizeHalf + chunk->chunkVoxels[i].x * chunk->voxelSizeHalf * 2);
				mesh.push_back(-1 * chunk->voxelSizeHalf + chunk->chunkVoxels[i].y * chunk->voxelSizeHalf * 2);
				mesh.push_back( 1 * chunk->voxelSizeHalf + chunk->chunkVoxels[i].z * chunk->voxelSizeHalf * 2);
				mesh.push_back((1 / 32.0f) + ((1.0f / 32.0f) * chunk->chunkVoxels[i].UVoffset[10]));
				mesh.push_back((0 / 16.0f) + ((1.0f / 16.0f) * chunk->chunkVoxels[i].UVoffset[11]));
				mesh.push_back((float)chunk->chunkVoxels[i].neighborLight[5]);

				mesh.push_back(-1 * chunk->voxelSizeHalf + chunk->chunkVoxels[i].x * chunk->voxelSizeHalf * 2);
				mesh.push_back(-1 * chunk->voxelSizeHalf + chunk->chunkVoxels[i].y * chunk->voxelSizeHalf * 2);
				mesh.push_back( 1 * chunk->voxelSizeHalf + chunk->chunkVoxels[i].z * chunk->voxelSizeHalf * 2);
				mesh.push_back((1 / 32.0f) + ((1.0f / 32.0f) * chunk->chunkVoxels[i].UVoffset[10]));
				mesh.push_back((0 / 16.0f) + ((1.0f / 16.0f) * chunk->chunkVoxels[i].UVoffset[11]));
				mesh.push_back((float)chunk->chunkVoxels[i].neighborLight[5]);

				mesh.push_back(-1 * chunk->voxelSizeHalf + chunk->chunkVoxels[i].x * chunk->voxelSizeHalf * 2);
				mesh.push_back( 1 * chunk->voxelSizeHalf + chunk->chunkVoxels[i].y * chunk->voxelSizeHalf * 2);
				mesh.push_back( 1 * chunk->voxelSizeHalf + chunk->chunkVoxels[i].z * chunk->voxelSizeHalf * 2);
				mesh.push_back((1 / 32.0f) + ((1.0f / 32.0f) * chunk->chunkVoxels[i].UVoffset[10]));
				mesh.push_back((1 / 16.0f) + ((1.0f / 16.0f) * chunk->chunkVoxels[i].UVoffset[11]));
				mesh.push_back((float)chunk->chunkVoxels[i].neighborLight[5]);

				mesh.push_back(-1 * chunk->voxelSizeHalf + chunk->chunkVoxels[i].x * chunk->voxelSizeHalf * 2);
				mesh.push_back( 1 * chunk->voxelSizeHalf + chunk->chunkVoxels[i].y * chunk->voxelSizeHalf * 2);
				mesh.push_back(-1 * chunk->voxelSizeHalf + chunk->chunkVoxels[i].z * chunk->voxelSizeHalf * 2);
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
				int k = getVoxelLoc(chunk, x, y, z);
				int maxSize = chunk->chunkSize * chunk->chunkSize * chunk->chunkSize;

				chunk->chunkVoxels[k].opaqueNeighbors[0] = true;
				chunk->chunkVoxels[k].opaqueNeighbors[1] = true;
				chunk->chunkVoxels[k].opaqueNeighbors[2] = true;
				chunk->chunkVoxels[k].opaqueNeighbors[3] = true;
				chunk->chunkVoxels[k].opaqueNeighbors[4] = true;
				chunk->chunkVoxels[k].opaqueNeighbors[5] = true;

				// +Z
				if (k + 1 < maxSize && chunk->chunkVoxels[k + 1].z != 0)
				{
					if (chunk->chunkVoxels[k + 1].opaque)
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
					for (int i = 0; i < maxSize; i++)
					{
						if (zPos->chunkVoxels[i].x == chunk->chunkVoxels[k].x && zPos->chunkVoxels[i].y == chunk->chunkVoxels[k].y && zPos->chunkVoxels[i].z == 0)
						{
							if (zPos->chunkVoxels[i].opaque)
							{
								chunk->chunkVoxels[k].opaqueNeighbors[0] = true;
							}
							else
							{
								chunk->chunkVoxels[k].opaqueNeighbors[0] = false;
							}
						}
					}
				}
				else
				{
					chunk->chunkVoxels[k].opaqueNeighbors[0] = false;
				}


				// -Z
				if (k - 1 > -1 && chunk->chunkVoxels[k - 1].z != chunk->chunkSize - 1)
				{
					if (chunk->chunkVoxels[k - 1].opaque)
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
					for (int i = 0; i < maxSize; i++)
					{
						if (zNeg->chunkVoxels[i].x == chunk->chunkVoxels[k].x && zNeg->chunkVoxels[i].y == chunk->chunkVoxels[k].y && zNeg->chunkVoxels[i].z == chunk->chunkSize - 1)
						{
							if (zNeg->chunkVoxels[i].opaque)
							{
								chunk->chunkVoxels[k].opaqueNeighbors[1] = true;
							}
							else
							{
								chunk->chunkVoxels[k].opaqueNeighbors[1] = false;
							}
						}
					}
				}
				else
				{
					chunk->chunkVoxels[k].opaqueNeighbors[1] = false;
				}

				// +Y
				if (k + chunk->chunkSize < maxSize && chunk->chunkVoxels[k + chunk->chunkSize].y != 0)
				{
					if (chunk->chunkVoxels[k + chunk->chunkSize].opaque)
					{
						chunk->chunkVoxels[k].opaqueNeighbors[2] = true;
					}
					else
					{
						chunk->chunkVoxels[k].opaqueNeighbors[2] = false;
					}
				}
				else if (yPos != nullptr)
				{
					for (int i = 0; i < maxSize; i++)
					{
						if (yPos->chunkVoxels[i].x == chunk->chunkVoxels[k].x && yPos->chunkVoxels[i].y == 0 && yPos->chunkVoxels[i].z == chunk->chunkVoxels[k].z)
						{
							if (yPos->chunkVoxels[i].opaque)
							{
								chunk->chunkVoxels[k].opaqueNeighbors[2] = true;
							}
							else
							{
								chunk->chunkVoxels[k].opaqueNeighbors[2] = false;
							}
						}
					}
				}
				else
				{
					chunk->chunkVoxels[k].opaqueNeighbors[2] = false;
				}

				// -Y
				if (k - chunk->chunkSize > -1 && chunk->chunkVoxels[k - chunk->chunkSize].y != chunk->chunkSize - 1)
				{
					if (chunk->chunkVoxels[k - chunk->chunkSize].opaque)
					{
						chunk->chunkVoxels[k].opaqueNeighbors[3] = true;
					}
					else
					{
						chunk->chunkVoxels[k].opaqueNeighbors[3] = false;
					}
				}
				else if (yNeg != nullptr)
				{
					for (int i = 0; i < maxSize; i++)
					{
						if (yNeg->chunkVoxels[i].x == chunk->chunkVoxels[k].x && yNeg->chunkVoxels[i].y == chunk->chunkSize - 1 && yNeg->chunkVoxels[i].z == chunk->chunkVoxels[k].z)
						{
							if (yNeg->chunkVoxels[i].opaque)
							{
								chunk->chunkVoxels[k].opaqueNeighbors[3] = true;
							}
							else
							{
								chunk->chunkVoxels[k].opaqueNeighbors[3] = false;
							}
						}
					}
				}
				else
				{
					chunk->chunkVoxels[k].opaqueNeighbors[3] = false;
				}
				
				// +X
				if (k + chunk->chunkSize * chunk->chunkSize < maxSize && chunk->chunkVoxels[k + chunk->chunkSize * chunk->chunkSize].x != 0)
				{
					if (chunk->chunkVoxels[k + chunk->chunkSize * chunk->chunkSize].opaque)
					{
						chunk->chunkVoxels[k].opaqueNeighbors[4] = true;
					}
					else
					{
						chunk->chunkVoxels[k].opaqueNeighbors[4] = false;
					}
				}
				else if (xPos != nullptr)
				{
					for (int i = 0; i < maxSize; i++)
					{
						if (xPos->chunkVoxels[i].x == 0 && xPos->chunkVoxels[i].y == chunk->chunkVoxels[k].y && xPos->chunkVoxels[i].z == chunk->chunkVoxels[k].z)
						{
							if (xPos->chunkVoxels[i].opaque)
							{
								chunk->chunkVoxels[k].opaqueNeighbors[4] = true;
							}
							else
							{
								chunk->chunkVoxels[k].opaqueNeighbors[4] = false;
							}
						}
					}
				}
				else
				{
					chunk->chunkVoxels[k].opaqueNeighbors[4] = false;
				}

				// -X
				if (k - chunk->chunkSize * chunk->chunkSize > -1 && chunk->chunkVoxels[k - chunk->chunkSize * chunk->chunkSize].x != chunk->chunkSize - 1)
				{
					if (chunk->chunkVoxels[k - chunk->chunkSize * chunk->chunkSize].opaque)
					{
						chunk->chunkVoxels[k].opaqueNeighbors[5] = true;
					}
					else
					{
						chunk->chunkVoxels[k].opaqueNeighbors[5] = false;
					}
				}
				else if (xNeg != nullptr)
				{
					for (int i = 0; i < maxSize; i++)
					{
						if (xNeg->chunkVoxels[i].x == chunk->chunkSize - 1 && xNeg->chunkVoxels[i].y == chunk->chunkVoxels[k].y && xNeg->chunkVoxels[i].z == chunk->chunkVoxels[k].z)
						{
							if (xNeg->chunkVoxels[i].opaque)
							{
								chunk->chunkVoxels[k].opaqueNeighbors[5] = true;
							}
							else
							{
								chunk->chunkVoxels[k].opaqueNeighbors[5] = false;
							}
						}
					}
				}
				else
				{
					chunk->chunkVoxels[k].opaqueNeighbors[5] = false;
				}
			}
		}
	}
}

int ChunkManager::getVoxelLoc(Chunk* chunk, int x, int y, int z)
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

			chunk->chunkVoxels[i].aabb.enabled = false;

			chunk->chunkVoxels[i].aabb.position.x = chunk->chunkVoxels[i].x + chunk->x * chunk->chunkSize;
			chunk->chunkVoxels[i].aabb.position.y = chunk->chunkVoxels[i].y + chunk->y * chunk->chunkSize;
			chunk->chunkVoxels[i].aabb.position.z = chunk->chunkVoxels[i].z + chunk->z * chunk->chunkSize;

			chunk->chunkVoxels[i].aabb.xLength = chunk->voxelSizeHalf * 2;
			chunk->chunkVoxels[i].aabb.yLength = chunk->voxelSizeHalf * 2;
			chunk->chunkVoxels[i].aabb.zLength = chunk->voxelSizeHalf * 2;
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

			chunk->chunkVoxels[i].aabb.enabled = true;

			chunk->chunkVoxels[i].aabb.position.x = chunk->chunkVoxels[i].x + chunk->x * chunk->chunkSize;
			chunk->chunkVoxels[i].aabb.position.y = chunk->chunkVoxels[i].y + chunk->y * chunk->chunkSize;
			chunk->chunkVoxels[i].aabb.position.z = chunk->chunkVoxels[i].z + chunk->z * chunk->chunkSize;

			chunk->chunkVoxels[i].aabb.xLength = chunk->voxelSizeHalf * 2;
			chunk->chunkVoxels[i].aabb.yLength = chunk->voxelSizeHalf * 2;
			chunk->chunkVoxels[i].aabb.zLength = chunk->voxelSizeHalf * 2;
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

			chunk->chunkVoxels[i].aabb.enabled = true;
			chunk->chunkVoxels[i].aabb.position.x = chunk->chunkVoxels[i].x + chunk->x * chunk->chunkSize;
			chunk->chunkVoxels[i].aabb.position.y = chunk->chunkVoxels[i].y + chunk->y * chunk->chunkSize;
			chunk->chunkVoxels[i].aabb.position.z = chunk->chunkVoxels[i].z + chunk->z * chunk->chunkSize;

			chunk->chunkVoxels[i].aabb.xLength = chunk->voxelSizeHalf * 2;
			chunk->chunkVoxels[i].aabb.yLength = chunk->voxelSizeHalf * 2;
			chunk->chunkVoxels[i].aabb.zLength = chunk->voxelSizeHalf * 2;
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

			chunk->chunkVoxels[i].aabb.enabled = true;
			chunk->chunkVoxels[i].aabb.position.x = chunk->chunkVoxels[i].x + chunk->x * chunk->chunkSize;
			chunk->chunkVoxels[i].aabb.position.y = chunk->chunkVoxels[i].y + chunk->y * chunk->chunkSize;
			chunk->chunkVoxels[i].aabb.position.z = chunk->chunkVoxels[i].z + chunk->z * chunk->chunkSize;

			chunk->chunkVoxels[i].aabb.xLength = chunk->voxelSizeHalf * 2;
			chunk->chunkVoxels[i].aabb.yLength = chunk->voxelSizeHalf * 2;
			chunk->chunkVoxels[i].aabb.zLength = chunk->voxelSizeHalf * 2;
			break;
		}
	}
}