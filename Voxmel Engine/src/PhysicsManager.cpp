#include "PhysicsManager.h"

PhysicsManager::PhysicsManager()
{
}

void PhysicsManager::addAABB(AABB& obj)
{
	//chunkBoxList.push_back(&obj);
}

void PhysicsManager::removeAABB(AABB& obj)
{
	/*for (unsigned i = 0; i < chunkBoxList.size(); i++)
	{
		if (chunkBoxList[i]->ID == obj.ID)
		{
			chunkBoxList.erase(chunkBoxList.begin() + i);
		}
	}*/
}

void PhysicsManager::update(float delta)
{
	// Apply velocity and gravity

	physicsRenderList.clear();

	for (unsigned int i = 0; i < dynamicList.size(); i++)
	{
		dynamicList[i]->isIntersecting = 2.0f;
	}

	for (unsigned int i = 0; i < chunkBoxList.size(); i++)
	{
		chunkBoxList[i]->isIntersecting = 0.0f;
	}

	for (unsigned int i = 0; i < dynamicList.size(); i++)
	{
		if (dynamicList[i]->enabled)
		{
			physicsRenderList.push_back(dynamicList[i]);

			for (unsigned int n = 0; n < chunkBoxList.size(); n++)
			{
				if (chunkBoxList[n]->enabled)
				{
					if (isAABB_Intersect(*dynamicList[i], *chunkBoxList[n]))
					{
						chunkBoxList[n]->isIntersecting = 1.0f;
						physicsRenderList.push_back(chunkBoxList[n]);

						for (unsigned int m = 0; m < chunkBoxList[n]->voxelBoxList.size(); m++)
						{
							if (chunkBoxList[n]->voxelBoxList[m]->enabled)
							{
								if (isAABB_Intersect(*dynamicList[i], *chunkBoxList[n]->voxelBoxList[m]))
								{
									dynamicList[i]->isIntersecting = 1.0f;
									physicsRenderList.push_back(chunkBoxList[n]->voxelBoxList[m]);
								}
							}
						}
					}
				}
			}
		}
	}
}

bool PhysicsManager::isPointInside(float x, float y, float z, AABB& box)
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

bool PhysicsManager::isAABB_Intersect(AABB& a, AABB& b)
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
