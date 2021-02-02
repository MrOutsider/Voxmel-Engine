#include "Renderer.h"

Renderer::Renderer(GLFWwindow* win, float* mouseScroll)
{
	window = win;
	mouseS = mouseScroll;
	init();
}

void Renderer::addEntityRenderTarget(Entity& e)
{
	RenderTarget newEntity;
	EntityList.push_back(newEntity);

	EntityList.back().entity = &e;

	EntityList.back().vertsSize = e.modelData.vertices.size() * sizeof(float);

	// Generate the IDs
	glGenVertexArrays(1, &EntityList.back().VAO);
	glGenBuffers(1, &EntityList.back().VBO);

	// Bind the VAO
	glBindVertexArray(EntityList.back().VAO);

	// Copy vertices array into a Vertex Buffer Object for OpenGL to use
	glBindBuffer(GL_ARRAY_BUFFER, EntityList.back().VBO);
	glBufferData(GL_ARRAY_BUFFER, e.modelData.vertices.size() * sizeof(float), &e.modelData.vertices.front(), GL_STATIC_DRAW);

	// Set the vertex attributes
	// Vertices
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(0 * sizeof(float)));
	glEnableVertexAttribArray(0);
	// Normals
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// UVs
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	if (e.modelData.texture.albedoPath != "NULL")
	{
		loadTexture(e.modelData.texture.albedoPath, EntityList.back().albedoTexture, true);
	}
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
	MeshLoader loader();
}

void Renderer::loadTexture(const char* textureName, GLuint& target, bool transparent)
{
	// Texture load and binding
	glGenTextures(1, &target);
	glBindTexture(GL_TEXTURE_2D, target);
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

	//glBindVertexArray(VAO);
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

	for (size_t i = 0; i < EntityList.size(); i++)
	{
		glDeleteVertexArrays(1, &EntityList[i].VAO);
		glDeleteVertexArrays(1, &EntityList[i].VBO);
		glDeleteTextures(1, &EntityList[i].albedoTexture);
		glDeleteTextures(1, &EntityList[i].secondTexturePath);
	}
}

