#ifndef PHYSICS_MANAGER
#define PHYSICS_MANAGER

#include <glm/glm.hpp>

#include <vector>
#include <iostream>

struct PhysicsObject
{
	unsigned int ID = 0;

	bool enabled = true;
	bool resting = false;
	float isIntersecting = 0.0f;

	std::vector<unsigned int> listOfIntersecting;

	glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 velocity = glm::vec3(0.0f, 0.0f, 0.0f);

	float xOffset = 0.0f;
	float yOffset = 0.0f;
	float zOffset = 0.0f;
};

struct AABB : PhysicsObject
{
	const int STATIC = 0;
	const int RIGID = 1;
	const int KINEMATIC = 2;
	const int AREA = 3;

	int typeOfBody = 0;

	float xLength = 1.0f;
	float yLength = 1.0f;
	float zLength = 1.0f;
};

struct CHUNK_AABB : AABB
{
	std::vector<AABB*> voxelBoxList;
};

class PhysicsManager
{
public:
	unsigned int nextID = 1;

	std::vector<AABB*> dynamicList;
	std::vector<CHUNK_AABB*> chunkBoxList;

	std::vector<AABB*> physicsRenderList;

	PhysicsManager();

	void addAABB(AABB& obj);
	void removeAABB(AABB& obj);

	void update(float delta);
private:
	const float GRAVITY = 9.7f;

	bool isPointInside(float x, float y, float z, AABB& box);
	bool isAABB_Intersect(AABB& a, AABB& b);
};
#endif // !PHYSICS_MANAGER

// HALP
// https://developer.mozilla.org/en-US/docs/Games/Techniques/3D_collision_detection

