#include "Model.h"
#include <iostream>
#include "vendor/glm/glm.hpp"

Model::Model(std::string filepath)
{
    Assimp::Importer import;
    const aiScene* scene = import.ReadFile(filepath,
        aiProcess_Triangulate |
              aiProcess_GenBoundingBoxes |
              aiProcess_CalcTangentSpace |
              aiProcess_GenNormals |
        aiProcess_JoinIdenticalVertices
    );

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << '\n';
        return;
    }
    directory_ = filepath.substr(0, filepath.find_last_of('/'));

    bounding_box_ = CalculateAABB(scene);

    //std::cout << bounding_box_.min.x << bounding_box_.max.x << '\n';

    processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode* node, const aiScene* scene)
{
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        meshes_.push_back(processMesh(mesh, scene));
    }

    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }
}

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    // vertices
    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
        vertices.push_back(LoadVertex(mesh, i));

    // indices
    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }
    
    // textures
    if (mesh->mMaterialIndex >= 0)
    {
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

        // diffuse map
        if (material->GetTextureCount(aiTextureType_DIFFUSE) != 0)
            textures.push_back(
                LoadTexture(material, aiTextureType_DIFFUSE, DIFFUSE)
            );

        // specular map
        if (material->GetTextureCount(aiTextureType_SPECULAR) != 0)
            textures.push_back(
                LoadTexture(material, aiTextureType_SPECULAR, SPECULAR)
            );

        // normal map
        if (material->GetTextureCount(aiTextureType_NORMALS) != 0)
            textures.push_back(
                LoadTexture(material, aiTextureType_NORMALS, NORMAL)
            );
    }

    return std::move(Mesh(vertices, indices, std::move(textures)));
}

Vertex Model::LoadVertex(aiMesh* mesh, unsigned int index)
{
    Vertex vertex{};

    glm::vec3 vector{};
    vector.x = mesh->mVertices[index].x;
    vector.y = mesh->mVertices[index].y;
    vector.z = mesh->mVertices[index].z;
    vertex.position = vector;

    vector.x = mesh->mNormals[index].x;
    vector.y = mesh->mNormals[index].y;
    vector.z = mesh->mNormals[index].z;
    vertex.normal = vector;

    if (mesh->mTextureCoords[0])
    {
        glm::vec2 vec{};
        vec.x = mesh->mTextureCoords[0][index].x;
        vec.y = mesh->mTextureCoords[0][index].y;
        vertex.texture_coords = vec;
    }
    else
        vertex.texture_coords = glm::vec2(0.0f, 0.0f);

    vector.x = mesh->mTangents[index].x;
    vector.y = mesh->mTangents[index].y;
    vector.z = mesh->mTangents[index].z;
    vertex.tangent = vector;

    return vertex;
}

Texture Model::LoadTexture(aiMaterial* mat, aiTextureType ai_type, TextureType type)
{
    aiString name;
    mat->GetTexture(ai_type, 0, &name);
    std::string path = directory_ + '/' + name.C_Str();
    return Texture(path, type);
}

AABB Model::CalculateAABB(const aiScene* scene)
{
    glm::vec3 max = glm::vec3(
        (float)scene->mMeshes[0]->mAABB.mMax.x,
        (float)scene->mMeshes[0]->mAABB.mMax.y,
        (float)scene->mMeshes[0]->mAABB.mMax.z
    );
    glm::vec3 min = glm::vec3(
        (float)scene->mMeshes[0]->mAABB.mMin.x,
        (float)scene->mMeshes[0]->mAABB.mMin.y,
        (float)scene->mMeshes[0]->mAABB.mMin.z
    );

    for (unsigned int i = 1; i < scene->mNumMeshes; i++)
    {
        max.x = std::max(max.x, scene->mMeshes[i]->mAABB.mMax.x);
        max.y = std::max(max.y, scene->mMeshes[i]->mAABB.mMax.y);
        max.z = std::max(max.z, scene->mMeshes[i]->mAABB.mMax.z);
        min.x = std::min(min.x, scene->mMeshes[i]->mAABB.mMin.x);
        min.y = std::min(min.y, scene->mMeshes[i]->mAABB.mMin.y);
        min.z = std::min(min.z, scene->mMeshes[i]->mAABB.mMin.z);
    }

    return AABB{ min, max };
}

void Model::Draw(Shader& shader) const
{
    for (unsigned int i = 0; i < meshes_.size(); i++)
        meshes_[i].Draw(shader);
}
