#pragma once

#include "engine/Texture.h"
#include "engine/Shader.h"
#include "engine/VertexArray.h"

struct Vertex2D
{
	glm::vec2 position;
	glm::vec2 uv;
};

class HUDElement
{
public:
	HUDElement(Texture* image, Shader* shader, float z_depth);
	void Render();
	void SetVisibility(bool is_visible) { is_visible_ = is_visible; }

private:
	Texture* image_;
	Shader* shader_;
	float z_depth_;
	VertexArray* vao_;
	VertexBuffer* vbo_;
	VertexBufferLayout* vb_layout_;
	std::vector<Vertex2D> vertices_;
	bool is_visible_ = true;
};