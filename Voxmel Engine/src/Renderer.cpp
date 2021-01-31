#include "Renderer.h"

Renderer::Renderer(GLFWwindow* win, float* mouseScroll)
{
	window = win;
	mouseS = mouseScroll;
	init();

	// Temp

	float vertices[] = {
		// Verts				UVs				 Normals
		-0.5f, -0.5f, -0.5f,	0.0f, 0.0f,		 0.0f, 0.0f, -1.0f,
		 0.5f, -0.5f, -0.5f,	1.0f, 0.0f,		 0.0f, 0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,	1.0f, 1.0f,		 0.0f, 0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,	1.0f, 1.0f,		 0.0f, 0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,	0.0f, 1.0f,		 0.0f, 0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,	0.0f, 0.0f,		 0.0f, 0.0f, -1.0f,
												 
		-0.5f, -0.5f,  0.5f,	0.0f, 0.0f,		 0.0f, 0.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,	1.0f, 0.0f,		 0.0f, 0.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,	1.0f, 1.0f,		 0.0f, 0.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,	1.0f, 1.0f,		 0.0f, 0.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,	0.0f, 1.0f,		 0.0f, 0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,	0.0f, 0.0f,		 0.0f, 0.0f,  1.0f,

		-0.5f,  0.5f,  0.5f,	1.0f, 0.0f,		-1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,	1.0f, 1.0f,		-1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,	0.0f, 1.0f,		-1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,	0.0f, 1.0f,		-1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,	0.0f, 0.0f,		-1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,	1.0f, 0.0f,		-1.0f,  0.0f,  0.0f,

		 0.5f,  0.5f,  0.5f,	1.0f, 0.0f,		 1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,	1.0f, 1.0f,		 1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,	0.0f, 1.0f,		 1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,	0.0f, 1.0f,		 1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,	0.0f, 0.0f,		 1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,	1.0f, 0.0f,		 1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,	0.0f, 1.0f,		 0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,	1.0f, 1.0f,		 0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,	1.0f, 0.0f,		 0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,	1.0f, 0.0f,		 0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,	0.0f, 0.0f,		 0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,	0.0f, 1.0f,		 0.0f, -1.0f,  0.0f,

		-0.5f,  0.5f, -0.5f,	0.0f, 1.0f,		 0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,	1.0f, 1.0f,		 0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,	1.0f, 0.0f,		 0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,	1.0f, 0.0f,		 0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,	0.0f, 0.0f,		 0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,	0.0f, 1.0f,		 0.0f,  1.0f,  0.0f
	};

	tempVertSize = sizeof(vertices);

	glGenVertexArrays(1, &tempVAO);
	glGenBuffers(1, &tempVBO);

	glBindVertexArray(tempVAO);
	// we only need to bind to the VBO, the container's VBO's data already contains the data.
	glBindBuffer(GL_ARRAY_BUFFER, tempVBO);
	// set the vertex attribute 
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(0 * sizeof(float)));
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, tempVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);
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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(0 * sizeof(float)));
	glEnableVertexAttribArray(0);
	// UVs
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	if (e.modelData.texture.albedoPath != "NULL")
	{
		loadTexture(e.modelData.texture.albedoPath, EntityList.back().albedoTexture, false);
	}

	if (e.modelData.texture.secondTexturePath != "NULL")
	{
		loadTexture(e.modelData.texture.secondTexturePath, EntityList.back().secondTexturePath, true);
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
	Shader basicShader;
	shaders.push_back(basicShader);
	shaders.back().create("res/shaders/basic.vs", "res/shaders/basic.fs");

	Shader tempShader;
	shaders.push_back(tempShader);
	shaders.back().create("res/shaders/temp.vs", "res/shaders/temp.fs");

	Shader lightShader;
	shaders.push_back(lightShader);
	shaders.back().create("res/shaders/light.vs", "res/shaders/light.fs");
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

	for (size_t i = 0; i < EntityList.size(); i++)
	{
		/*glm::mat4 model = glm::mat4(1.0f);
		if ((EntityList[i].entity->transform.x != 0) || (EntityList[i].entity->transform.y != 0) || (EntityList[i].entity->transform.z != 0))
		{
			model = glm::translate(model, EntityList[i].entity->transform);
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
		}
		if ((EntityList[i].entity->scale.x != 1) || (EntityList[i].entity->scale.y != 1) || (EntityList[i].entity->scale.z != 1))
		{
			model = glm::scale(model, EntityList[i].entity->scale);
		}*/
		
		//----------------------------------------------------------------------------
		// This is just to move the spawned cubes around
		glm::vec3 cubePositions[] = {
			glm::vec3(5.0f,  0.0f,  0.0f),
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

		shaders[EntityList[i].shader].use();

		shaders[EntityList[i].shader].setMat4("model", model);
		shaders[EntityList[i].shader].setMat4("view", view);
		shaders[EntityList[i].shader].setMat4("projection", projection);

		if (!EntityList[i].albedoTexture == 0)
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, EntityList[i].albedoTexture);
			shaders[EntityList[i].shader].setInt("albedoTexture", 0);
		}

		if (!EntityList[i].secondTexturePath == 0)
		{
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, EntityList[i].secondTexturePath);
		shaders[EntityList[i].shader].setInt("secondTexture", 1);
		}

		glBindVertexArray(EntityList[i].VAO);
		glDrawArrays(GL_TRIANGLES, 0, EntityList[i].vertsSize);
		glBindVertexArray(0);
	}

	// New box for light
	glm::mat4 model = glm::mat4(1.0f);
	float angle = 1.0f * glfwGetTime();
	model = glm::rotate(model, angle, glm::vec3(1.0f, 0.0f, 0.0f));

	glm::mat4 VP = projection * view;
	glm::mat3 normalMat = glm::transpose(glm::inverse(model));

	shaders[1].use();

	shaders[1].setMat4("VP", VP);
	shaders[1].setMat3("normalMat", normalMat);
	shaders[1].setVec3("viewPos", camera->transform);
	shaders[1].setMat4("model", model);
	shaders[1].setMat4("view", view);
	shaders[1].setMat4("projection", projection);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, EntityList[0].albedoTexture);
	shaders[0].setInt("albedoTexture", 0);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, EntityList[0].albedoTexture);
	shaders[0].setInt("secondTexture", 0);

	shaders[1].setVec3("objectColor", glm::vec3(1.0f, 0.5f, 0.31f));
	shaders[1].setVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
	shaders[1].setVec3("lightPos", lightPos);

	glBindVertexArray(tempVAO);
	glDrawArrays(GL_TRIANGLES, 0, tempVertSize);
	glBindVertexArray(0);

	// Light
	// set light position
	float lightX = 2.0f * sin(glfwGetTime());
	float lightY = 0.0f;
	float lightZ = 2.0f * cos(glfwGetTime());
	lightPos = glm::vec3(lightX, lightY, lightZ);

	model = glm::mat4(1.0f);
	model = glm::translate(model, lightPos);
	model = glm::scale(model, glm::vec3(0.2f));

	//glm::mat4 MVP = projection * view * model;

	shaders[2].use();

	//shaders[2].setMat4("MVP", MVP);

	shaders[2].setMat4("model", model);
	shaders[2].setMat4("view", view);
	shaders[2].setMat4("projection", projection);
	shaders[2].setVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));

	glBindVertexArray(tempVAO);
	glDrawArrays(GL_TRIANGLES, 0, tempVertSize);
	glBindVertexArray(0);

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

