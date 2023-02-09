#pragma once

#include <vector>

#include "engine/VertexArray.h"
#include "engine/VertexBuffer.h"
#include "engine/IndexBuffer.h"
#include "engine/VertexBufferLayout.h"
#include "engine/Shader.h"
#include "engine/Texture.h"
#include "engine/Renderer.h"
#include "vendor/glm/glm.hpp"

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texture_coords;
	glm::vec3 tangent;
};

class Mesh
{
public:
	Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture> textures);
	~Mesh() = default;

	// move constructor
	Mesh(Mesh&& other) noexcept = default;
	// move assignment
	Mesh& operator=(Mesh&& other) noexcept = default;

	void Draw(Shader& shader) const;

private:
	VertexArray vao_;
	VertexBuffer vbo_;
	VertexBufferLayout vb_layout_;
	IndexBuffer ibo_;
	std::vector<Vertex> vertices_;
	std::vector<GLuint> indices_;
	std::vector<Texture> textures_;
};