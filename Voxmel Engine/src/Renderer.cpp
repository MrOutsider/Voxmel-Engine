#include "Renderer.h"

Renderer::Renderer(GLFWwindow* win)
{
	window = win;
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

	// Set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

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
	glClear(GL_COLOR_BUFFER_BIT);

	for (size_t i = 0; i < EntityList.size(); i++)
	{
		shaders[EntityList[i].shader].use();

		glm::mat4 localTransform = glm::mat4(1.0f);
		localTransform = glm::translate(localTransform, EntityList[i].entity->transform);
		localTransform = glm::scale(localTransform, EntityList[i].entity->scale);
		localTransform = glm::rotate(localTransform, glm::radians(EntityList[i].entity->rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
		localTransform = glm::rotate(localTransform, glm::radians(EntityList[i].entity->rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
		localTransform = glm::rotate(localTransform, glm::radians(EntityList[i].entity->rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

		uint32_t transformLoc = glGetUniformLocation(shaders[EntityList[i].shader].getID(), "localTransform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(localTransform));

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

