#include "Entity.h"

Entity::Entity()
{
	// Hard coded for learning
	modelData.vertices = {
		-0.5f,  0.5f, -0.5f,	0.0f, 1.0f, // 0	Back
		 0.5f,  0.5f, -0.5f,	1.0f, 1.0f, // 1
		 0.5f, -0.5f, -0.5f,	1.0f, 0.0f, // 2
		-0.5f, -0.5f, -0.5f,	0.0f, 0.0f, // 3

		 0.5f,  0.5f,  0.5f,	0.0f, 1.0f, // 4	Right
		 0.5f,  0.5f, -0.5f,	1.0f, 1.0f, // 5
		 0.5f, -0.5f, -0.5f,	1.0f, 0.0f, // 6
		 0.5f, -0.5f,  0.5f,	0.0f, 0.0f, // 7

		-0.5f,  0.5f,  0.5f,	0.0f, 1.0f, // 8	Front
		 0.5f,  0.5f,  0.5f,	1.0f, 1.0f, // 9
		 0.5f, -0.5f,  0.5f,	1.0f, 0.0f, // 10
		-0.5f, -0.5f,  0.5f,	0.0f, 0.0f, // 11
					  
		-0.5f,  0.5f, -0.5f,	0.0f, 1.0f, // 12	Top
		 0.5f,  0.5f, -0.5f,	1.0f, 1.0f, // 13
		 0.5f,  0.5f,  0.5f,	1.0f, 0.0f, // 14
		-0.5f,  0.5f,  0.5f,	0.0f, 0.0f, // 15

		-0.5f,  0.5f, -0.5f,	0.0f, 1.0f, // 16	Left
		-0.5f,  0.5f,  0.5f,	1.0f, 1.0f, // 17
		-0.5f, -0.5f,  0.5f,	1.0f, 0.0f, // 18
		-0.5f, -0.5f, -0.5f,	0.0f, 0.0f, // 19

		-0.5f, -0.5f, -0.5f,	0.0f, 1.0f, // 20	Bottom
		 0.5f, -0.5f, -0.5f,	1.0f, 1.0f, // 21
		 0.5f, -0.5f,  0.5f,	1.0f, 0.0f, // 22
		-0.5f, -0.5f,  0.5f,	0.0f, 0.0f  // 23
	};

	modelData.indices = {
		0,  1,  3,
		1,  2,  3,

		4,  5,  6,
		6,  7,  4,

		8,  9,  10,
		10, 11, 8,

		12, 13, 14,
		14, 15, 12,

		16, 17, 18,
		18, 19, 16,

		20, 21, 22,
		22, 23, 20
	};

	modelData.texture.albedo = "res/textures/container.jpg";
	modelData.texture.secondTexture = "res/textures/awesomeface.png";
}

Entity::~Entity()
{
}
