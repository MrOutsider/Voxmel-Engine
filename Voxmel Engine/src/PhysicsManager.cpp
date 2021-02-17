#include "PhysicsManager.h"

PhysicsManager::PhysicsManager()
{
}

unsigned int PhysicsManager::assignID()
{
	return nextID;
	nextID++;
}

void PhysicsManager::addChunk_AABB(CHUNK_AABB& chunk)
{
	chunkBoxList.push_back(&chunk);
}

void PhysicsManager::removeDynamic_AABB(CHUNK_AABB& chunk)
{
	for (unsigned i = 0; i < chunkBoxList.size(); i++)
	{
		if (chunkBoxList[i]->ID == chunk.ID)
		{
			chunkBoxList.erase(chunkBoxList.begin() + i);
			return;
		}
	}
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
	// Clear all list for rendering & reset colors
	AABB_RenderList.clear();
	raycastRenderList.clear();

	for (unsigned int i = 0; i < dynamicList.size(); i++)
	{
		dynamicList[i]->color = Colors.BLUE;
	}
	for (unsigned int i = 0; i < chunkBoxList.size(); i++)
	{
		chunkBoxList[i]->color = Colors.GREEN;
		for (unsigned int n = 0; n < chunkBoxList[i]->voxelBoxList.size(); n++)
		{
			chunkBoxList[i]->voxelBoxList[n]->color = Colors.GREEN;
		}
	}
	for (unsigned int i = 0; i < raycastList.size(); i++)
	{
		raycastList[i]->color = Colors.BLUE;
		raycastList[i]->collisionPosition = glm::vec3(0.0f);
		raycastList[i]->closestVoxel = nullptr;
		raycastList[i]->closestVoxelsChunk = nullptr;
		raycastList[i]->closestDynamic = nullptr;
	}

	// Test dynamic physics bodys against static bodys
	for (unsigned int i = 0; i < dynamicList.size(); i++)
	{
		if (dynamicList[i]->enabled)
		{
			AABB_RenderList.push_back(dynamicList[i]);
			for (unsigned int n = 0; n < chunkBoxList.size(); n++)
			{
				if (chunkBoxList[n]->enabled)
				{
					if (isAABB_AABB(dynamicList[i], chunkBoxList[n]))
					{
						chunkBoxList[n]->color = Colors.RED;
						AABB_RenderList.push_back(chunkBoxList[n]);

						for (unsigned int m = 0; m < chunkBoxList[n]->voxelBoxList.size(); m++)
						{
							if (chunkBoxList[n]->voxelBoxList[m]->enabled)
							{
								if (isAABB_AABB(dynamicList[i], chunkBoxList[n]->voxelBoxList[m]))
								{
									dynamicList[i]->color = Colors.RED;
									AABB_RenderList.push_back(chunkBoxList[n]->voxelBoxList[m]);
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
	for (unsigned int i = 0; i < raycastList.size(); i++)
	{
		if (raycastList[i]->enabled)
		{
			float rayResult = -1.0f;
			std::vector<AABB*> rayVoxelsIntersected;

			raycastRenderList.push_back(raycastList[i]);

			for (unsigned int n = 0; n < chunkBoxList.size(); n++)
			{
				if (chunkBoxList[n]->enabled)
				{
					rayResult = isRayAABB(raycastList[i], chunkBoxList[n]);
					if (isPointAABB(raycastList[i]->position.x, raycastList[i]->position.y, raycastList[i]->position.z, chunkBoxList[n]))
					{
						for (unsigned int m = 0; m < chunkBoxList[n]->voxelBoxList.size(); m++)
						{
							if (chunkBoxList[n]->voxelBoxList[m]->enabled)
							{
								rayResult = isRayAABB(raycastList[i], chunkBoxList[n]->voxelBoxList[m]);
								if (rayResult != -1 && rayResult < raycastList[i]->length)
								{
									raycastList[i]->color = Colors.RED;
									rayVoxelsIntersected.push_back(chunkBoxList[n]->voxelBoxList[m]);
								}
							}
						}
					}
					else if (rayResult != -1 && rayResult < raycastList[i]->length)
					{
						for (unsigned int m = 0; m < chunkBoxList[n]->voxelBoxList.size(); m++)
						{
							if (chunkBoxList[n]->voxelBoxList[m]->enabled)
							{
								rayResult = isRayAABB(raycastList[i], chunkBoxList[n]->voxelBoxList[m]);
								if (rayResult != -1 && rayResult < raycastList[i]->length)
								{
									raycastList[i]->color = Colors.RED;
									rayVoxelsIntersected.push_back(chunkBoxList[n]->voxelBoxList[m]);
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
					voxelDistToRay = distBetweenPoints(closestVoxelToRay->position, raycastList[i]->position);
				}
				else
				{
					float distToCompare = distBetweenPoints(rayVoxelsIntersected[n]->position, raycastList[i]->position);
					if (distToCompare < voxelDistToRay)
					{
						closestVoxelToRay = rayVoxelsIntersected[n];
						voxelDistToRay = distToCompare;
					}
				}
			}

			if (closestVoxelToRay != nullptr)
			{
				raycastList[i]->closestVoxel = closestVoxelToRay;
				raycastList[i]->closestVoxelsChunk = findVoxelsChunk(closestVoxelToRay);
				raycastList[i]->collisionPosition = raycastList[i]->position + raycastList[i]->Direction * isRayAABB(raycastList[i], closestVoxelToRay);
				closestVoxelToRay->color = Colors.RED;
				AABB_RenderList.push_back(closestVoxelToRay);
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

	for (unsigned int i = 0; i < chunkBoxList.size(); i++)
	{
		if (chunkBoxList[i]->chunkX == x && chunkBoxList[i]->chunkY == y && chunkBoxList[i]->chunkZ == z)
		{
			return chunkBoxList[i];
		}
	}
}
