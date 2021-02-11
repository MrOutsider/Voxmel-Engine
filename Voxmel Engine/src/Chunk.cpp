#include "Chunk.h"

Chunk::Chunk(int newX, int newY, int newZ)
{
	x = newX;
	y = newY;
	z = newZ;

	chunkAABB.typeOfBody = chunkAABB.STATIC;

	chunkAABB.position.x = newX * chunkSize + (chunkSize - 1)  * voxelSizeHalf;
	chunkAABB.position.y = newY * chunkSize + (chunkSize - 1)  * voxelSizeHalf;
	chunkAABB.position.z = newZ * chunkSize + (chunkSize - 1)  * voxelSizeHalf;

	chunkAABB.xLength = chunkSize;
	chunkAABB.yLength = chunkSize;
	chunkAABB.zLength = chunkSize;
}

Chunk::~Chunk()
{
}