#pragma once

#include "engine/Texture.h"
#include "engine/Shader.h"
#include "engine/VertexArray.h"

class Text
{
public:
	static void Init(Texture* bitmap_texture, Shader* shader_);
	static void Render(const char* text, float x, float y, float size);
	static void Clear();

private:
	static Texture* bitmap_texture_;
	static Shader* shader_;
	static VertexArray* vao_;
	static VertexBuffer* vbo_;
	static VertexBufferLayout* vb_layout_;
};