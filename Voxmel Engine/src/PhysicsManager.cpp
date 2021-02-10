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
		// Do Collision Check
	}
}
