#pragma once

#include <vector>
#include "Mesh.h"
#include "engine/Texture.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

struct AABB
{
    glm::vec3 min;
    glm::vec3 max;
};

class Model
{
public:
    Model(std::string filepath);

    // move constructor
    Model(Model&& other) noexcept = default;
    // move assignment
    Model& operator=(Model&& other) noexcept = default;

    void Draw(Shader& shader) const;
    AABB GetAABB() const { return bounding_box_; }

private:
    std::vector<Mesh> meshes_;
    std::string directory_;
    AABB bounding_box_;

    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    Vertex LoadVertex(aiMesh* mesh, unsigned int index);
    Texture LoadTexture(aiMaterial* mat, aiTextureType ai_type, TextureType type);
    AABB CalculateAABB(const aiScene* scene);
};
