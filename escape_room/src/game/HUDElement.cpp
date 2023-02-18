#include "HUDElement.h"
#include "engine/Renderer.h"

HUDElement::HUDElement(Texture* image, Shader* shader, float z_depth)
{
    image_ = image;
    shader_ = shader;
    z_depth_ = z_depth;

    vao_ = new VertexArray();
    vb_layout_ = new VertexBufferLayout();
    vb_layout_->Push<float>(2); // position
    vb_layout_->Push<float>(2); // texture coordinates

    glm::vec2 vertex_up_left = glm::vec2(-1.0f, 1.0f);
    glm::vec2 vertex_up_right = glm::vec2(1.0f, 1.0f);
    glm::vec2 vertex_down_right = glm::vec2(1.0f, -1.0f);
    glm::vec2 vertex_down_left = glm::vec2(-1.0f, -1.0f);

    glm::vec2 uv_up_left = glm::vec2(0.0f, 1.0f);
    glm::vec2 uv_up_right = glm::vec2(1.0f, 1.0f);
    glm::vec2 uv_down_right = glm::vec2(1.0f, 0.0f);
    glm::vec2 uv_down_left = glm::vec2(0.0f, 0.0f);

    vertices_.push_back({ vertex_up_left, uv_up_left });
    vertices_.push_back({ vertex_down_left, uv_down_left });
    vertices_.push_back({ vertex_up_right, uv_up_right });

    vertices_.push_back({ vertex_down_right, uv_down_right });
    vertices_.push_back({ vertex_up_right, uv_up_right });
    vertices_.push_back({ vertex_down_left, uv_down_left });

    unsigned int vbo_size = vertices_.size() * sizeof(float) * 4;
    vbo_ = new VertexBuffer(&vertices_[0], vbo_size);

    vao_->AddBuffer(*vbo_, *vb_layout_);
}

void HUDElement::Render()
{
    shader_->Bind();
    image_->Bind();
    shader_->setUniform1i("u_image", 0);
    shader_->setUniform1f("u_depth", z_depth_);
    Renderer::Draw(*vao_, *shader_);
}
