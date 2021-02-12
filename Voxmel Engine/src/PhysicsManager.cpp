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
					if (isPointAABB(raycastList[i]->position.x, raycastList[i]->position.y, raycastList[i]->position.z, *chunkBoxList[n]))
					{
						raycastList[i]->listOfIntersecting.push_back(chunkBoxList[n]->ID);
						for (unsigned int m = 0; m < chunkBoxList[n]->voxelBoxList.size(); m++)
						{
							if (chunkBoxList[n]->voxelBoxList[m]->enabled)
							{
								if (isPointAABB(raycastList[i]->position.x, raycastList[i]->position.y, raycastList[i]->position.z, *chunkBoxList[n]->voxelBoxList[m]))
								{
									raycastList[i]->isIntersecting = 1.0f;
									raycastList[i]->listOfIntersecting.push_back(chunkBoxList[n]->voxelBoxList[m]->ID);
									AABB_RenderList.push_back(chunkBoxList[n]->voxelBoxList[m]);
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

int PhysicsManager::isRayAABB(Raycast ray, AABB aabb)
{
	return -1;
}