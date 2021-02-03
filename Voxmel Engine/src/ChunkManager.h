#ifndef CHUNK_MANAGER_H
#define CHUNK_MANAGER_H

class ChunkManager
{
public:
	ChunkManager();
	~ChunkManager();

	void chunkSetterTest();
	void chunkMesher();

private:
	unsigned int chunkSize = 16;
	unsigned int chunk[4096];	// 16^3

	float voxelSize = 0.25f;
	float voxel[180] =
	{ //Verts												UVs
		(0 * voxelSize), (0 * voxelSize), (0 * voxelSize),	0.0f, 0.0f,
		(0 * voxelSize), (0 * voxelSize), (0 * voxelSize),	0.0f, 0.0f,
		(0 * voxelSize), (0 * voxelSize), (0 * voxelSize),	0.0f, 0.0f,
		(0 * voxelSize), (0 * voxelSize), (0 * voxelSize),	0.0f, 0.0f,
		(0 * voxelSize), (0 * voxelSize), (0 * voxelSize),	0.0f, 0.0f,
		(0 * voxelSize), (0 * voxelSize), (0 * voxelSize),	0.0f, 0.0f,

		(0 * voxelSize), (0 * voxelSize), (0 * voxelSize),	0.0f, 0.0f,
		(0 * voxelSize), (0 * voxelSize), (0 * voxelSize),	0.0f, 0.0f,
		(0 * voxelSize), (0 * voxelSize), (0 * voxelSize),	0.0f, 0.0f,
		(0 * voxelSize), (0 * voxelSize), (0 * voxelSize),	0.0f, 0.0f,
		(0 * voxelSize), (0 * voxelSize), (0 * voxelSize),	0.0f, 0.0f,
		(0 * voxelSize), (0 * voxelSize), (0 * voxelSize),	0.0f, 0.0f,

		(0 * voxelSize), (0 * voxelSize), (0 * voxelSize),	0.0f, 0.0f,
		(0 * voxelSize), (0 * voxelSize), (0 * voxelSize),	0.0f, 0.0f,
		(0 * voxelSize), (0 * voxelSize), (0 * voxelSize),	0.0f, 0.0f,
		(0 * voxelSize), (0 * voxelSize), (0 * voxelSize),	0.0f, 0.0f,
		(0 * voxelSize), (0 * voxelSize), (0 * voxelSize),	0.0f, 0.0f,
		(0 * voxelSize), (0 * voxelSize), (0 * voxelSize),	0.0f, 0.0f,

		(0 * voxelSize), (0 * voxelSize), (0 * voxelSize),	0.0f, 0.0f,
		(0 * voxelSize), (0 * voxelSize), (0 * voxelSize),	0.0f, 0.0f,
		(0 * voxelSize), (0 * voxelSize), (0 * voxelSize),	0.0f, 0.0f,
		(0 * voxelSize), (0 * voxelSize), (0 * voxelSize),	0.0f, 0.0f,
		(0 * voxelSize), (0 * voxelSize), (0 * voxelSize),	0.0f, 0.0f,
		(0 * voxelSize), (0 * voxelSize), (0 * voxelSize),	0.0f, 0.0f,

		(0 * voxelSize), (0 * voxelSize), (0 * voxelSize),	0.0f, 0.0f,
		(0 * voxelSize), (0 * voxelSize), (0 * voxelSize),	0.0f, 0.0f,
		(0 * voxelSize), (0 * voxelSize), (0 * voxelSize),	0.0f, 0.0f,
		(0 * voxelSize), (0 * voxelSize), (0 * voxelSize),	0.0f, 0.0f,
		(0 * voxelSize), (0 * voxelSize), (0 * voxelSize),	0.0f, 0.0f,
		(0 * voxelSize), (0 * voxelSize), (0 * voxelSize),	0.0f, 0.0f,

		(0 * voxelSize), (0 * voxelSize), (0 * voxelSize),	0.0f, 0.0f,
		(0 * voxelSize), (0 * voxelSize), (0 * voxelSize),	0.0f, 0.0f,
		(0 * voxelSize), (0 * voxelSize), (0 * voxelSize),	0.0f, 0.0f,
		(0 * voxelSize), (0 * voxelSize), (0 * voxelSize),	0.0f, 0.0f,
		(0 * voxelSize), (0 * voxelSize), (0 * voxelSize),	0.0f, 0.0f,
		(0 * voxelSize), (0 * voxelSize), (0 * voxelSize),	0.0f, 0.0f
	};
};

#endif // !CHUNK_MANAGER_H
