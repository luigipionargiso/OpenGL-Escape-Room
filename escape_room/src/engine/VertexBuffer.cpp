#include "VertexBuffer.h"
#include "GL/glew.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size)
    :size_(size)
{
    glGenBuffers(1, &id_);
    glBindBuffer(GL_ARRAY_BUFFER, id_);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &id_);
}

VertexBuffer::VertexBuffer(VertexBuffer&& other) noexcept
	:id_(other.id_),
	size_(other.size_)
{
	other.id_ = 0;
	other.size_ = 0;
}

VertexBuffer& VertexBuffer::operator=(VertexBuffer&& other) noexcept
{
	if (this != &other)
	{
		id_ = other.id_;
		size_ = other.size_;

		other.id_ = 0;
		other.size_ = 0;
	}
	return *this;
}

void VertexBuffer::Bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, id_);
}

void VertexBuffer::Unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
