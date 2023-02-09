#include "IndexBuffer.h"
#include "GL/glew.h"

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count)
    :count_(count)
{
    glGenBuffers(1, &id_);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer()
{
    glDeleteBuffers(1, &id_);
}

IndexBuffer::IndexBuffer(IndexBuffer&& other) noexcept
    :id_(other.id_),
    count_(other.count_)
{
    other.id_ = 0;
    other.count_ = 0;
}

IndexBuffer& IndexBuffer::operator=(IndexBuffer&& other) noexcept
{
    if (this != &other)
    {
        id_ = other.id_;
        count_ = other.count_;

        other.id_ = 0;
        other.count_ = 0;
    }
    return *this;
}

void IndexBuffer::Bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_);
}

void IndexBuffer::Unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
