#ifndef CHUNK_H
#define CHUNK_H

#include <glad/glad.h>

struct Voxel
{
	float x;
	float y;
	float z;

	unsigned int blockID;
};

class Chunk
{
public:
	// OpenGL : Buffers
	GLuint VAO;
	GLuint VBO;
	unsigned int verticiesAmount;

	Chunk();
	~Chunk();

private:

};

#endif // !CHUNK_H

