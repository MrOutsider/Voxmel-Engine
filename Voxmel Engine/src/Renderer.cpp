#include "Renderer.h"

Renderer::Renderer(GLFWwindow* win)
{
	window = win;
	init();
}

void Renderer::addObj(Entity& entity)
{
	sizeOfIndi.push_back(sizeof(uint32_t) * entity.getIndices().size());

	// Gen and asaign these var IDs
	uint32_t VAO, VBO, EBO;

	// Store the vars so they dont go out of scope and can be called later
	VAOs.push_back(VAO);
	VBOs.push_back(VBO);
	EBOs.push_back(EBO);

	// Generate the IDs
	glGenVertexArrays(1, &VAOs.back());
	glGenBuffers(1, &VBOs.back());
	glGenBuffers(1, &EBOs.back());

	// Bind the VAO
	glBindVertexArray(VAOs.back());

	// Copy vertices array into a Vertex Buffer Object for OpenGL to use
	glBindBuffer(GL_ARRAY_BUFFER, VBOs.back());
	glBufferData(GL_ARRAY_BUFFER, entity.getVertices().size() * sizeof(float), &entity.getVertices().front(), GL_STATIC_DRAW);

	// Copy indices array into an Element Array Buffer Object for OpenGL to reuse verts from the VBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs.back());
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, entity.getIndices().size() * sizeof(uint32_t), &entity.getIndices().front(), GL_STATIC_DRAW);

	// Set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Set the vertex attributes
	// Vertices
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(0 * sizeof(float)));
	glEnableVertexAttribArray(0);
	// Vertice Colors
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// UVs
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// Texture load and binding
	uint32_t newTexture;

	textures.push_back(newTexture);

	glGenTextures(1, &textures.back());
	glBindTexture(GL_TEXTURE_2D, textures.back());
	// Wraping
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//Mipmap
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int textureWidth, textureHeight, texture_nrChannels;
	unsigned char* textureData = stbi_load(entity.getTextures().back(), &textureWidth, &textureHeight, &texture_nrChannels, 0);

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

void Renderer::loadTextures()
{
}

void Renderer::loadModels()
{
}

void Renderer::render()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	if (VAOs.size() != 0)	// Only render models when there is at least one VAO in queue
	{
		shaders[0].use();
		glBindTexture(GL_TEXTURE_2D, textures.back());
		glBindVertexArray(VAOs.back());
		glDrawElements(GL_TRIANGLES, sizeOfIndi.back(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}

	glfwSwapBuffers(window);
}

void Renderer::destroy()
{
	if (shaders.size() != 0)
	{
		for (size_t i = 0; i < shaders.size(); i++)
		{
			shaders[i].destroy();
		}
	}

	if (VAOs.size() != 0)
	{
		for (size_t i = 0; i < VAOs.size(); i++)
		{
			glDeleteVertexArrays(1, &VAOs[i]);
		}
	}

	if (VBOs.size() != 0)
	{
		for (size_t i = 0; i < VBOs.size(); i++)
		{
			glDeleteVertexArrays(1, &VBOs[i]);
		}
	}

	if (EBOs.size() != 0)
	{
		for (size_t i = 0; i < EBOs.size(); i++)
		{
			glDeleteVertexArrays(1, &EBOs[i]);
		}
	}

	if (textures.size() != 1)
	{
		for (size_t i = 0; i < textures.size(); i++)
		{
			glDeleteTextures(1, &textures[i]);
		}
	}
}
