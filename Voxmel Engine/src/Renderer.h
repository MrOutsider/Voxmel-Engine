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

struct RenderTarget
{
	Entity* entity;
	
	GLuint ID; // ID assosiated with imported entity
	GLuint shader = 0;

	GLuint vertsSize;

	GLuint VAO;
	GLuint VBO;

	GLuint albedoTexture = 0;
	GLuint secondTexturePath = 0;
};

struct Light
{
	glm::vec3 position;
	glm::vec3 color;
};

class Renderer
{
public:
	Renderer(GLFWwindow* win, float* mouseScroll);
	void addCamera(Camera& cam);
	void addEntityRenderTarget(Entity& entity);
	void render();
	void destroy();
private:
	GLFWwindow* window;
	Camera* camera;
	float* mouseS;

	std::vector<Shader> shaders;
	std::vector<RenderTarget> EntityList;

	const float FOV = 45.0f;
	float fov = FOV;

	void init();
	void compileShaders();
	void loadModel();
	void loadTexture(const char* textureName, GLuint& target, bool transparent);
};

#endif // !RENDERER_H

