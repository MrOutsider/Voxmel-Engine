#include "Renderer.h"

Renderer::Renderer(GLFWwindow* win, float* mouseScroll, ChunkManager& ChunkManager)
{
	window = win;
	mouseS = mouseScroll;
	CM = &ChunkManager;
	init();
}

void Renderer::addCamera(Camera& cam)
{
	camera = &cam;
}

void Renderer::addEntity(Entity& entity)
{
	models.push_back(&entity);
}

void Renderer::removeEntity(Entity& entity)
{
	for (unsigned int i = 0; i < models.size(); i++)
	{
		if (models[i]->ID == entity.ID)
		{
			models.erase(models.begin() + i);
		}
	}
}

void Renderer::loadEntityBuffers(Entity& entity)
{
	loadModel(entity);
	loadTexture(entity.albedoPath, entity.albedo);
}

void Renderer::eraseEntityBuffers(Entity& entity)
{
	glDeleteVertexArrays(1, &entity.VAO);
	glDeleteVertexArrays(1, &entity.VBO);
	glDeleteVertexArrays(1, &entity.EBO);
	glDeleteTextures(1, &entity.albedo);
	entity.indices.clear();
}

void Renderer::init()
{
	compileShaders();
	loadTexture("res/textures/block_atlas.png", chunkAlbedo);
}

void Renderer::compileShaders()
{
	// 0
	Shader voxelShader;
	shaders.push_back(voxelShader);
	shaders.back().create("res/shaders/voxel.vs", "res/shaders/voxel.fs");

	// 1
	Shader entityShader;
	shaders.push_back(entityShader);
	shaders.back().create("res/shaders/entity.vs", "res/shaders/entity.fs");
}

void Renderer::loadModel(Entity& entity)
{
	MeshLoader meshData;
	meshData.loadMesh(entity.modelPath);
	meshData.OpenGLBufferLoading(entity.VAO, entity.VBO, entity.EBO, entity.indices);
}

void Renderer::loadTexture(const char* textureName, GLuint& texture)
{
	// Texture load and binding
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	// Wraping
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//Mipmap
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	int textureWidth, textureHeight, texture_nrChannels;
	stbi_set_flip_vertically_on_load(true);

	unsigned char* textureData = stbi_load(textureName, &textureWidth, &textureHeight, &texture_nrChannels, 0);

	if (textureData)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureWidth, textureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData);
		//glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(textureData);
}

void Renderer::render()
{
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glDisable(GL_CULL_FACE);//TMP

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	drawCalls = 0;

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
	projection = glm::perspective(glm::radians(fov), (float)width / (float)height, 0.1f, 1000.0f);

	glm::mat4 model = glm::mat4(1.0f);

	//-------------------------------------------------------
	// Test
	for (unsigned int i = 0; i < CM->loadedChunks.size(); i++)
	{
		shaders[0].use();

		//std::cout << CM.loadedChunks[i]->x << " | " << CM.loadedChunks[i]->z << std::endl;

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(CM->loadedChunks[i]->x * CM->loadedChunks[i]->chunkSize, 0.0f, 0.0f));
		model = glm::translate(model, glm::vec3(0.0f, CM->loadedChunks[i]->y * CM->loadedChunks[i]->chunkSize, 0.0f));
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -CM->loadedChunks[i]->z * CM->loadedChunks[i]->chunkSize - ((float)i + 1.0f)));
		
		glm::mat4 MVP = projection * view * model;

		shaders[0].setMat4("MVP", MVP);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, chunkAlbedo);
		shaders[0].setInt("albedo", 0);

		glBindVertexArray(CM->loadedChunks[i]->VAO);
		glDrawArrays(GL_TRIANGLES, 0, CM->loadedChunks[i]->verticiesAmount);
		glBindVertexArray(0);
		drawCalls++;
	}
	//-------------------------------------------------------

	// Rendering entities
	for (unsigned i = 0; i < models.size(); i++)
	{
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));

		// Translate
		if (models[i]->transform != glm::vec3(0.0f))
		{
			model = glm::translate(model, models[i]->transform);
		}
		// Rotate
		if (models[i]->rotation.x != 0.0f)
		{
			model = glm::rotate(model, models[i]->rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
		}
		if (models[i]->rotation.y != 0.0f)
		{
			model = glm::rotate(model, models[i]->rotation.x, glm::vec3(0.0f, 1.0f, 0.0f));
		}
		if (models[i]->rotation.z != 0.0f)
		{
			model = glm::rotate(model, models[i]->rotation.x, glm::vec3(1.0f, 0.0f, 1.0f));
		}
		// Scale
		if (models[i]->scale != glm::vec3(1.0f))
		{
			model = glm::scale(model, models[i]->scale);
		}

		glm::mat4 MVP = projection * view * model;

		shaders[1].use();

		shaders[1].setMat4("MVP", MVP);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, models[i]->albedo);
		shaders[1].setInt("albedo", 0);

		glBindVertexArray(models[i]->VAO);
		glDrawElements(GL_TRIANGLES, models[i]->indices.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		drawCalls++;
	}
	glfwSwapBuffers(window);
}

void Renderer::destroy()
{
	for (unsigned int i = 0; i < shaders.size(); i++)
	{
		shaders[i].destroy();
	}

	for (unsigned int i = 0; i < models.size(); i++)
	{
		glDeleteVertexArrays(1, &models[i]->VAO);
		glDeleteVertexArrays(1, &models[i]->VBO);
		glDeleteVertexArrays(1, &models[i]->EBO);
		glDeleteTextures(1, &models[i]->albedo);
	}

	shaders.clear();
	models.clear();
}