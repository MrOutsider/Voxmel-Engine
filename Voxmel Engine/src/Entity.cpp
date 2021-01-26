#include "Entity.h"

Entity::Entity()
{
	// Hard coded for learning
	modelData.vertices = {
		// Positions			UV
		 0.5f,  0.5f, 0.0f,		1.0f, 1.0f,	// Top Right
		 0.5f, -0.5f, 0.0f,		1.0f, 0.0f,	// Bottom Right
		-0.5f, -0.5f, 0.0f,		0.0f, 0.0f,	// Bottom Left
		-0.5f,  0.5f, 0.0f,		0.0f, 1.0f	// Top Left
	};

	modelData.indices = {
		0, 1, 2,
		2, 3, 0
	};

	modelData.texture.albedo = "res/textures/container.jpg";
	modelData.texture.secondTexture = "res/textures/awesomeface.png";
}

Entity::~Entity()
{
}
