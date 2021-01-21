#ifndef RENDERER_H
#define RENDERER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>

#include <iostream>
#include <vector>

#include "Shader.h"
#include "Entity.h"

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
	std::vector<uint32_t> VAOs;
	std::vector<uint32_t> VBOs;
	std::vector<uint32_t> EBOs;
	std::vector<uint32_t> sizeOfIndi;
	std::vector<uint32_t> albedoTextures;
	std::vector<uint32_t> roughnessTextures;

	void init();
	void compileShaders();
	void loadModel();
	void loadTexture(const char* textureName, std::vector<uint32_t>& texVec);
};

#endif // !RENDERER_H

