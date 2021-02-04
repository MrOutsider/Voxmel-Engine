#ifndef RENDERER_H
#define RENDERER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <string>
#include <vector>

#include "Shader.h"
#include "MeshLoader.h"
#include "Camera.h"
#include "Entity.h"

#include "ChunkManager.h"

class Renderer
{
public:
	struct RenderTarget
	{
		Entity* entity;

		std::vector<unsigned int> indicesList;
		GLuint VAO;
		GLuint VBO;
		GLuint EBO;
		GLuint albedo;
	};

	unsigned int drawCalls = 0;
	//----------------------------------
	ChunkManager cManager;

	unsigned int vertexCount = 0;
	GLuint chunkMeshVAO;
	GLuint chunkMeshVBO;
	GLuint chunkAlbedo;
	void initChunk();
	//----------------------------------
	Renderer(GLFWwindow* win, float* mouseScroll);
	void addCamera(Camera& cam);

	void loadEntityData(Entity& entity);
	void removeEntity(Entity& entity);

	void addEntityToRenderList(Entity& entinty);
	void removeEntityFromRenderList(Entity& entinty);

	void render();
	void destroy();
private:
	GLFWwindow* window;
	Camera* camera;
	float* mouseS;

	std::vector<Shader> shaders;
	// Voxel = 0
	// Entity = 1

	const float FOV = 45.0f;
	float fov = FOV;

	std::vector<RenderTarget> models;
	std::vector<Entity*> renderList;

	void init();
	void compileShaders();
	void loadModel(const char* modelPath, const char* texturePath, Entity& entity);
	void loadTexture(const char* textureName, GLuint& target, bool transparent);
};

#endif // !RENDERER_H

