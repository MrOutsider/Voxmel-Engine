#ifndef MESH_LOADER_H
#define MESH_LOADER_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <iostream>
#include <string>
#include <vector>

class MeshLoader
{
public:
    struct Vertex {
        glm::vec3 Position;
        glm::vec3 Normal;
        glm::vec2 TexCoords;
    };

    struct Texture {
        unsigned int id;
        std::string type;
    };

    struct Mesh
    {
        std::vector<Vertex>       vertices;
        std::vector<unsigned int> indices;
    };

    std::string directory;

	MeshLoader();
	~MeshLoader();

    void OpenGLBufferLoading(std::vector<GLuint>& VAOs, std::vector<GLuint>& VBOs, std::vector<GLuint>& EBOs, std::vector<std::vector<unsigned int>>& indicesList);
    bool loadMesh(std::string meshPath);

private:
    void processNode(aiNode* node, const aiScene* scene);
    void processMesh(aiMesh* mesh, const aiScene* scene);

    std::vector<Mesh> myMeshes;
};
#endif // !MESH_LOADER_H

