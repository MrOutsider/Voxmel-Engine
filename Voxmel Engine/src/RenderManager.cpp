#include "RenderManager.h"

RenderManager::RenderManager(GLFWwindow* win, std::vector<Chunk*>* loadedChunks, std::vector<AABB*>* aabbList, std::vector<Raycast*>* raycastList)
{
	window = win;
	chunksToRender = loadedChunks;
	aabbRenderList = aabbList;
	raycastRenderList = raycastList;

	init();
}

void RenderManager::addCamera(Camera& cam)
{
	camera = &cam;
}

void RenderManager::addEntity(Entity& entity)
{
	models.push_back(&entity);
}

void RenderManager::removeEntity(Entity& entity)
{
	for (unsigned int i = 0; i < models.size(); i++)
	{
		if (models[i]->ID == entity.ID)
		{
			models.erase(models.begin() + i);
		}
	}
}

void RenderManager::loadEntityBuffers(Entity& entity)
{
	loadModel(entity);
	loadTexture(entity.albedoPath, entity.albedo);
}

void RenderManager::eraseEntityBuffers(Entity& entity)
{
	glDeleteVertexArrays(1, &entity.VAO);
	glDeleteVertexArrays(1, &entity.VBO);
	glDeleteVertexArrays(1, &entity.EBO);
	glDeleteTextures(1, &entity.albedo);
	entity.indices.clear();
}

void RenderManager::init()
{
	compileShaders();
	loadTexture("res/textures/block_atlas.png", chunkAlbedo);

	glGenVertexArrays(1, &PhysicsVAO);
	glGenBuffers(1, &PhysicsVBO);

	//-------------------------------------

	glGenFramebuffers(1, &framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

	// generate texture
	glGenTextures(1, &texColorBuffer);
	glBindTexture(GL_TEXTURE_2D, texColorBuffer);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, framebufferWidth, framebufferHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, 0);

	// attach it to currently bound framebuffer object
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texColorBuffer, 0);

	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, framebufferWidth, framebufferHeight);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);

	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
	}

	float quadMesh [] = {
		-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
		 1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
		-1.0f,  1.0f, 0.0f, 0.0f, 1.0f,

		-1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
		 1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
		 1.0f,  1.0f, 0.0f, 1.0f, 1.0f
	};

	glGenVertexArrays(1, &quadVAO);
	glGenBuffers(1, &quadVBO);

	glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadMesh), quadMesh, GL_DYNAMIC_DRAW);

	glBindVertexArray(quadVAO);
	// Vertex Positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);

	//UVs
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

	glBindVertexArray(0);
}

void RenderManager::compileShaders()
{
	// 0
	Shader screenShader;
	shaders.push_back(screenShader);
	shaders.back().create("res/shaders/framebuffer.vs", "res/shaders/framebuffer.fs");

	// 1
	Shader physicsShader;
	shaders.push_back(physicsShader);
	shaders.back().create("res/shaders/physics.vs", "res/shaders/physics.fs");

	// 2
	Shader voxelShader;
	shaders.push_back(voxelShader);
	shaders.back().create("res/shaders/voxel.vs", "res/shaders/voxel.fs");

	// 3
	Shader entityShader;
	shaders.push_back(entityShader);
	shaders.back().create("res/shaders/entity.vs", "res/shaders/entity.fs");
}

void RenderManager::loadModel(Entity& entity)
{
	MeshLoader meshData;
	meshData.loadMesh(entity.modelPath);
	meshData.OpenGLBufferLoading(entity.VAO, entity.VBO, entity.EBO, entity.indices);
}

void RenderManager::loadTexture(const char* textureName, GLuint& texture)
{
	// Texture load and binding
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	// Wraping
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//Mipmap
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	int textureWidth, textureHeight, texture_nrChannels;
	stbi_set_flip_vertically_on_load(true);

	unsigned char* textureData = stbi_load(textureName, &textureWidth, &textureHeight, &texture_nrChannels, 0);

	if (textureData)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureWidth, textureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData);
		glGenerateMipmap(GL_TEXTURE_2D);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LOD, 4);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(textureData);
}

void RenderManager::render()
{
	int windowWidth, windowHeight;
	glfwGetWindowSize(window, &windowWidth, &windowHeight);

	glViewport(0, 0, framebufferWidth, framebufferHeight);

	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	//glDisable(GL_CULL_FACE);//TMP

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	drawCalls = 0;

	glm::mat4 view = glm::mat4(1.0f);

	view = glm::lookAt(camera->position, camera->position + camera->cameraFront, camera->cameraUp);

	int width, height;
	glfwGetWindowSize(window, &width, &height);

	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::perspective(glm::radians(camera->fov), (float)width / (float)height, 0.01f, 1000.0f);

	glm::mat4 model = glm::mat4(1.0f);

	// Rendering Voxels
	for (unsigned int i = 0; i < chunksToRender[0].size(); i++)
	{
		shaders[VOXEL_SHADER].use();

		// Translate the chunk to a vec3 pos * sizeOf Chunk rows
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(chunksToRender[0][i]->x * chunksToRender[0][i]->chunkSize * chunksToRender[0][i]->voxelSizeHalf * 2, 0.0f, 0.0f));
		model = glm::translate(model, glm::vec3(0.0f, chunksToRender[0][i]->y * chunksToRender[0][i]->chunkSize * chunksToRender[0][i]->voxelSizeHalf * 2, 0.0f));
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, chunksToRender[0][i]->z * chunksToRender[0][i]->chunkSize * chunksToRender[0][i]->voxelSizeHalf * 2));
		
		glm::mat4 MVP = projection * view * model;

		shaders[VOXEL_SHADER].setMat4("MVP", MVP);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, chunkAlbedo);
		shaders[VOXEL_SHADER].setInt("albedo", 0);

		glBindVertexArray(chunksToRender[0][i]->VAO);
		glDrawArrays(GL_TRIANGLES, 0, chunksToRender[0][i]->verticiesAmount);
		glBindVertexArray(0);
		drawCalls++;
	}

	// Rendering entities
	for (unsigned i = 0; i < models.size(); i++)
	{
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));

		// Translate
		if (models[i]->collisionBox.position != glm::vec3(0.0f))
		{
			model = glm::translate(model, models[i]->collisionBox.position);
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

		shaders[ENTITY_SHADER].use();

		shaders[ENTITY_SHADER].setMat4("MVP", MVP);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, models[i]->albedo);
		shaders[ENTITY_SHADER].setInt("albedo", 0);

		glBindVertexArray(models[i]->VAO);
		glDrawElements(GL_TRIANGLES, models[i]->indices.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		drawCalls++;
	}

	// Rendering physics

	if (renderPhysics)
	{
		std::vector<float> listOfLines;

		for (unsigned int i = 0; i < aabbRenderList[0].size(); i++)
		{
			drawBox(listOfLines, aabbRenderList[0][i]);
		}

		for (unsigned int i = 0; i < raycastRenderList[0].size(); i++)
		{
			drawRay(listOfLines, raycastRenderList[0][i]);
		}

		if (!listOfLines.empty())
		{
			glBindBuffer(GL_ARRAY_BUFFER, PhysicsVBO);
			glBufferData(GL_ARRAY_BUFFER, listOfLines.size() * sizeof(float), &listOfLines[0], GL_DYNAMIC_DRAW);

			glBindVertexArray(PhysicsVAO);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(3 * sizeof(float)));


			//glDisable(GL_DEPTH_TEST);
			shaders[PHYSICS_SHADER].use();

			model = glm::mat4(1.0f);
			glm::mat4 MVP = projection * view * model;

			shaders[PHYSICS_SHADER].setMat4("MVP", MVP);
			glDrawArrays(GL_LINES, 0, listOfLines.size());
			glBindVertexArray(0);
			glIsEnabled(GL_DEPTH_TEST);
			drawCalls++;
		}
	}

	glViewport(0, 0, windowWidth, windowHeight);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glDisable(GL_DEPTH_TEST);
	shaders[SCREEN_SHADER].use();
	glBindVertexArray(quadVAO);
	glBindTexture(GL_TEXTURE_2D, texColorBuffer);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
	glEnable(GL_DEPTH_TEST);
	drawCalls++;

	glfwSwapBuffers(window);
}

void RenderManager::destroy()
{
	for (unsigned int i = 0; i < shaders.size(); i++)
	{
		shaders[i].destroy();
	}

	for (unsigned int i = 0; i < models.size(); i++)
	{
		glDeleteVertexArrays(1, &models[i]->VAO);
		glDeleteBuffers(1, &models[i]->VBO);
		glDeleteBuffers(1, &models[i]->EBO);
		glDeleteTextures(1, &models[i]->albedo);
	}

	glDeleteVertexArrays(1, &PhysicsVAO);
	glDeleteBuffers(1, &PhysicsVBO);

	shaders.clear();
	models.clear();
}

void RenderManager::drawBox(std::vector<float>& listOfLines, AABB* box)
{
	if (box->visable)
	{
		// Z
		listOfLines.push_back(box->position.x - box->xLength * 0.5f + box->xOffset);
		listOfLines.push_back(box->position.y - box->yLength * 0.5f + box->yOffset);
		listOfLines.push_back(box->position.z + box->zLength * 0.5f + box->zOffset);
		listOfLines.push_back(box->color);

		listOfLines.push_back(box->position.x + box->xLength * 0.5f + box->xOffset);
		listOfLines.push_back(box->position.y - box->yLength * 0.5f + box->yOffset);
		listOfLines.push_back(box->position.z + box->zLength * 0.5f + box->zOffset);
		listOfLines.push_back(box->color);

		listOfLines.push_back(box->position.x - box->xLength * 0.5f + box->xOffset);
		listOfLines.push_back(box->position.y + box->yLength * 0.5f + box->yOffset);
		listOfLines.push_back(box->position.z + box->zLength * 0.5f + box->zOffset);
		listOfLines.push_back(box->color);	

		listOfLines.push_back(box->position.x + box->xLength * 0.5f + box->xOffset);
		listOfLines.push_back(box->position.y + box->yLength * 0.5f + box->yOffset);
		listOfLines.push_back(box->position.z + box->zLength * 0.5f + box->zOffset);
		listOfLines.push_back(box->color);

		listOfLines.push_back(box->position.x - box->xLength * 0.5f + box->xOffset);
		listOfLines.push_back(box->position.y - box->yLength * 0.5f + box->yOffset);
		listOfLines.push_back(box->position.z - box->zLength * 0.5f + box->zOffset);
		listOfLines.push_back(box->color);

		listOfLines.push_back(box->position.x + box->xLength * 0.5f + box->xOffset);
		listOfLines.push_back(box->position.y - box->yLength * 0.5f + box->yOffset);
		listOfLines.push_back(box->position.z - box->zLength * 0.5f + box->zOffset);
		listOfLines.push_back(box->color);

		listOfLines.push_back(box->position.x - box->xLength * 0.5f + box->xOffset);
		listOfLines.push_back(box->position.y + box->yLength * 0.5f + box->yOffset);
		listOfLines.push_back(box->position.z - box->zLength * 0.5f + box->zOffset);
		listOfLines.push_back(box->color);

		listOfLines.push_back(box->position.x + box->xLength * 0.5f + box->xOffset);
		listOfLines.push_back(box->position.y + box->yLength * 0.5f + box->yOffset);
		listOfLines.push_back(box->position.z - box->zLength * 0.5f + box->zOffset);
		listOfLines.push_back(box->color);

		// X
		listOfLines.push_back(box->position.x + box->xLength * 0.5f + box->xOffset);
		listOfLines.push_back(box->position.y - box->yLength * 0.5f + box->yOffset);
		listOfLines.push_back(box->position.z - box->zLength * 0.5f + box->zOffset);
		listOfLines.push_back(box->color);

		listOfLines.push_back(box->position.x + box->xLength * 0.5f + box->xOffset);
		listOfLines.push_back(box->position.y - box->yLength * 0.5f + box->yOffset);
		listOfLines.push_back(box->position.z + box->zLength * 0.5f + box->zOffset);
		listOfLines.push_back(box->color);

		listOfLines.push_back(box->position.x + box->xLength * 0.5f + box->xOffset);
		listOfLines.push_back(box->position.y + box->yLength * 0.5f + box->yOffset);
		listOfLines.push_back(box->position.z - box->zLength * 0.5f + box->zOffset);
		listOfLines.push_back(box->color);

		listOfLines.push_back(box->position.x + box->xLength * 0.5f + box->xOffset);
		listOfLines.push_back(box->position.y + box->yLength * 0.5f + box->yOffset);
		listOfLines.push_back(box->position.z + box->zLength * 0.5f + box->zOffset);
		listOfLines.push_back(box->color);

		listOfLines.push_back(box->position.x - box->xLength * 0.5f + box->xOffset);
		listOfLines.push_back(box->position.y - box->yLength * 0.5f + box->yOffset);
		listOfLines.push_back(box->position.z - box->zLength * 0.5f + box->zOffset);
		listOfLines.push_back(box->color);

		listOfLines.push_back(box->position.x - box->xLength * 0.5f + box->xOffset);
		listOfLines.push_back(box->position.y - box->yLength * 0.5f + box->yOffset);
		listOfLines.push_back(box->position.z + box->zLength * 0.5f + box->zOffset);
		listOfLines.push_back(box->color);

		listOfLines.push_back(box->position.x - box->xLength * 0.5f + box->xOffset);
		listOfLines.push_back(box->position.y + box->yLength * 0.5f + box->yOffset);
		listOfLines.push_back(box->position.z - box->zLength * 0.5f + box->zOffset);
		listOfLines.push_back(box->color);

		listOfLines.push_back(box->position.x - box->xLength * 0.5f + box->xOffset);
		listOfLines.push_back(box->position.y + box->yLength * 0.5f + box->yOffset);
		listOfLines.push_back(box->position.z + box->zLength * 0.5f + box->zOffset);
		listOfLines.push_back(box->color);

		// Y
		listOfLines.push_back(box->position.x - box->xLength * 0.5f + box->xOffset);
		listOfLines.push_back(box->position.y + box->yLength * 0.5f + box->yOffset);
		listOfLines.push_back(box->position.z - box->zLength * 0.5f + box->zOffset);
		listOfLines.push_back(box->color);

		listOfLines.push_back(box->position.x - box->xLength * 0.5f + box->xOffset);
		listOfLines.push_back(box->position.y - box->yLength * 0.5f + box->yOffset);
		listOfLines.push_back(box->position.z - box->zLength * 0.5f + box->zOffset);
		listOfLines.push_back(box->color);

		listOfLines.push_back(box->position.x + box->xLength * 0.5f + box->xOffset);
		listOfLines.push_back(box->position.y + box->yLength * 0.5f + box->yOffset);
		listOfLines.push_back(box->position.z - box->zLength * 0.5f + box->zOffset);
		listOfLines.push_back(box->color);

		listOfLines.push_back(box->position.x + box->xLength * 0.5f + box->xOffset);
		listOfLines.push_back(box->position.y - box->yLength * 0.5f + box->yOffset);
		listOfLines.push_back(box->position.z - box->zLength * 0.5f + box->zOffset);
		listOfLines.push_back(box->color);

		listOfLines.push_back(box->position.x - box->xLength * 0.5f + box->xOffset);
		listOfLines.push_back(box->position.y + box->yLength * 0.5f + box->yOffset);
		listOfLines.push_back(box->position.z + box->zLength * 0.5f + box->zOffset);
		listOfLines.push_back(box->color);

		listOfLines.push_back(box->position.x - box->xLength * 0.5f + box->xOffset);
		listOfLines.push_back(box->position.y - box->yLength * 0.5f + box->yOffset);
		listOfLines.push_back(box->position.z + box->zLength * 0.5f + box->zOffset);
		listOfLines.push_back(box->color);

		listOfLines.push_back(box->position.x + box->xLength * 0.5f + box->xOffset);
		listOfLines.push_back(box->position.y + box->yLength * 0.5f + box->yOffset);
		listOfLines.push_back(box->position.z + box->zLength * 0.5f + box->zOffset);
		listOfLines.push_back(box->color);

		listOfLines.push_back(box->position.x + box->xLength * 0.5f + box->xOffset);
		listOfLines.push_back(box->position.y - box->yLength * 0.5f + box->yOffset);
		listOfLines.push_back(box->position.z + box->zLength * 0.5f + box->zOffset);
		listOfLines.push_back(box->color);
	}
}

void RenderManager::drawRay(std::vector<float>& listOfLines, Raycast* ray)
{
	if (ray->visable)
	{
		listOfLines.push_back(ray->position.x);
		listOfLines.push_back(ray->position.y);
		listOfLines.push_back(ray->position.z);
		listOfLines.push_back(ray->color);

		glm::vec3 endPos = glm::vec3(ray->position + ray->Direction * (float)ray->length);

		listOfLines.push_back(endPos.x);
		listOfLines.push_back(endPos.y);
		listOfLines.push_back(endPos.z);
		listOfLines.push_back(ray->color);
	}
}
