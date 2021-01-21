#ifndef RENDERER_H
#define RENDERER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>

#include <vector>

#include "Shader.h"
#include "Entity.h"

class Renderer
{
public:
	Renderer(GLFWwindow* win);
	void addObj(Entity& entity);
	void render();
	void destroy();
private:
	GLFWwindow* window;

	std::vector<Shader> shaders;
	std::vector<uint32_t> VAOs;
	std::vector<uint32_t> sizeOfIndi;
	std::vector<uint32_t> textures;

	void init();
	void compileShaders();
	void loadTextures();
	void loadModels();
};

#endif // !RENDERER_H

