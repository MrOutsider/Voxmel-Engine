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

	std::vector<unsigned int> checkedIDs;

	for (unsigned int i = 0; i < aabbList.size(); i++)
	{
		for (unsigned int n = 0; n < aabbList.size(); n++)
		{
			bool checked = false;

			for (unsigned int m = 0; m < checkedIDs.size(); m++)
			{
				if (aabbList[n]->ID == checkedIDs[m])
				{
					checked = true;
				}
			}

			if (aabbList[i]->enabled)
			{
				if (isAABB_Intersect(*aabbList[i], *aabbList[n]) && aabbList[i]->ID != aabbList[n]->ID)
				{
					aabbList[i]->isIntersecting = 1.0f;
				}
			}
			else
			{
				aabbList[i]->isIntersecting = 2.0f;
			}
		}
		checkedIDs.push_back(aabbList[i]->ID);
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
