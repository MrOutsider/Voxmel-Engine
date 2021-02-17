#ifndef PHYSICS_MANAGER
#define PHYSICS_MANAGER

#include <glm/glm.hpp>

#include <math.h>
#include <algorithm>
#include <vector>
#include <iostream>

struct Colors
{
	const float RED		= 1.0f;
	const float GREEN	= 2.0f;
	const float BLUE	= 3.0f;
};

struct PhysicsObject
{
	unsigned int ID = 0;

	bool enabled = true;
	bool visable = true;
	bool resting = false;

	float color = 0.0f;

	glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 velocity = glm::vec3(0.0f, 0.0f, 0.0f);

	float xOffset = 0.0f;
	float yOffset = 0.0f;
	float zOffset = 0.0f;
};

struct AABB : PhysicsObject
{
	const int VOXEL = 1;
	const int CHUNK = 2;

	int typeOfContainer = -1;

	const int STATIC = 0;
	const int RIGID = 1;
	const int KINEMATIC = 2;
	const int AREA = 3;

	int typeOfBody = 0;

	float xLength = 1.0f;
	float yLength = 1.0f;
	float zLength = 1.0f;

	int voxelID = -1;
};

struct CHUNK_AABB : AABB
{
	int chunkX = 0;
	int chunkY = 0;
	int chunkZ = 0;

	std::vector<AABB*> voxelBoxList;
};

struct Raycast
{
	unsigned int ID = 0;

	bool enabled = true;
	bool visable = true;

	glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 Direction = glm::vec3(0.0f, 0.0f, 0.0f);
	int length = 0;

	float color = 0.0f;

	glm::vec3 collisionPosition = glm::vec3(0.0f);
	AABB* closestVoxel = nullptr;
	CHUNK_AABB* closestVoxelsChunk = nullptr;
	AABB* closestDynamic = nullptr;
};

class PhysicsManager
{
public:
	Colors Colors;

	std::vector<AABB*> AABB_RenderList;
	std::vector<Raycast*> raycastRenderList;

	PhysicsManager();

	unsigned int assignID();

	void addChunk_AABB(CHUNK_AABB& chunk);
	void removeDynamic_AABB(CHUNK_AABB& chunk);

	void addDynamic_AABB(AABB& aabb);
	void removeDynamic_AABB(AABB& aabb);

	void addRaycast(Raycast& ray);
	void removeRaycast(Raycast& ray);

	void update(float delta);
private:
	const float GRAVITY = 9.7f;

	unsigned int nextID = 1;

	std::vector<CHUNK_AABB*> chunkBoxList;
	std::vector<AABB*> dynamicList;
	std::vector<Raycast*> raycastList;

	bool isPointAABB(float x, float y, float z, AABB* box);
	bool isAABB_AABB(AABB* a, AABB* b);
	float isRayAABB(Raycast* ray, AABB* aabb);

	float distBetweenPoints(glm::vec3& positionOne, glm::vec3& positionTwo);

	CHUNK_AABB* findVoxelsChunk(AABB* voxel);
};
#endif // !PHYSICS_MANAGER

// HALP
// https://developer.mozilla.org/en-US/docs/Games/Techniques/3D_collision_detection -> Point, Sphere, AABB
// https://gdbooks.gitbooks.io/3dcollisions/content/Chapter3/raycast_aabb.html -> Ray
// [LINK] -> OOB

