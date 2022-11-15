#include "VertexArray.h"
#include "GL/glew.h"

VertexArray::VertexArray()
	:m_bufferSize(0), m_indicesCount(0)
{
	glGenVertexArrays(1, &m_rendererID);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_rendererID);
}

VertexArray::VertexArray(VertexArray&& other) noexcept
	:m_rendererID(other.m_rendererID),
	m_bufferSize(other.m_bufferSize),
	m_indicesCount(other.m_indicesCount)
{
	other.m_rendererID = 0;
	other.m_bufferSize = 0;
	other.m_indicesCount = 0;
}

VertexArray& VertexArray::operator=(VertexArray&& other) noexcept
{
	if (this != &other)
	{
		m_rendererID = other.m_rendererID;
		m_bufferSize = other.m_bufferSize;
		m_indicesCount = other.m_indicesCount;

		other.m_rendererID = 0;
		other.m_bufferSize = 0;
		other.m_indicesCount = 0;
	}
	return *this;
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
	Bind();
	vb.Bind();
	const auto& elements = layout.getElements();
	size_t offset = 0;
	for (unsigned int i = 0; i < elements.size(); i++)
	{
		const auto& element = elements[i];
		glVertexAttribPointer(i, element.count, element.type,
			element.normalized, layout.getStride(), (const void*)offset);
		glEnableVertexAttribArray(i);
		offset += (size_t)element.count * VertexBufferElement::GetSizeOfType(element.type);
	}
	m_bufferSize = vb.GetSize();
}

void VertexArray::AddIndexBuffer(const IndexBuffer& ib)
{
	ib.Bind();
	m_indicesCount = ib.getCount();
}

void VertexArray::Bind() const
{
	glBindVertexArray(m_rendererID);
}

void VertexArray::Unbind() const
{
	glBindVertexArray(0);
}
