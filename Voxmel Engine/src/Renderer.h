#ifndef RENDERER_H
#define RENDERER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>

#include <vector>

#include "Shader.h"

class Renderer
{
public:
	void init(GLFWwindow* win);
	void render();
	void destroy();
private:
	GLFWwindow* window;

	std::vector<Shader> shaders;

	void compileShaders();
	void loadTextures();
	void loadModels();
};

#endif // !RENDERER_H

