#ifndef RENDERER_H
#define RENDERER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <string>
#include <vector>

#include "Shader.h"
#include "MeshLoader.h"
#include "Camera.h"
#include "Entity.h"

class Renderer
{
public:
	unsigned int drawCalls = 0;

	Renderer(GLFWwindow* win, float* mouseScroll);

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
	GLFWwindow* window;
	Camera* camera;
	float* mouseS;

	std::vector<Shader> shaders;
	// Voxel = 0
	// Entity = 1

	const float FOV = 45.0f;
	float fov = FOV;

	std::vector<Entity*> models;

	void init();
	void compileShaders();
	void loadModel(Entity& entity);
	void loadTexture(const char* textureName, GLuint& target, bool transparent);
};

#endif // !RENDERER_H

