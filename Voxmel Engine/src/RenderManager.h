#ifndef RENDER_MANAGER_H
#define RENDER_MANAGER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "PhysicsManager.h"
#include "ChunkManager.h"

#include "Shader.h"
#include "MeshLoader.h"
#include "Camera.h"
#include "Entity.h"

#include <string>
#include <vector>

class RenderManager
{
public:
	unsigned int drawCalls = 0;

	RenderManager(GLFWwindow* win, float* mouseScroll, std::vector<Chunk*>& loadedChunks, std::vector<AABB*>& aabbList, std::vector<Raycast*>& raycastList);

	void addCamera(Camera& cam);

	// Render Queue
	void addEntity(Entity& entity);
	void removeEntity(Entity& entity);

	// OpenGL : Buffers
	void loadEntityBuffers(Entity& entity);
	void eraseEntityBuffers(Entity& entity);

	void render();
	void destroy();
private:
	const int PHYSICS_SHADER = 0;
	const int VOXEL_SHADER = 1;
	const int ENTITY_SHADER = 2;

	std::vector<Shader> shaders;

	GLFWwindow* window;
	Camera* camera;
	float* mouseS;

	const float FOV = 45.0f;
	float fov = FOV;

	std::vector<Entity*> models; // Temp untill EntityManager has own list

	std::vector<Chunk*>* chunksToRender;
	GLuint chunkAlbedo;

	std::vector<AABB*>* aabbRenderList;
	std::vector<Raycast*>* raycastRenderList;

	void init();
	void compileShaders();
	void loadModel(Entity& entity);
	void loadTexture(const char* textureName, GLuint& target);

	//------------------------------------------------------------------
	// DEBUG
	bool renderPhysics = true;
	GLuint PhysicsVAO;
	GLuint PhysicsVBO;
	void drawBox(std::vector<float>& listOfLines, AABB* box);
	void drawRay(std::vector<float>& listOfLines, Raycast* ray);
	//------------------------------------------------------------------
};

#endif // !RENDER_MANAGER_H

