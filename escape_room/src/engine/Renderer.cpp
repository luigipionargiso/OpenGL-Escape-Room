#include "Renderer.h"
#include "GL/glew.h"

void Renderer::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::Draw(const VertexArray& va, const Shader& shader)
{
	shader.Bind();
	va.Bind();
	glDrawArrays(GL_TRIANGLES, 0, va.GetSize());
}

void Renderer::DrawIndexed(const VertexArray& va, const Shader& shader)
{
	shader.Bind();
	va.Bind();

	glDrawElements(GL_TRIANGLES, va.GetIndicesCount(), GL_UNSIGNED_INT, nullptr);
}
