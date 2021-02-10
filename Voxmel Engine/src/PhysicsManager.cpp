#include "PhysicsManager.h"

PhysicsManager::PhysicsManager()
{
}

void PhysicsManager::addAABB(AABB& obj)
{
	aabbList.push_back(&obj);
}

void PhysicsManager::update(float delta)
{
	// Apply velocity and gravity

	for (unsigned int i = 0; i < aabbList.size(); i++)
	{
		aabbList[i]->isIntersecting = 0.0f;
	}

	for (unsigned int i = 0; i < aabbList.size(); i++)
	{
		for (unsigned int n = 0; n < aabbList.size(); n++)
		{
			if (aabbList[i]->enabled)
			{
				if (aabbList[i]->typeOfBody == aabbList[i]->KINEMATIC)
				{
					if (aabbList[n]->typeOfBody == aabbList[n]->STATIC)
					{
						if (isAABB_Intersect(*aabbList[i], *aabbList[n]) && aabbList[i]->ID != aabbList[n]->ID)
						{
							aabbList[i]->isIntersecting = 1.0f;
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
	if (a.position.x - a.xLength * 0.5f < b.position.x + b.xLength * 0.5f && a.position.x + a.xLength * 0.5f > b.position.x - b.xLength * 0.5f &&
		a.position.y - a.yLength * 0.5f < b.position.y + b.yLength * 0.5f && a.position.y + a.yLength * 0.5f > b.position.y - b.yLength * 0.5f &&
		a.position.z - a.zLength * 0.5f < b.position.z + b.zLength * 0.5f && a.position.z + a.zLength * 0.5f > b.position.z - b.zLength * 0.5f)
	{
		return true;
	}
	else
	{
		return false;
	}
}
