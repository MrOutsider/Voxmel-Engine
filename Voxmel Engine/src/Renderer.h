#ifndef RENDERER_H
#define RENDERER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Shader.h"
#include "MeshLoader.h"
#include "Camera.h"
#include "PhysicsManager.h"
#include "Entity.h"

#include "ChunkManager.h"

#include <string>
#include <vector>

class Renderer
{
public:
	unsigned int drawCalls = 0;

	Renderer(GLFWwindow* win, float* mouseScroll, ChunkManager& ChunkManager, /*TMP*/ PhysicsManager& pm);

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

	std::vector<Entity*> models;

	ChunkManager* CM;
	GLuint chunkAlbedo;

	PhysicsManager* physicsManager;

	void init();
	void compileShaders();
	void loadModel(Entity& entity);
	void loadTexture(const char* textureName, GLuint& target);

	//---------------------------------
	// DEBUG
	bool renderPhysics = true;
	GLuint PhysicsVAO;
	GLuint PhysicsVBO;
	void drawBox(std::vector<float>& listOfLines, AABB& box);
	//---------------------------------
};

#endif // !RENDERER_H

