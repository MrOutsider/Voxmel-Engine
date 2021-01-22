#include "Renderer.h"

Renderer::Renderer(GLFWwindow* win)
{
	window = win;
	init();
}

void Renderer::addEntityRenderTarget(Entity& entity)
{
	sizeOfIndi.push_back(sizeof(uint32_t) * entity.modelData.indices.size());

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
	glBufferData(GL_ARRAY_BUFFER, entity.modelData.vertices.size() * sizeof(float), &entity.modelData.vertices.front(), GL_STATIC_DRAW);

	// Copy indices array into an Element Array Buffer Object for OpenGL to reuse verts from the VBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs.back());
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, entity.modelData.indices.size() * sizeof(uint32_t), &entity.modelData.indices.front(), GL_STATIC_DRAW);

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

	if (entity.modelData.texture.albedo != "NULL")
	{
		loadTexture(entity.modelData.texture.albedo, albedoTextures);
		loadTexture("res/textures/awesomeface.png", roughnessTextures);
	}
	else
	{
		loadTexture("res/textures/default.png", albedoTextures);
		loadTexture("res/textures/default.png", roughnessTextures);
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

void Renderer::loadTexture(const char* textureName, std::vector<uint32_t>& texVec)
{
	// Texture load and binding
	uint32_t newTexture;

	texVec.push_back(newTexture);

	glGenTextures(1, &texVec.back());
	glBindTexture(GL_TEXTURE_2D, texVec.back());
	// Wraping
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//Mipmap
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int textureWidth, textureHeight, texture_nrChannels;
	stbi_set_flip_vertically_on_load(true);

	if (texVec == albedoTextures)
	{
		unsigned char* textureData = stbi_load(textureName, &textureWidth, &textureHeight, &texture_nrChannels, 0);

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
	else if (texVec == roughnessTextures)
	{
		unsigned char* textureData = stbi_load(textureName, &textureWidth, &textureHeight, &texture_nrChannels, 0);

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

	if (!VAOs.empty())	// Only render models when there is at least one VAO in queue
	{
		for (size_t i = 0; i < VAOs.size(); i++)
		{
			shaders[0].use();
			if (!albedoTextures.empty())
			{
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, albedoTextures[i]);
				glActiveTexture(GL_TEXTURE1);
				glBindTexture(GL_TEXTURE_2D, roughnessTextures[i]);
				shaders[0].setInt("albedoTexture", 0);
				shaders[0].setInt("roughnessTexture", 1);
			}
			glBindVertexArray(VAOs[i]);
			glDrawElements(GL_TRIANGLES, sizeOfIndi[i], GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
		}
	}

	glfwSwapBuffers(window);
}

void Renderer::destroy()
{
	if (!shaders.empty())
	{
		for (size_t i = 0; i < shaders.size(); i++)
		{
			shaders[i].destroy();
		}
		std::cout << "Shaders destroyed\n";
	}

	if (!VAOs.empty())
	{
		for (size_t i = 0; i < VAOs.size(); i++)
		{
			glDeleteVertexArrays(1, &VAOs[i]);
		}
		std::cout << "VAOs destroyed\n";
	}

	if (!VBOs.empty())
	{
		for (size_t i = 0; i < VBOs.size(); i++)
		{
			glDeleteVertexArrays(1, &VBOs[i]);
		}
		std::cout << "VBOs destroyed\n";
	}

	if (!EBOs.empty())
	{
		for (size_t i = 0; i < EBOs.size(); i++)
		{
			glDeleteVertexArrays(1, &EBOs[i]);
		}
		std::cout << "EBOs destroyed\n";
	}

	if (!albedoTextures.empty())
	{
		for (size_t i = 0; i < albedoTextures.size(); i++)
		{
			glDeleteTextures(1, &albedoTextures[i]);
		}
		std::cout << "Albedo textures destroyed\n";
	}

	if (!roughnessTextures.empty())
	{
		for (size_t i = 0; i < roughnessTextures.size(); i++)
		{
			glDeleteTextures(1, &roughnessTextures[i]);
		}
		std::cout << "Roughness textures destroyed\n";
	}
}

