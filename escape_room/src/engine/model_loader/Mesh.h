#pragma once

#include <vector>

#include "engine/VertexArray.h"
#include "engine/VertexBuffer.h"
#include "engine/IndexBuffer.h"
#include "engine/VertexBufferLayout.h"
#include "engine/Shader.h"
#include "vendor/glm/glm.hpp"
#include "engine/Texture.h"
#include "engine/Renderer.h"

struct Vertex
{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};

class Mesh
{
private:
	VertexArray m_VAO;
	VertexBuffer m_VBO;
	VertexBufferLayout m_layout;
	IndexBuffer m_IBO;
public:
	std::vector<Vertex> m_vertices;
	std::vector<GLuint> m_indices;
	std::vector<Texture> m_textures;

	Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture> textures);
	~Mesh() = default;

	Mesh(Mesh&& other) noexcept = default;	// move constructor
	Mesh& operator=(Mesh&& other) noexcept = default;	// move assignment

	void Draw(Shader& shader);
};