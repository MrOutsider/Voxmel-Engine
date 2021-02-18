#ifndef MANAGERS_H
#define MANAGERS_H

#include "WindowManager.h"
#include "RenderManager.h"
#include "PhysicsManager.h"
#include "ChunkManager.h"

class Managers
{
public:
	Managers();
	~Managers();

	WindowManager* windowManager = nullptr;
	// InputManager
	RenderManager* renderManager = nullptr;
	PhysicsManager* physicsManager = nullptr;
	// UI_Manager
	// EntityManager
	ChunkManager* chunkManager = nullptr;

private:

};

Managers::Managers()
{
}

Managers::~Managers()
{
}

#endif // !MANAGERS_H

