#include "VertexArray.h"
#include "GL/glew.h"

VertexArray::VertexArray()
	:buffer_size_(0), indices_count_(0)
{
	glGenVertexArrays(1, &id_);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &id_);
}

VertexArray::VertexArray(VertexArray&& other) noexcept
	:id_(other.id_),
	buffer_size_(other.buffer_size_),
	indices_count_(other.indices_count_)
{
	other.id_ = 0;
	other.buffer_size_ = 0;
	other.indices_count_ = 0;
}

VertexArray& VertexArray::operator=(VertexArray&& other) noexcept
{
	if (this != &other)
	{
		id_ = other.id_;
		buffer_size_ = other.buffer_size_;
		indices_count_ = other.indices_count_;

		other.id_ = 0;
		other.buffer_size_ = 0;
		other.indices_count_ = 0;
	}
	return *this;
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
	Bind();
	vb.Bind();
	const auto& elements = layout.GetElements();
	size_t offset = 0;
	for (unsigned int i = 0; i < elements.size(); i++)
	{
		const auto& element = elements[i];
		glVertexAttribPointer(i, element.count, element.type,
			element.normalized, layout.GetStride(), (const void*)offset);
		glEnableVertexAttribArray(i);
		offset += (size_t)element.count * VertexBufferElement::GetSizeOfType(element.type);
	}
	buffer_size_ = vb.GetSize();
}

void VertexArray::AddIndexBuffer(const IndexBuffer& ib)
{
	// Bind(); ??
	ib.Bind();
	indices_count_ = ib.getCount();
}

void VertexArray::Bind() const
{
	glBindVertexArray(id_);
}

void VertexArray::Unbind() const
{
	glBindVertexArray(0);
}
