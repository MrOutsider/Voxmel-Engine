#ifndef PHYSICS_MANAGER
#define PHYSICS_MANAGER

#include <glm/glm.hpp>

#include <vector>

struct PhysicsObject
{
	glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 velocity = glm::vec3(0.0f, 0.0f, 0.0f);
};

struct AABB : PhysicsObject
{
	float isIntersecting = 0.0f;

	float xlength = 1.0f;
	float ylength = 1.0f;
	float zlength = 1.0f;

	float xOffset = 0.0f;
	float yOffset = 0.0f;
	float zOffset = 0.0f;
};

class PhysicsManager
{
public:
	std::vector<AABB*> aabbList;

	PhysicsManager();

	void addAABB(AABB& obj);

	void update(float delta);
private:
	
};
#endif // !PHYSICS_MANAGER

// HALP
// https://developer.mozilla.org/en-US/docs/Games/Techniques/3D_collision_detection

