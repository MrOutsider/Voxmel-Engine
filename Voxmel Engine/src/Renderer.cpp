#include "Renderer.h"

Renderer::Renderer(GLFWwindow* win, float* mouseScroll, ChunkManager& ChunkManager, /*TMP*/ PhysicsManager& pm)
{
	window = win;
	mouseS = mouseScroll;
	CM = &ChunkManager;
	init();

	physicsManager = &pm;
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

	glGenVertexArrays(1, &PhysicsVAO);
	glGenBuffers(1, &PhysicsVBO);
}

void Renderer::compileShaders()
{
	// 0
	Shader physicsShader;
	shaders.push_back(physicsShader);
	shaders.back().create("res/shaders/physics.vs", "res/shaders/physics.fs");

	// 1
	Shader voxelShader;
	shaders.push_back(voxelShader);
	shaders.back().create("res/shaders/voxel.vs", "res/shaders/voxel.fs");

	// 2
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
	//glDisable(GL_CULL_FACE);//TMP

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
	projection = glm::perspective(glm::radians(fov), (float)width / (float)height, 0.01f, 1000.0f);

	glm::mat4 model = glm::mat4(1.0f);

	// Rendering Voxels
	for (unsigned int i = 0; i < CM->loadedChunks.size(); i++)
	{
		shaders[VOXEL_SHADER].use();

		// Translate the chunk to a vec3 pos * sizeOf Chunk rows
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(CM->loadedChunks[i]->x * CM->loadedChunks[i]->chunkSize * CM->loadedChunks[i]->voxelSizeHalf * 2, 0.0f, 0.0f));
		model = glm::translate(model, glm::vec3(0.0f, CM->loadedChunks[i]->y * CM->loadedChunks[i]->chunkSize * CM->loadedChunks[i]->voxelSizeHalf * 2, 0.0f));
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, CM->loadedChunks[i]->z * CM->loadedChunks[i]->chunkSize * CM->loadedChunks[i]->voxelSizeHalf * 2));
		
		glm::mat4 MVP = projection * view * model;

		shaders[VOXEL_SHADER].setMat4("MVP", MVP);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, chunkAlbedo);
		shaders[VOXEL_SHADER].setInt("albedo", 0);

		glBindVertexArray(CM->loadedChunks[i]->VAO);
		glDrawArrays(GL_TRIANGLES, 0, CM->loadedChunks[i]->verticiesAmount);
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

		for (unsigned int i = 0; i < physicsManager->AABB_RenderList.size(); i++)
		{
			drawBox(listOfLines, *physicsManager->AABB_RenderList[i]);
		}

		for (unsigned int i = 0; i < physicsManager->raycastRenderList.size(); i++)
		{
			drawRay(listOfLines, *physicsManager->raycastRenderList[i]);
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


			glDisable(GL_DEPTH_TEST);
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
		glDeleteBuffers(1, &models[i]->VBO);
		glDeleteBuffers(1, &models[i]->EBO);
		glDeleteTextures(1, &models[i]->albedo);
	}

	glDeleteVertexArrays(1, &PhysicsVAO);
	glDeleteBuffers(1, &PhysicsVBO);

	shaders.clear();
	models.clear();
}

void Renderer::drawBox(std::vector<float>& listOfLines, AABB& box)
{
	listOfLines.push_back(box.position.x - box.xLength * 0.5f + box.xOffset);
	listOfLines.push_back(box.position.y - box.yLength * 0.5f + box.yOffset);
	listOfLines.push_back(box.position.z + box.zLength * 0.5f + box.zOffset);
	listOfLines.push_back(box.isIntersecting);

	listOfLines.push_back(box.position.x + box.xLength * 0.5f + box.xOffset);
	listOfLines.push_back(box.position.y - box.yLength * 0.5f + box.yOffset);
	listOfLines.push_back(box.position.z + box.zLength * 0.5f + box.zOffset);
	listOfLines.push_back(box.isIntersecting);

	listOfLines.push_back(box.position.x - box.xLength * 0.5f + box.xOffset);
	listOfLines.push_back(box.position.y + box.yLength * 0.5f + box.yOffset);
	listOfLines.push_back(box.position.z + box.zLength * 0.5f + box.zOffset);
	listOfLines.push_back(box.isIntersecting);

	listOfLines.push_back(box.position.x + box.xLength * 0.5f + box.xOffset);
	listOfLines.push_back(box.position.y + box.yLength * 0.5f + box.yOffset);
	listOfLines.push_back(box.position.z + box.zLength * 0.5f + box.zOffset);
	listOfLines.push_back(box.isIntersecting);

	listOfLines.push_back(box.position.x - box.xLength * 0.5f + box.xOffset);
	listOfLines.push_back(box.position.y - box.yLength * 0.5f + box.yOffset);
	listOfLines.push_back(box.position.z - box.zLength * 0.5f + box.zOffset);
	listOfLines.push_back(box.isIntersecting);

	listOfLines.push_back(box.position.x + box.xLength * 0.5f + box.xOffset);
	listOfLines.push_back(box.position.y - box.yLength * 0.5f + box.yOffset);
	listOfLines.push_back(box.position.z - box.zLength * 0.5f + box.zOffset);
	listOfLines.push_back(box.isIntersecting);

	listOfLines.push_back(box.position.x - box.xLength * 0.5f + box.xOffset);
	listOfLines.push_back(box.position.y + box.yLength * 0.5f + box.yOffset);
	listOfLines.push_back(box.position.z - box.zLength * 0.5f + box.zOffset);
	listOfLines.push_back(box.isIntersecting);

	listOfLines.push_back(box.position.x + box.xLength * 0.5f + box.xOffset);
	listOfLines.push_back(box.position.y + box.yLength * 0.5f + box.yOffset);
	listOfLines.push_back(box.position.z - box.zLength * 0.5f + box.zOffset);
	listOfLines.push_back(box.isIntersecting);

	// X
	listOfLines.push_back(box.position.x + box.xLength * 0.5f + box.xOffset);
	listOfLines.push_back(box.position.y - box.yLength * 0.5f + box.yOffset);
	listOfLines.push_back(box.position.z - box.zLength * 0.5f + box.zOffset);
	listOfLines.push_back(box.isIntersecting);

	listOfLines.push_back(box.position.x + box.xLength * 0.5f + box.xOffset);
	listOfLines.push_back(box.position.y - box.yLength * 0.5f + box.yOffset);
	listOfLines.push_back(box.position.z + box.zLength * 0.5f + box.zOffset);
	listOfLines.push_back(box.isIntersecting);

	listOfLines.push_back(box.position.x + box.xLength * 0.5f + box.xOffset);
	listOfLines.push_back(box.position.y + box.yLength * 0.5f + box.yOffset);
	listOfLines.push_back(box.position.z - box.zLength * 0.5f + box.zOffset);
	listOfLines.push_back(box.isIntersecting);

	listOfLines.push_back(box.position.x + box.xLength * 0.5f + box.xOffset);
	listOfLines.push_back(box.position.y + box.yLength * 0.5f + box.yOffset);
	listOfLines.push_back(box.position.z + box.zLength * 0.5f + box.zOffset);
	listOfLines.push_back(box.isIntersecting);

	listOfLines.push_back(box.position.x - box.xLength * 0.5f + box.xOffset);
	listOfLines.push_back(box.position.y - box.yLength * 0.5f + box.yOffset);
	listOfLines.push_back(box.position.z - box.zLength * 0.5f + box.zOffset);
	listOfLines.push_back(box.isIntersecting);

	listOfLines.push_back(box.position.x - box.xLength * 0.5f + box.xOffset);
	listOfLines.push_back(box.position.y - box.yLength * 0.5f + box.yOffset);
	listOfLines.push_back(box.position.z + box.zLength * 0.5f + box.zOffset);
	listOfLines.push_back(box.isIntersecting);

	listOfLines.push_back(box.position.x - box.xLength * 0.5f + box.xOffset);
	listOfLines.push_back(box.position.y + box.yLength * 0.5f + box.yOffset);
	listOfLines.push_back(box.position.z - box.zLength * 0.5f + box.zOffset);
	listOfLines.push_back(box.isIntersecting);

	listOfLines.push_back(box.position.x - box.xLength * 0.5f + box.xOffset);
	listOfLines.push_back(box.position.y + box.yLength * 0.5f + box.yOffset);
	listOfLines.push_back(box.position.z + box.zLength * 0.5f + box.zOffset);
	listOfLines.push_back(box.isIntersecting);

	// Y
	listOfLines.push_back(box.position.x - box.xLength * 0.5f + box.xOffset);
	listOfLines.push_back(box.position.y + box.yLength * 0.5f + box.yOffset);
	listOfLines.push_back(box.position.z - box.zLength * 0.5f + box.zOffset);
	listOfLines.push_back(box.isIntersecting);

	listOfLines.push_back(box.position.x - box.xLength * 0.5f + box.xOffset);
	listOfLines.push_back(box.position.y - box.yLength * 0.5f + box.yOffset);
	listOfLines.push_back(box.position.z - box.zLength * 0.5f + box.zOffset);
	listOfLines.push_back(box.isIntersecting);

	listOfLines.push_back(box.position.x + box.xLength * 0.5f + box.xOffset);
	listOfLines.push_back(box.position.y + box.yLength * 0.5f + box.yOffset);
	listOfLines.push_back(box.position.z - box.zLength * 0.5f + box.zOffset);
	listOfLines.push_back(box.isIntersecting);

	listOfLines.push_back(box.position.x + box.xLength * 0.5f + box.xOffset);
	listOfLines.push_back(box.position.y - box.yLength * 0.5f + box.yOffset);
	listOfLines.push_back(box.position.z - box.zLength * 0.5f + box.zOffset);
	listOfLines.push_back(box.isIntersecting);

	listOfLines.push_back(box.position.x - box.xLength * 0.5f + box.xOffset);
	listOfLines.push_back(box.position.y + box.yLength * 0.5f + box.yOffset);
	listOfLines.push_back(box.position.z + box.zLength * 0.5f + box.zOffset);
	listOfLines.push_back(box.isIntersecting);

	listOfLines.push_back(box.position.x - box.xLength * 0.5f + box.xOffset);
	listOfLines.push_back(box.position.y - box.yLength * 0.5f + box.yOffset);
	listOfLines.push_back(box.position.z + box.zLength * 0.5f + box.zOffset);
	listOfLines.push_back(box.isIntersecting);

	listOfLines.push_back(box.position.x + box.xLength * 0.5f + box.xOffset);
	listOfLines.push_back(box.position.y + box.yLength * 0.5f + box.yOffset);
	listOfLines.push_back(box.position.z + box.zLength * 0.5f + box.zOffset);
	listOfLines.push_back(box.isIntersecting);

	listOfLines.push_back(box.position.x + box.xLength * 0.5f + box.xOffset);
	listOfLines.push_back(box.position.y - box.yLength * 0.5f + box.yOffset);
	listOfLines.push_back(box.position.z + box.zLength * 0.5f + box.zOffset);
	listOfLines.push_back(box.isIntersecting);
}

void Renderer::drawRay(std::vector<float>& listOfLines, Raycast& ray)
{
	listOfLines.push_back(ray.position.x);
	listOfLines.push_back(ray.position.y);
	listOfLines.push_back(ray.position.z);
	listOfLines.push_back(ray.isIntersecting);

	glm::vec3 endPos = glm::vec3(ray.position + ray.Direction * (float)ray.length);

	listOfLines.push_back(endPos.x);
	listOfLines.push_back(endPos.y);
	listOfLines.push_back(endPos.z);
	listOfLines.push_back(ray.isIntersecting);
}
