#pragma once

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexBufferLayout.h"

class VertexArray
{
private:
	unsigned int m_rendererID;
	unsigned int m_bufferSize;
	unsigned int m_indicesCount;

public:
	VertexArray();
	~VertexArray();

	VertexArray(VertexArray&& other) noexcept;	// move constructor
	VertexArray& operator=(VertexArray&& other) noexcept;	// move assignment

	VertexArray(const VertexArray& other) = delete;	// copy constructor
	VertexArray& operator=(const VertexArray& other) = delete; // copy assignment

	void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
	void AddIndexBuffer(const IndexBuffer& ib);
	void Bind() const;
	void Unbind() const;
	unsigned int GetSize() const { return m_bufferSize; }
	unsigned int GetIndicesCount() const { return m_indicesCount; }
};
