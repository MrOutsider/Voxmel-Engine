#include "Entity.h"

Entity::Entity()
{
	// Hard coded for learning
	vertices = {
		// Positions			Colors				UV
		 0.5f,  0.5f, 0.0f,		1.0f, 0.0f, 0.0f,	1.0f, 1.0f,	// Top Right
		 0.5f, -0.5f, 0.0f,		0.0f, 1.0f, 0.0f,	1.0f, 0.0f,	// Bottom Right
		-0.5f, -0.5f, 0.0f,		0.0f, 0.0f, 1.0f,	0.0f, 0.0f,	// Bottom Left
		-0.5f,  0.5f, 0.0f,		1.0f, 1.0f, 0.0f,	0.0f, 1.0f	// Top Left
	};

	indices = {
		0, 1, 2,
		2, 3, 0
	};

	textures.push_back("res/textures/container.jpg");
}

Entity::~Entity()
{
}

std::vector<float>& Entity::getVertices()
{
	return vertices;
}

std::vector<uint32_t>& Entity::getIndices()
{
	return indices;
}

std::vector<const char*>& Entity::getTextures()
{
	return textures;
}
