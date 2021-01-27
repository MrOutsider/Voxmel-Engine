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

	EntityList.back().indicesSize = e.modelData.indices.size() * sizeof(uint32_t);

	// Generate the IDs
	glGenVertexArrays(1, &EntityList.back().VAO);
	glGenBuffers(1, &EntityList.back().VBO);
	glGenBuffers(1, &EntityList.back().EBO);

	// Bind the VAO
	glBindVertexArray(EntityList.back().VAO);

	// Copy vertices array into a Vertex Buffer Object for OpenGL to use
	glBindBuffer(GL_ARRAY_BUFFER, EntityList.back().VBO);
	glBufferData(GL_ARRAY_BUFFER, e.modelData.vertices.size() * sizeof(float), &e.modelData.vertices.front(), GL_STATIC_DRAW);

	// Copy indices array into an Element Array Buffer Object for OpenGL to reuse verts from the VBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EntityList.back().EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, e.modelData.indices.size() * sizeof(uint32_t), &e.modelData.indices.front(), GL_STATIC_DRAW);

	// Set the vertex attributes
	// Vertices
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(0 * sizeof(float)));
	glEnableVertexAttribArray(0);
	// UVs
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	if (e.modelData.texture.albedo != "NULL")
	{
		loadTexture(e.modelData.texture.albedo, EntityList.back().albedoTexture, false);
	}

	if (e.modelData.texture.secondTexture != "NULL")
	{
		loadTexture(e.modelData.texture.secondTexture, EntityList.back().secondTexture, true);
	}
}

void Renderer::addCamera(Camera& cam)
{
	camera = &cam;
}

void Renderer::init()
{
	compileShaders();
}

void Renderer::compileShaders()
{
	Shader newShader;
	shaders.push_back(newShader);
	shaders.back().create("res/shaders/basic.vs", "res/shaders/basic.fs");
}

void Renderer::loadModel()
{
}

void Renderer::loadTexture(const char* textureName, uint32_t& target, bool transparent)
{
	// Texture load and binding
	glGenTextures(1, &target);
	glBindTexture(GL_TEXTURE_2D, target);
	// Wraping
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//Mipmap
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

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
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureWidth, textureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData);
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
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (size_t i = 0; i < EntityList.size(); i++)
	{
		shaders[EntityList[i].shader].use();

		/*glm::mat4 model = glm::mat4(1.0f);
		if ((EntityList[i].entity->transform.x != 0) || (EntityList[i].entity->transform.y != 0) || (EntityList[i].entity->transform.z != 0))
		{
			model = glm::translate(model, EntityList[i].entity->transform);
		}
		if ((EntityList[i].entity->scale.x != 1) || (EntityList[i].entity->scale.y != 1) || (EntityList[i].entity->scale.z != 1))
		{
			model = glm::scale(model, EntityList[i].entity->scale);
		}
		if (EntityList[i].entity->rotation.x != 0)
		{
			model = glm::rotate(model, glm::radians(EntityList[i].entity->rotation.x * (float)glfwGetTime()), glm::vec3(1.0f, 0.0f, 0.0f));
		}
		if (EntityList[i].entity->rotation.y != 0)
		{
			model = glm::rotate(model, glm::radians(EntityList[i].entity->rotation.y * (float)glfwGetTime()), glm::vec3(0.0f, 1.0f, 0.0f));
		}
		if (EntityList[i].entity->rotation.z != 0)
		{
			model = glm::rotate(model, glm::radians(EntityList[i].entity->rotation.z * (float)glfwGetTime()), glm::vec3(0.0f, 0.0f, 1.0f));
		}*/

		//----------------------------------------------------------------------------
		// This is just to move the spawned cubes around
		glm::vec3 cubePositions[] = {
			glm::vec3(0.0f,  0.0f,  0.0f),
			glm::vec3(2.0f,  5.0f, -15.0f),
			glm::vec3(-1.5f, -2.2f, -2.5f),
			glm::vec3(-3.8f, -2.0f, -12.3f),
			glm::vec3(2.4f, -0.4f, -3.5f),
			glm::vec3(-1.7f,  3.0f, -7.5f),
			glm::vec3(1.3f, -2.0f, -2.5f),
			glm::vec3(1.5f,  2.0f, -2.5f),
			glm::vec3(1.5f,  0.2f, -1.5f),
			glm::vec3(-1.3f,  1.0f, -1.5f)
		};

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, cubePositions[i]);
		float angle = 20.0f * i * glfwGetTime();
		model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
		//----------------------------------------------------------------------------

		glm::mat4 view = glm::mat4(1.0f);

		view = glm::lookAt(camera->transform, camera->transform + camera->cameraFront, camera->cameraUp);

		const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
		float window_width = mode->width;
		float window_height = mode->height;

		glm::mat4 projection = glm::mat4(1.0f);
		fov -= *mouseS;
		if (fov < 20.0f)
			fov = 20.0f;
		if (fov > 45.0f)
			fov = 45.0f;
		projection = glm::perspective(glm::radians(fov), (float)window_width / (float)window_height, 0.1f, 100.0f);

		shaders[EntityList[i].shader].setMat4("model", model);
		shaders[EntityList[i].shader].setMat4("view", view);
		shaders[EntityList[i].shader].setMat4("projection", projection);

		if (!EntityList[i].albedoTexture == 0)
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, EntityList[i].albedoTexture);
			shaders[EntityList[i].shader].setInt("albedoTexture", 0);
		}

		if (!EntityList[i].secondTexture == 0)
		{
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, EntityList[i].secondTexture);
		shaders[EntityList[i].shader].setInt("secondTexture", 1);
		}

		glBindVertexArray(EntityList[i].VAO);
		glDrawElements(GL_TRIANGLES, EntityList[i].indicesSize, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}

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
		glDeleteVertexArrays(1, &EntityList[i].EBO);
		glDeleteTextures(1, &EntityList[i].albedoTexture);
		glDeleteTextures(1, &EntityList[i].secondTexture);
	}
}

