#pragma once

#include "VertexArray.h"
#include "Shader.h"

class Renderer {
public:
	static void Clear();
	static void Draw(const VertexArray& va, const Shader& shader);
	static void DrawIndexed(const VertexArray& va, const Shader& shader);
};