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
	struct Light
	{
		glm::vec3 position;
		glm::vec3 color;
	};

	Renderer(GLFWwindow* win, float* mouseScroll);
	void addCamera(Camera& cam);
	void render();
	void destroy();
private:
	GLFWwindow* window;
	Camera* camera;
	float* mouseS;

	std::vector<Shader> shaders;

	const float FOV = 45.0f;
	float fov = FOV;

	//---------------------------------------------
	unsigned int numOfVerticies;
	GLuint VAO;
	GLuint VBO;
	GLuint EBO;
	GLuint albedo;
	//---------------------------------------------

	void init();
	void compileShaders();
	void loadModel();
	void loadTexture(const char* textureName, GLuint& target, bool transparent);
};

#endif // !RENDERER_H

