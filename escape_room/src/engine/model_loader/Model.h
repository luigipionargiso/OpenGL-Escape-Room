#pragma once

#include <vector>
#include "Mesh.h"
#include "engine/Texture.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class Model
{
private:
    std::vector<Mesh> m_meshes;
    std::string m_directory;

    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    Vertex LoadVertices(aiMesh* mesh, unsigned int index);
    Texture LoadTexture(aiMaterial* mat, aiTextureType ai_type, TextureType type);
public:
    Model(std::string path);
    void Draw(Shader& shader);
};
