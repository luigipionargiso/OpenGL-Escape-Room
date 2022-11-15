#include "Mesh.h"
#include <iostream>

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture> textures)
	:m_vertices(std::move(vertices)),
	m_indices(std::move(indices)),
	m_textures(std::move(textures)),
	m_VAO(VertexArray())
{
	unsigned int vbo_size = m_vertices.size() * sizeof(float) * 8;
	m_VBO = VertexBuffer(&m_vertices[0], vbo_size);
	m_IBO = IndexBuffer(&m_indices[0], m_indices.size());

	m_layout.Push<float>(3); //Position
	m_layout.Push<float>(3); //Normal
	m_layout.Push<float>(2); //TexCoord

	m_VAO.AddBuffer(m_VBO, m_layout);
	m_VAO.AddIndexBuffer(m_IBO);

	for (Vertex& v : m_vertices)
		std::cout << v.Position.x << " " << v.Position.y << " " << v.Position.z
		<< " Normal: " << v.Normal.x << " " << v.Normal.y << " " << v.Normal.z << '\n';

	m_VAO.Unbind();
}

void Mesh::Draw(Shader& shader)
{
	shader.Bind();

	for (unsigned int i = 0; i < m_textures.size(); i++)
	{
		m_textures[i].Bind(i);
		switch (m_textures[i].GetType())
		{
		case DIFFUSE:
			shader.setUniform1i("u_Material.diffuse", i);
			break;
		case SPECULAR:
			shader.setUniform1i("u_Material.specular", i);
			break;
		default:
			break;
		}
	}

	Renderer::DrawIndexed(m_VAO, shader);
	m_VAO.Unbind();
	shader.Unbind();
}

//void Mesh::Draw(Shader& shader)
//{
//	shader.Bind();
//
//	unsigned int diffuseNr = 0;
//	unsigned int specularNr = 0;
//	for (unsigned int i = 0; i < m_textures.size(); i++)
//	{
//		m_textures[i].Bind(i);
//		std::string number;
//		switch (m_textures[i].GetType())
//		{
//		case DIFFUSE:
//			number = std::to_string(diffuseNr++);
//			shader.setUniform1i(("u_Material.diffuse" + number).c_str(), i);
//			break;
//		case SPECULAR:
//			number = std::to_string(specularNr++);
//			shader.setUniform1i(("u_Material.specular" + number).c_str(), i);
//			break;
//		default:
//			break;
//		}
//	}
// 	glActiveTexture(GL_TEXTURE0);
//	glBindTexture(GL_TEXTURE_2D, 0);
//
//	Renderer::DrawIndexed(m_VAO, shader);
//	m_VAO.Unbind();
//	shader.Unbind();
//}
