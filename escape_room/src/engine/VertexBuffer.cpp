#include "VertexBuffer.h"
#include "GL/glew.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size)
    :m_size(size)
{
    glGenBuffers(1, &m_rendererID);
    glBindBuffer(GL_ARRAY_BUFFER, m_rendererID);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &m_rendererID);
}

VertexBuffer::VertexBuffer(VertexBuffer&& other) noexcept
	:m_rendererID(other.m_rendererID),
	m_size(other.m_size)
{
	other.m_rendererID = 0;
	other.m_size = 0;
}

VertexBuffer& VertexBuffer::operator=(VertexBuffer&& other) noexcept
{
	if (this != &other)
	{
		m_rendererID = other.m_rendererID;
		m_size = other.m_size;

		other.m_rendererID = 0;
		other.m_size = 0;
	}
	return *this;
}

void VertexBuffer::Bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_rendererID);
}

void VertexBuffer::Unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
