#include "Renderer.h"

Renderer::Renderer(GLFWwindow* win, float* mouseScroll)
{
	window = win;
	mouseS = mouseScroll;
	init();
	loadModel();
}

void Renderer::addCamera(Camera& cam)
{
	camera = &cam;
}

void Renderer::init()
{
	compileShaders();
	glEnable(GL_DEPTH_TEST);
}

void Renderer::compileShaders()
{
	Shader entityShader;
	shaders.push_back(entityShader);
	shaders.back().create("res/textures/entity.vs", "res/textures/entity.fs");
}

void Renderer::loadModel()
{
	// TODO : VAO, VBO, EBO, and Texture GLuints
	MeshLoader meshData;
	meshData.setupMesh(VAO, VBO, EBO);
	loadTexture("res/textures/container2.png", albedo, true);
}

void Renderer::loadTexture(const char* textureName, GLuint& texture, bool transparent)
{
	// Texture load and binding
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	// Wraping
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//Mipmap
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	int textureWidth, textureHeight, texture_nrChannels;
	stbi_set_flip_vertically_on_load(true);

	unsigned char* textureData = stbi_load(textureName, &textureWidth, &textureHeight, &texture_nrChannels, 0);

	if (!transparent)
	{
		if (textureData)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureWidth, textureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			std::cout << "Failed to load texture" << std::endl;
		}
		stbi_image_free(textureData);
	}
	else
	{
		if (textureData)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureWidth, textureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			std::cout << "Failed to load texture" << std::endl;
		}
		stbi_image_free(textureData);
	}
}

void Renderer::render()
{
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::mat4 view = glm::mat4(1.0f);

	view = glm::lookAt(camera->transform, camera->transform + camera->cameraFront, camera->cameraUp);

	int width, height;
	glfwGetWindowSize(window, &width, &height);

	glm::mat4 projection = glm::mat4(1.0f);
	fov -= *mouseS;
	if (fov < 20.0f)
		fov = 20.0f;
	if (fov > 45.0f)
		fov = 45.0f;
	projection = glm::perspective(glm::radians(fov), (float)width / (float)height, 0.1f, 100.0f);

	glm::mat4 model = glm::mat4(1.0f);

	glm::mat4 MVP = projection * view * model;

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, numOfVerticies, GL_UNSIGNED_INT, &EBO);
	//glDrawArrays(GL_TRIANGLES, 0, vertSize);
	//glBindVertexArray(0);

	glfwSwapBuffers(window);
}

void Renderer::destroy()
{
	for (size_t i = 0; i < shaders.size(); i++)
	{
		shaders[i].destroy();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteVertexArrays(1, &VBO);
	glDeleteVertexArrays(1, &EBO);
	glDeleteTextures(1, &albedo);
}

