#include "Mesh.h"
#include <iostream>

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture> textures)
    :vertices_(std::move(vertices)),
    indices_(std::move(indices)),
    textures_(std::move(textures)),
    vao_(VertexArray())
{
    unsigned int vbo_size = vertices_.size() * sizeof(float) * 11; //magic number
    vbo_ = VertexBuffer(&vertices_[0], vbo_size);
    ibo_ = IndexBuffer(&indices_[0], indices_.size());

    vb_layout_.Push<float>(3); // position
    vb_layout_.Push<float>(3); // normal
    vb_layout_.Push<float>(2); // texture coordinates
    vb_layout_.Push<float>(3); // tangent

    vao_.AddBuffer(vbo_, vb_layout_);
    vao_.AddIndexBuffer(ibo_);

    vao_.Unbind();
}

void Mesh::Draw(Shader& shader) const
{
    shader.Bind();

    for (unsigned int i = 0; i < textures_.size(); i++)
    {
        textures_[i].Bind(i);
        switch (textures_[i].GetType())
        {
        case DIFFUSE:
            shader.setUniform1i("u_Material.diffuse", i);
            break;
        case SPECULAR:
            shader.setUniform1i("u_Material.specular", i);
            break;
        case NORMAL:
            shader.setUniform1i("u_Material.normal", i);
            break;
        default:
            break;
        }
    }

    Renderer::DrawIndexed(vao_, shader);

    vao_.Unbind();
    shader.Unbind();
}
