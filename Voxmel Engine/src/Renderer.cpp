#include "Renderer.h"

Renderer::Renderer(GLFWwindow* win, float* mouseScroll)
{
	window = win;
	mouseS = mouseScroll;
	init();
}

void Renderer::addCamera(Camera& cam)
{
	camera = &cam;
}

void Renderer::loadEntityData(Entity& entity)
{
	loadModel(entity.modelPath, entity.albedoPath, entity);
}

void Renderer::removeEntity(Entity& entity)
{
	for (unsigned int i = 0; i < renderList.size(); i++)
	{
		if (renderList[i]->ID == entity.ID)
		{
			renderList.erase(renderList.begin() + i);
		}
	}

	for (unsigned int i = 0; i < models.size(); i++)
	{
		if (models[i].entity->ID == entity.ID)
		{
			for (unsigned int n = 0; n < models[i].VAOs.size(); n++)
			{
				glDeleteVertexArrays(1, &models[i].VAOs[n]);
			}

			for (unsigned int n = 0; n < models[i].VBOs.size(); n++)
			{
				glDeleteVertexArrays(1, &models[i].VBOs[n]);
			}

			for (unsigned int n = 0; n < models[i].EBOs.size(); n++)
			{
				glDeleteVertexArrays(1, &models[i].EBOs[n]);
			}

			glDeleteTextures(1, &models[i].albedo);
		}

		models.erase(models.begin() + i);
	}
}

void Renderer::addEntityToRenderList(Entity& entinty)
{
	for (unsigned int i = 0; i < models.size(); i++)
	{
		if (models[i].entity->ID == entinty.ID)
		{
			renderList.push_back(&entinty);
		}
		else
		{
			std::string IDstring = std::to_string(entinty.ID);
			std::cout << "Entity data not loaded : ID : #" + IDstring << std::endl;
		}
	}
}

void Renderer::removeEntityFromRenderList(Entity& entinty)
{
	for (unsigned int i = 0; i < renderList.size(); i++)
	{
		if (renderList[i]->ID == entinty.ID)
		{
			renderList.erase(renderList.begin() + i);
		}
	}
}

void Renderer::init()
{
	compileShaders();
	glEnable(GL_DEPTH_TEST);
}

void Renderer::compileShaders()
{
	// 0
	Shader voxelShader;
	shaders.push_back(voxelShader);
	shaders.back().create("res/shaders/entity.vs", "res/shaders/entity.fs");

	// 1
	Shader entityShader;
	shaders.push_back(entityShader);
	shaders.back().create("res/shaders/entity.vs", "res/shaders/entity.fs");
}

void Renderer::loadModel(const char* modelPath, const char* texturePath, Entity& entity)
{
	RenderTarget newTarget;
	newTarget.entity = &entity;

	MeshLoader meshData;
	meshData.loadMesh(modelPath);
	meshData.OpenGLBufferLoading(newTarget.VAOs, newTarget.VBOs, newTarget.EBOs, newTarget.indicesList);
	loadTexture(texturePath, newTarget.albedo, true);

	models.push_back(newTarget);
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

	for (unsigned int i = 0; i < renderList.size(); i++)
	{
		for (unsigned n = 0; n < models.size(); n++)
		{
			if (renderList[i]->ID == models[n].entity->ID)
			{
				for (unsigned int m = 0; m < models[n].indicesList.size(); m++)
				{
					glm::mat4 model = glm::mat4(1.0f);
					model = glm::translate(model, glm::vec3(0.0f, 0.0f, -5.0f));

					// Translate
					if (models[n].entity->transform != glm::vec3(0.0f))
					{
						model = glm::translate(model, models[n].entity->transform);
					}
					// Rotate
					if (models[n].entity->rotation.x != 0.0f)
					{
						model = glm::rotate(model, models[n].entity->rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
					}
					if (models[n].entity->rotation.y != 0.0f)
					{
						model = glm::rotate(model, models[n].entity->rotation.x, glm::vec3(0.0f, 1.0f, 0.0f));
					}
					if (models[n].entity->rotation.z != 0.0f)
					{
						model = glm::rotate(model, models[n].entity->rotation.x, glm::vec3(1.0f, 0.0f, 1.0f));
					}
					// Scale
					if (models[n].entity->scale != glm::vec3(1.0f))
					{
						model = glm::scale(model, models[n].entity->scale);
					}

					glm::mat4 MVP = projection * view * model;

					shaders[1].use();

					shaders[1].setMat4("MVP", MVP);

					glActiveTexture(GL_TEXTURE0);
					glBindTexture(GL_TEXTURE_2D, models[n].albedo);
					shaders[1].setInt("albedo", 0);

					glBindVertexArray(models[n].VAOs[m]);
					glDrawElements(GL_TRIANGLES, models[n].indicesList[m].size(), GL_UNSIGNED_INT, 0);
					glBindVertexArray(0);
				}
			}
		}
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
		for (unsigned int n = 0; n < models[i].VAOs.size(); n++)
		{
			glDeleteVertexArrays(1, &models[i].VAOs[n]);
		}

		for (unsigned int n = 0; n < models[i].VBOs.size(); n++)
		{
			glDeleteVertexArrays(1, &models[i].VBOs[n]);
		}

		for (unsigned int n = 0; n < models[i].EBOs.size(); n++)
		{
			glDeleteVertexArrays(1, &models[i].EBOs[n]);
		}

		glDeleteTextures(1, &models[i].albedo);
	}
}

