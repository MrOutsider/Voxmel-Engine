#include "PhysicsManager.h"

PhysicsManager::PhysicsManager(std::vector<AABB*>& dynamicB, std::vector<CHUNK_AABB*>& staticChunkB, std::vector<Raycast*>& rays, std::vector<AABB*>& aabbRenderL, std::vector<Raycast*>& raycastRenderL)
{
	dynamicList = &dynamicB;
	chunkBoxList = &staticChunkB;
	raycastList = &rays;

	AABB_RenderList = &aabbRenderL;
	raycastRenderList = &raycastRenderL;
}

unsigned int PhysicsManager::assignID()
{
	return nextID;
	nextID++;
}

void PhysicsManager::addChunk_AABB(CHUNK_AABB& chunk)
{
	chunkBoxList[0].push_back(&chunk);
}

void PhysicsManager::removeDynamic_AABB(CHUNK_AABB& chunk)
{
	for (unsigned i = 0; i < chunkBoxList[0].size(); i++)
	{
		if (chunkBoxList[0][i]->ID == chunk.ID)
		{
			chunkBoxList[0].erase(chunkBoxList[0].begin() + i);
			return;
		}
	}
}

void PhysicsManager::addDynamic_AABB(AABB& aabb)
{
	dynamicList[0].push_back(&aabb);
}

void PhysicsManager::removeDynamic_AABB(AABB& aabb)
{
	for (unsigned i = 0; i < dynamicList[0].size(); i++)
	{
		if (dynamicList[0][i]->ID == aabb.ID)
		{
			dynamicList[0].erase(dynamicList[0].begin() + i);
			return;
		}
	}
}

void PhysicsManager::addRaycast(Raycast& ray)
{
	raycastList[0].push_back(&ray);
}

void PhysicsManager::removeRaycast(Raycast& ray)
{
	for (unsigned i = 0; i < raycastList[0].size(); i++)
	{
		if (raycastList[0][i]->ID == ray.ID)
		{
			raycastList[0].erase(raycastList[0].begin() + i);
			return;
		}
	}
}

void PhysicsManager::update(float delta)
{
	// Clear all list for rendering & reset colors
	AABB_RenderList[0].clear();
	raycastRenderList[0].clear();

	for (unsigned int i = 0; i < dynamicList[0].size(); i++)
	{
		dynamicList[0][i]->color = Colors.BLUE;
	}
	for (unsigned int i = 0; i < chunkBoxList[0].size(); i++)
	{
		chunkBoxList[0][i]->color = Colors.GREEN;
		for (unsigned int n = 0; n < chunkBoxList[0][i]->voxelBoxList.size(); n++)
		{
			chunkBoxList[0][i]->voxelBoxList[n]->color = Colors.GREEN;
		}
	}
	for (unsigned int i = 0; i < raycastList[0].size(); i++)
	{
		raycastList[0][i]->color = Colors.BLUE;
		raycastList[0][i]->collisionPosition = glm::vec3(0.0f);
		raycastList[0][i]->closestVoxel = nullptr;
		raycastList[0][i]->closestVoxelsChunk = nullptr;
		raycastList[0][i]->closestDynamic = nullptr;
	}

	// Test dynamic physics bodys against static bodys
	for (unsigned int i = 0; i < dynamicList[0].size(); i++)
	{
		if (dynamicList[0][i]->enabled)
		{
			AABB_RenderList[0].push_back(dynamicList[0][i]);
			for (unsigned int n = 0; n < chunkBoxList[0].size(); n++)
			{
				if (chunkBoxList[0][n]->enabled)
				{
					if (isAABB_AABB(dynamicList[0][i], chunkBoxList[0][n]))
					{
						chunkBoxList[0][n]->color = Colors.RED;
						AABB_RenderList[0].push_back(chunkBoxList[0][n]);

						for (unsigned int m = 0; m < chunkBoxList[0][n]->voxelBoxList.size(); m++)
						{
							if (chunkBoxList[0][n]->voxelBoxList[m]->enabled)
							{
								if (isAABB_AABB(dynamicList[0][i], chunkBoxList[0][n]->voxelBoxList[m]))
								{
									dynamicList[0][i]->color = Colors.RED;
									AABB_RenderList[0].push_back(chunkBoxList[0][n]->voxelBoxList[m]);
								}
							}
						}
					}
				}
			}
		}
	}

	// Check raycast then cull for closest
	// TODO : Add dynamic to raycast detection
	for (unsigned int i = 0; i < raycastList[0].size(); i++)
	{
		if (raycastList[0][i]->enabled)
		{
			float rayResult = -1.0f;
			std::vector<AABB*> rayVoxelsIntersected;

			raycastRenderList[0].push_back(raycastList[0][i]);

			for (unsigned int n = 0; n < chunkBoxList[0].size(); n++)
			{
				if (chunkBoxList[0][n]->enabled)
				{
					rayResult = isRayAABB(raycastList[0][i], chunkBoxList[0][n]);
					if (isPointAABB(raycastList[0][i]->position.x, raycastList[0][i]->position.y, raycastList[0][i]->position.z, chunkBoxList[0][n]))
					{
						for (unsigned int m = 0; m < chunkBoxList[0][n]->voxelBoxList.size(); m++)
						{
							if (chunkBoxList[0][n]->voxelBoxList[m]->enabled)
							{
								rayResult = isRayAABB(raycastList[0][i], chunkBoxList[0][n]->voxelBoxList[m]);
								if (rayResult != -1 && rayResult < raycastList[0][i]->length)
								{
									raycastList[0][i]->color = Colors.RED;
									rayVoxelsIntersected.push_back(chunkBoxList[0][n]->voxelBoxList[m]);
								}
							}
						}
					}
					else if (rayResult != -1 && rayResult < raycastList[0][i]->length)
					{
						for (unsigned int m = 0; m < chunkBoxList[0][n]->voxelBoxList.size(); m++)
						{
							if (chunkBoxList[0][n]->voxelBoxList[m]->enabled)
							{
								rayResult = isRayAABB(raycastList[0][i], chunkBoxList[0][n]->voxelBoxList[m]);
								if (rayResult != -1 && rayResult < raycastList[0][i]->length)
								{
									raycastList[0][i]->color = Colors.RED;
									rayVoxelsIntersected.push_back(chunkBoxList[0][n]->voxelBoxList[m]);
								}
							}
						}
					}
				}
			}

			AABB* closestVoxelToRay = nullptr;
			float voxelDistToRay;

			for (unsigned int n = 0; n < rayVoxelsIntersected.size(); n++)
			{
				if (n == 0)
				{
					closestVoxelToRay = rayVoxelsIntersected[0];
					voxelDistToRay = distBetweenPoints(closestVoxelToRay->position, raycastList[0][i]->position);
				}
				else
				{
					float distToCompare = distBetweenPoints(rayVoxelsIntersected[n]->position, raycastList[0][i]->position);
					if (distToCompare < voxelDistToRay)
					{
						closestVoxelToRay = rayVoxelsIntersected[n];
						voxelDistToRay = distToCompare;
					}
				}
			}

			if (closestVoxelToRay != nullptr)
			{
				raycastList[0][i]->closestVoxel = closestVoxelToRay;
				raycastList[0][i]->closestVoxelsChunk = findVoxelsChunk(closestVoxelToRay);
				raycastList[0][i]->collisionPosition = raycastList[0][i]->position + raycastList[0][i]->Direction * isRayAABB(raycastList[0][i], closestVoxelToRay);
				closestVoxelToRay->color = Colors.RED;
				AABB_RenderList[0].push_back(closestVoxelToRay);
			}
		}
	}
}

bool PhysicsManager::isPointAABB(float x, float y, float z, AABB* box)
{
	if (x >= box->position.x - box->xLength * 0.5f && x < box->position.x + box->xLength * 0.5f &&
		y >= box->position.y - box->yLength * 0.5f && y < box->position.y + box->yLength * 0.5f &&
		z >= box->position.z - box->zLength * 0.5f && z < box->position.z + box->zLength * 0.5f)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool PhysicsManager::isAABB_AABB(AABB* a, AABB* b)
{
	if (a->position.x - a->xLength * 0.5f <= b->position.x + b->xLength * 0.5f && a->position.x + a->xLength * 0.5f >= b->position.x - b->xLength * 0.5f &&
		a->position.y - a->yLength * 0.5f <= b->position.y + b->yLength * 0.5f && a->position.y + a->yLength * 0.5f >= b->position.y - b->yLength * 0.5f &&
		a->position.z - a->zLength * 0.5f <= b->position.z + b->zLength * 0.5f && a->position.z + a->zLength * 0.5f >= b->position.z - b->zLength * 0.5f)
	{
		return true;
	}
	else
	{
		return false;
	}
}

float PhysicsManager::isRayAABB(Raycast* ray, AABB* aabb)
{
	float t1 = ((aabb->position.x - aabb->xLength * 0.5f) - ray->position.x) / ray->Direction.x;
	float t2 = ((aabb->position.x + aabb->xLength * 0.5f) - ray->position.x) / ray->Direction.x;
	float t3 = ((aabb->position.y - aabb->yLength * 0.5f) - ray->position.y) / ray->Direction.y;
	float t4 = ((aabb->position.y + aabb->yLength * 0.5f) - ray->position.y) / ray->Direction.y;
	float t5 = ((aabb->position.z - aabb->zLength * 0.5f) - ray->position.z) / ray->Direction.z;
	float t6 = ((aabb->position.z + aabb->zLength * 0.5f) - ray->position.z) / ray->Direction.z;

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

CHUNK_AABB* PhysicsManager::findVoxelsChunk(AABB* voxel)
{
	int x = (voxel->position.x + 1) / 16; // 16 <--- Chunk Size
	int y = (voxel->position.y + 1) / 16; // 16 <--- Chunk Size
	int z = (voxel->position.z + 1) / 16; // 16 <--- Chunk Size

	for (unsigned int i = 0; i < chunkBoxList[0].size(); i++)
	{
		if (chunkBoxList[0][i]->chunkX == x && chunkBoxList[0][i]->chunkY == y && chunkBoxList[0][i]->chunkZ == z)
		{
			return chunkBoxList[0][i];
		}
	}
}
