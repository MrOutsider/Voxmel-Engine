#ifndef RENDERER_H
#define RENDERER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <vector>

#include "Shader.h"
#include "Entity.h"

struct RenderTarget
{
	Entity* entity;

	uint32_t ID; // ID assosiated with imported entity
	uint32_t shader = 0;

	uint32_t indicesSize;

	uint32_t VAO;
	uint32_t VBO;
	uint32_t EBO;

	uint32_t albedoTexture = 0;
	uint32_t secondTexture = 0;
};

class Renderer
{
public:
	Renderer(GLFWwindow* win);
	void addEntityRenderTarget(Entity& entity);
	void render();
	void destroy();
private:
	GLFWwindow* window;

	std::vector<Shader> shaders;
	std::vector<RenderTarget> EntityList;

	void init();
	void compileShaders();
	void loadModel();
	void loadTexture(const char* textureName, uint32_t& target, bool transparent);
};

#endif // !RENDERER_H

