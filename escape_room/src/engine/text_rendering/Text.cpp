#include "Text.h"
#include "engine/Renderer.h"
#include "engine/window/Window.h"

Texture* Text::bitmap_texture_ = nullptr;
Shader* Text::shader_ = nullptr;
VertexArray* Text::vao_ = nullptr;
VertexBuffer* Text::vbo_ = nullptr;
VertexBufferLayout* Text::vb_layout_ = nullptr;

struct Vertex2D
{
    glm::vec2 position;
    glm::vec2 uv;
};

void Text::Init(Texture* bitmap_texture, Shader* shader)
{
    bitmap_texture_ = bitmap_texture;
    shader_ = shader;
    vao_ = new VertexArray();
    vb_layout_ = new VertexBufferLayout();
    vb_layout_->Push<float>(2); // position
    vb_layout_->Push<float>(2); // texture coordinates
}

void Text::Render(const char* text, float x, float y, float size)
{
    unsigned int length = strlen(text);

    size = 32.0 * 2.0 / Window::GetActiveWindow()->GetFrameBufferSize().x;
    // Fill buffers
    std::vector<Vertex2D> vertices;
    for (unsigned int i = 0; i < length; i++)
    {
        glm::vec2 vertex_up_left = glm::vec2(x + i * size, y + size);
        glm::vec2 vertex_up_right = glm::vec2(x + i * size + size, y + size);
        glm::vec2 vertex_down_right = glm::vec2(x + i * size + size, y);
        glm::vec2 vertex_down_left = glm::vec2(x + i * size, y);

        char character = text[i];
        float uv_x = (character % 16) / 16.0f;
        float uv_y = ((character / 16)-2) / 16.0f;

        glm::vec2 uv_up_left = glm::vec2(uv_x, uv_y);
        glm::vec2 uv_up_right = glm::vec2(uv_x + 1.0f / 16.0f, uv_y);
        glm::vec2 uv_down_right = glm::vec2(uv_x + 1.0f / 16.0f, (uv_y + 1.0f / 16.0f));
        glm::vec2 uv_down_left = glm::vec2(uv_x, (uv_y + 1.0f / 16.0f));

        vertices.push_back({ vertex_up_left, uv_up_left });
        vertices.push_back({ vertex_down_left, uv_down_left });
        vertices.push_back({ vertex_up_right, uv_up_right });

        vertices.push_back({ vertex_down_right, uv_down_right });
        vertices.push_back({ vertex_up_right, uv_up_right });
        vertices.push_back({ vertex_down_left, uv_down_left });
    }

    if (vbo_) delete vbo_;

    unsigned int vbo_size = vertices.size() * sizeof(float) * 4;
    vbo_ = new VertexBuffer(&vertices[0], vbo_size);
    vao_->AddBuffer(*vbo_, *vb_layout_);
    
    shader_->Bind();
    bitmap_texture_->Bind();
    shader_->setUniform1i("u_text_texture", 0);

    Renderer::Draw(*vao_, *shader_);
}

void Text::Clear()
{
    if (bitmap_texture_) delete(bitmap_texture_);
    if (shader_) delete(shader_);
    /* to do */
}
