#include <iostream>
#include "Model.h"
#include "vendor/glm/glm.hpp"

Model::Model(std::string path)
{
    Assimp::Importer import;
    const aiScene* scene = import.ReadFile(path, aiProcess_Triangulate |
                                                            aiProcess_CalcTangentSpace |
                                                            aiProcess_GenNormals);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << '\n';
        return;
    }
    m_directory = path.substr(0, path.find_last_of('/'));

    processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode* node, const aiScene* scene)
{
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        m_meshes.push_back(processMesh(mesh, scene));
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

    /* Vertices */
    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
        vertices.push_back(LoadVertices(mesh, i));
    
    /* Indices */
    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }
    
    /* Textures */
    if (mesh->mMaterialIndex >= 0)
    {
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

        /* diffuse map */
        if (material->GetTextureCount(aiTextureType_DIFFUSE) != 0)
            textures.push_back(
                LoadTexture(material, aiTextureType_DIFFUSE, DIFFUSE)
            );

        /* specular map */
        if (material->GetTextureCount(aiTextureType_SPECULAR) != 0)
            textures.push_back(
                LoadTexture(material, aiTextureType_SPECULAR, SPECULAR)
            );
    }

    return std::move(Mesh(vertices, indices, std::move(textures)));
}

Vertex Model::LoadVertices(aiMesh* mesh, unsigned int index)
{
    Vertex vertex{};

    glm::vec3 vector{};
    vector.x = mesh->mVertices[index].x;
    vector.y = mesh->mVertices[index].y;
    vector.z = mesh->mVertices[index].z;
    vertex.Position = vector;

    vector.x = mesh->mNormals[index].x;
    vector.y = mesh->mNormals[index].y;
    vector.z = mesh->mNormals[index].z;
    vertex.Normal = vector;

    if (mesh->mTextureCoords[0])
    {
        glm::vec2 vec{};
        vec.x = mesh->mTextureCoords[0][index].x;
        vec.y = mesh->mTextureCoords[0][index].y;
        vertex.TexCoords = vec;
    }
    else
        vertex.TexCoords = glm::vec2(0.0f, 0.0f);

    return vertex;
}

Texture Model::LoadTexture(aiMaterial* mat, aiTextureType ai_type, TextureType type)
{
    aiString name;
    mat->GetTexture(ai_type, 0, &name);
    std::string path = m_directory + '/' + name.C_Str();
    return Texture(path, type);
}

void Model::Draw(Shader& shader)
{
    for (unsigned int i = 0; i < m_meshes.size(); i++)
        m_meshes[i].Draw(shader);
}
