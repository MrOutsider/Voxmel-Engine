#include "PhysicsManager.h"

PhysicsManager::PhysicsManager()
{
}

unsigned int PhysicsManager::assignID()
{
	return nextID;
	nextID++;
}

void PhysicsManager::addDynamic_AABB(AABB& aabb)
{
	dynamicList.push_back(&aabb);
}

void PhysicsManager::removeDynamic_AABB(AABB& aabb)
{
	for (unsigned i = 0; i < dynamicList.size(); i++)
	{
		if (dynamicList[i]->ID == aabb.ID)
		{
			dynamicList.erase(dynamicList.begin() + i);
			return;
		}
	}
}

void PhysicsManager::addRaycast(Raycast& ray)
{
	raycastList.push_back(&ray);
}

void PhysicsManager::removeRaycast(Raycast& ray)
{
	for (unsigned i = 0; i < raycastList.size(); i++)
	{
		if (raycastList[i]->ID == ray.ID)
		{
			raycastList.erase(raycastList.begin() + i);
			return;
		}
	}
}

void PhysicsManager::update(float delta)
{
	// Apply velocity and gravity

	const float COLOR_GREEN	= 0.0f;
	const float COLOR_RED	= 1.0f;
	const float COLOR_BLUE	= 2.0f;

	AABB_RenderList.clear();
	raycastRenderList.clear();

	struct TempChunk
	{
		CHUNK_AABB* chunk;
		std::vector<AABB*> voxels;
	};

	for (unsigned int i = 0; i < dynamicList.size(); i++)
	{
		dynamicList[i]->isIntersecting = COLOR_BLUE;
		dynamicList[i]->listOfIntersecting.clear();
	}
	for (unsigned int i = 0; i < chunkBoxList.size(); i++)
	{
		chunkBoxList[i]->isIntersecting = COLOR_GREEN;
		chunkBoxList[i]->listOfIntersecting.clear();
	}

	for (unsigned int i = 0; i < raycastList.size(); i++)
	{
		raycastList[i]->isIntersecting = COLOR_BLUE;
		raycastList[i]->listOfIntersecting.clear();
	}

	for (unsigned int i = 0; i < dynamicList.size(); i++)
	{
		if (dynamicList[i]->enabled)
		{
			AABB_RenderList.push_back(dynamicList[i]);

			for (unsigned int n = 0; n < chunkBoxList.size(); n++)
			{
				if (chunkBoxList[n]->enabled)
				{
					if (isAABB_AABB(*dynamicList[i], *chunkBoxList[n]))
					{
						chunkBoxList[n]->isIntersecting = COLOR_RED;
						dynamicList[i]->listOfIntersecting.push_back(chunkBoxList[n]->ID);
						AABB_RenderList.push_back(chunkBoxList[n]);

						for (unsigned int m = 0; m < chunkBoxList[n]->voxelBoxList.size(); m++)
						{
							if (chunkBoxList[n]->voxelBoxList[m]->enabled)
							{
								if (isAABB_AABB(*dynamicList[i], *chunkBoxList[n]->voxelBoxList[m]))
								{
									dynamicList[i]->isIntersecting = COLOR_RED;
									dynamicList[i]->listOfIntersecting.push_back(chunkBoxList[n]->voxelBoxList[m]->ID);
									AABB_RenderList.push_back(chunkBoxList[n]->voxelBoxList[m]);
								}
							}
						}
					}
				}
			}
		}
	}

	float rayResult = -1.0f;
	std::vector<TempChunk> rayChunks;

	for (unsigned int i = 0; i < raycastList.size(); i++)
	{
		if (raycastList[i]->enabled)
		{
			if (raycastList[i]->visable)
			{
				raycastRenderList.push_back(raycastList[i]);
			}
			for (unsigned int n = 0; n < chunkBoxList.size(); n++)
			{
				if (chunkBoxList[n]->enabled)
				{
					rayResult = isRayAABB(*raycastList[i], *chunkBoxList[n]);
					if (isPointAABB(raycastList[i]->position.x, raycastList[i]->position.y, raycastList[i]->position.z, *chunkBoxList[n]))
					{
						raycastList[i]->isIntersecting = COLOR_GREEN;
						TempChunk newTempChunk;
						newTempChunk.chunk = chunkBoxList[n];
						for (unsigned int m = 0; m < chunkBoxList[n]->voxelBoxList.size(); m++)
						{
							if (chunkBoxList[n]->voxelBoxList[m]->enabled)
							{
								rayResult = isRayAABB(*raycastList[i], *chunkBoxList[n]->voxelBoxList[m]);
								if (rayResult != -1 && rayResult < raycastList[i]->length)
								{
									raycastList[i]->isIntersecting = COLOR_RED;
									newTempChunk.voxels.push_back(chunkBoxList[n]->voxelBoxList[m]);
									//AABB_RenderList.push_back(chunkBoxList[n]->voxelBoxList[m]);

								}
							}
						}
						rayChunks.push_back(newTempChunk);
					}
					else if (rayResult != -1 && rayResult < raycastList[i]->length)
					{
						raycastList[i]->isIntersecting = COLOR_GREEN;
						TempChunk newTempChunk;
						newTempChunk.chunk = chunkBoxList[n];
						for (unsigned int m = 0; m < chunkBoxList[n]->voxelBoxList.size(); m++)
						{
							if (chunkBoxList[n]->voxelBoxList[m]->enabled)
							{
								rayResult = isRayAABB(*raycastList[i], *chunkBoxList[n]->voxelBoxList[m]);
								if (rayResult != -1 && rayResult < raycastList[i]->length)
								{
									raycastList[i]->isIntersecting = COLOR_RED;
									newTempChunk.voxels.push_back(chunkBoxList[n]->voxelBoxList[m]);
									//AABB_RenderList.push_back(chunkBoxList[n]->voxelBoxList[m]);
								}
							}
						}
						rayChunks.push_back(newTempChunk);
					}
				}
			}

			bool thereIsA_ChunkRight = false;
			unsigned int chunkIndex = 0;
			CHUNK_AABB* chunkToTest = nullptr;
			float chunkToCamDist = 0.0f;
			for (unsigned int n = 0; n < rayChunks.size(); n++)
			{
				if (rayChunks.size() < 2)
				{
					raycastList[i]->closestChunk = rayChunks[0].chunk;
					thereIsA_ChunkRight = true;
				}
				else if (n == 0)
				{
					chunkToTest = rayChunks[0].chunk;
					thereIsA_ChunkRight = true;
					chunkToCamDist = distBetweenPoints(raycastList[i]->position, rayChunks[0].chunk->position);
				}
				else
				{
					float distToCompare = distBetweenPoints(raycastList[i]->position, rayChunks[n].chunk->position);
					if (distToCompare < chunkToCamDist)
					{
						chunkToTest = rayChunks[n].chunk;
						chunkToCamDist = distToCompare;
						chunkIndex = n;
						thereIsA_ChunkRight = true;
					}
				}
			}

			bool thereIsA_VoxelRight = false;
			unsigned int voxelIndex = 0;
			AABB* voxelToTest = nullptr;
			float voxelToCamDist = 0.0f;
			if (thereIsA_ChunkRight)
			{
				for (unsigned int n = 0; n < rayChunks[chunkIndex].voxels.size(); n++)
				{
					if (rayChunks[chunkIndex].voxels.size() < 2)
					{
						raycastList[i]->closestVoxel = rayChunks[chunkIndex].voxels[n];
						thereIsA_VoxelRight = true;
					}
					else if (n == 0)
					{
						voxelToTest = rayChunks[chunkIndex].voxels[0];
						thereIsA_VoxelRight = true;
						voxelToCamDist = distBetweenPoints(raycastList[i]->position, rayChunks[chunkIndex].voxels[0]->position);
					}
					else
					{
						float distToCompare = distBetweenPoints(raycastList[i]->position, rayChunks[chunkIndex].voxels[n]->position);
						if (distToCompare < voxelToCamDist)
						{
							voxelToTest = rayChunks[chunkIndex].voxels[n];
							voxelToCamDist = distToCompare;
							voxelIndex = n;
							thereIsA_VoxelRight = true;
						}
					}
				}
				if (thereIsA_ChunkRight)
				{
					rayChunks[chunkIndex].chunk->isIntersecting = COLOR_RED;
					AABB_RenderList.push_back(rayChunks[chunkIndex].chunk);
					if (thereIsA_VoxelRight)
					{
						AABB_RenderList.push_back(rayChunks[chunkIndex].voxels[voxelIndex]);
					}
				}
			}
		}
	}
}

bool PhysicsManager::isPointAABB(float x, float y, float z, AABB& box)
{
	if (x >= box.position.x - box.xLength * 0.5f && x < box.position.x + box.xLength * 0.5f &&
		y >= box.position.y - box.yLength * 0.5f && y < box.position.y + box.yLength * 0.5f &&
		z >= box.position.z - box.zLength * 0.5f && z < box.position.z + box.zLength * 0.5f)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool PhysicsManager::isAABB_AABB(AABB& a, AABB& b)
{
	if (a.position.x - a.xLength * 0.5f <= b.position.x + b.xLength * 0.5f && a.position.x + a.xLength * 0.5f >= b.position.x - b.xLength * 0.5f &&
		a.position.y - a.yLength * 0.5f <= b.position.y + b.yLength * 0.5f && a.position.y + a.yLength * 0.5f >= b.position.y - b.yLength * 0.5f &&
		a.position.z - a.zLength * 0.5f <= b.position.z + b.zLength * 0.5f && a.position.z + a.zLength * 0.5f >= b.position.z - b.zLength * 0.5f)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int PhysicsManager::isRayAABB(Raycast& ray, AABB& aabb)
{
	float t1 = ((aabb.position.x - aabb.xLength * 0.5f) - ray.position.x) / ray.Direction.x;
	float t2 = ((aabb.position.x + aabb.xLength * 0.5f) - ray.position.x) / ray.Direction.x;
	float t3 = ((aabb.position.y - aabb.yLength * 0.5f) - ray.position.y) / ray.Direction.y;
	float t4 = ((aabb.position.y + aabb.yLength * 0.5f) - ray.position.y) / ray.Direction.y;
	float t5 = ((aabb.position.z - aabb.zLength * 0.5f) - ray.position.z) / ray.Direction.z;
	float t6 = ((aabb.position.z + aabb.zLength * 0.5f) - ray.position.z) / ray.Direction.z;

	float tmin = std::max(std::max(std::min(t1, t2), std::min(t3, t4)), std::min(t5, t6));
	float tmax = std::min(std::min(std::max(t1, t2), std::max(t3, t4)), std::max(t5, t6));

	// if tmax < 0, ray (line) is intersecting AABB, but whole AABB is behing us
	if (tmax < 0) {
		return -1;
	}

	// if tmin > tmax, ray doesn't intersect AABB
	if (tmin > tmax) {
		return -1;
	}

	if (tmin < 0.0f) {
		return tmax;
	}
	return tmin;
}

float PhysicsManager::distBetweenPoints(glm::vec3& positionOne, glm::vec3& positionTwo)
{
	return std::sqrt(std::pow(positionTwo.x - positionOne.x, 2.0f) + std::pow(positionTwo.y - positionOne.y, 2.0f) + std::pow(positionTwo.z - positionOne.z, 2.0f));
}