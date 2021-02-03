#include "MeshLoader.h"

MeshLoader::MeshLoader()
{
}

MeshLoader::~MeshLoader()
{
}

void MeshLoader::OpenGLBufferLoading(GLuint& VAO, GLuint& VBO, GLuint& EBO, std::vector<unsigned int>& indicesList)
{
    std::vector<unsigned int> newIndices;
    std::vector<Vertex> newVertices;

    unsigned int nxtInidices = 0;

    for (unsigned int i = 0; i < myMeshes.size(); i++)
    {
        for (unsigned int n = 0; n < myMeshes[i].indices.size(); n++)
        {
            newIndices.push_back(myMeshes[i].indices[n] + nxtInidices);
        }

        for (unsigned int n = 0; n < myMeshes[i].vertices.size(); n++)
        {
            newVertices.push_back(myMeshes[i].vertices[n]);
            nxtInidices++;
        }
    }

    indicesList = newIndices;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, newVertices.size() * sizeof(Vertex), &newVertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, newIndices.size() * sizeof(unsigned int), &newIndices[0], GL_STATIC_DRAW);

    // Vertex positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    // Vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
    // Vertex texture coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

    glBindVertexArray(0);
}

bool MeshLoader::loadMesh(std::string meshPath)
{
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(meshPath, aiProcess_JoinIdenticalVertices | aiProcess_FlipUVs);

    // If the import failed, report it
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
        return false;
    }

    directory = meshPath.substr(0, meshPath.find_last_of('/'));

    // Now we can access the file's contents.
    processNode(scene->mRootNode, scene);
    return true;
}

void MeshLoader::processNode(aiNode* node, const aiScene* scene)
{
    // process all the node's meshes (if any)
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* newMesh = scene->mMeshes[node->mMeshes[i]];
        //myMeshes.push_back(processMesh(mesh, scene));
        processMesh(newMesh, scene);
    }
    // then do the same for each of its children
    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }
}

void MeshLoader::processMesh(aiMesh* mesh, const aiScene* scene)
{
    Mesh newMesh;
    myMeshes.push_back(newMesh);

    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;
        // process vertex positions, normals and texture coordinates
        glm::vec3 vector;
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.Position = vector;

        vector.x = mesh->mNormals[i].x;
        vector.y = mesh->mNormals[i].y;
        vector.z = mesh->mNormals[i].z;
        vertex.Normal = vector;

        if (mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
        {
            glm::vec2 vec;
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.TexCoords = vec;
        }
        else
            vertex.TexCoords = glm::vec2(0.0f, 0.0f);

        myMeshes.back().vertices.push_back(vertex);
    }
    // process indices
    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++)
            myMeshes.back().indices.push_back(face.mIndices[j]);
    }
}
