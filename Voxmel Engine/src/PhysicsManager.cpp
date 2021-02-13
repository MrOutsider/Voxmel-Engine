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

	AABB_RenderList.clear();
	raycastRenderList.clear();

	for (unsigned int i = 0; i < dynamicList.size(); i++)
	{
		dynamicList[i]->isIntersecting = 2.0f;
		dynamicList[i]->listOfIntersecting.clear();
	}
	for (unsigned int i = 0; i < chunkBoxList.size(); i++)
	{
		chunkBoxList[i]->isIntersecting = 0.0f;
		chunkBoxList[i]->listOfIntersecting.clear();
	}

	for (unsigned int i = 0; i < raycastList.size(); i++)
	{
		raycastList[i]->isIntersecting = 2.0f;
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
						chunkBoxList[n]->isIntersecting = 1.0f;
						dynamicList[i]->listOfIntersecting.push_back(chunkBoxList[n]->ID);
						AABB_RenderList.push_back(chunkBoxList[n]);

						for (unsigned int m = 0; m < chunkBoxList[n]->voxelBoxList.size(); m++)
						{
							if (chunkBoxList[n]->voxelBoxList[m]->enabled)
							{
								if (isAABB_AABB(*dynamicList[i], *chunkBoxList[n]->voxelBoxList[m]))
								{
									dynamicList[i]->isIntersecting = 1.0f;
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
						raycastList[i]->isIntersecting = 0.0f;
						raycastList[i]->listOfIntersecting.push_back(chunkBoxList[n]->ID);
						for (unsigned int m = 0; m < chunkBoxList[n]->voxelBoxList.size(); m++)
						{
							if (chunkBoxList[n]->voxelBoxList[m]->enabled)
							{
								rayResult = isRayAABB(*raycastList[i], *chunkBoxList[n]->voxelBoxList[m]);
								if (rayResult != -1 && rayResult < raycastList[i]->length)
								{
									raycastList[i]->isIntersecting = 1.0f;
									AABB_RenderList.push_back(chunkBoxList[n]->voxelBoxList[m]);
									raycastList[i]->listOfIntersecting.push_back(chunkBoxList[n]->voxelBoxList[m]->ID);

								}
							}
						}
					}
					else if (rayResult != -1 && rayResult < raycastList[i]->length)
					{
						raycastList[i]->isIntersecting = 0.0f;
						raycastList[i]->listOfIntersecting.push_back(chunkBoxList[n]->ID);
						for (unsigned int m = 0; m < chunkBoxList[n]->voxelBoxList.size(); m++)
						{
							if (chunkBoxList[n]->voxelBoxList[m]->enabled)
							{
								rayResult = isRayAABB(*raycastList[i], *chunkBoxList[n]->voxelBoxList[m]);
								if (rayResult != -1 && rayResult < raycastList[i]->length)
								{
									raycastList[i]->isIntersecting = 1.0f;
									AABB_RenderList.push_back(chunkBoxList[n]->voxelBoxList[m]);
									raycastList[i]->listOfIntersecting.push_back(chunkBoxList[n]->voxelBoxList[m]->ID);

								}
							}
						}
					}
				}
			}
			// Cull Raycast -> listOfIntersecting for closest
			for (unsigned int n = 0; n < raycastList[i]->listOfIntersecting.size(); n++)
			{
				unsigned int chunkID;
				unsigned int voxelID;
				for (unsigned int m = 0; m < chunkBoxList.size(); m++)
				{
					if (chunkBoxList[m]->ID == raycastList[i]->listOfIntersecting[n])
					{
						for (unsigned int j = 0; j < chunkBoxList[m]->voxelBoxList.size(); j++)
						{
							for (unsigned int k = 0; k < raycastList[i]->listOfIntersecting.size(); k++)
							{
								if (chunkBoxList[m]->voxelBoxList[j]->ID == raycastList[i]->listOfIntersecting[k])
								{
									// Continued...
								}
							}
						}
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
	return 0.0f;
}