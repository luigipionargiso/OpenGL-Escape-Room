#pragma once

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexBufferLayout.h"

class VertexArray
{
public:
	VertexArray();
	~VertexArray();

	// move constructor
	VertexArray(VertexArray&& other) noexcept;
	// move assignment
	VertexArray& operator=(VertexArray&& other) noexcept;

	// copy constructor
	VertexArray(const VertexArray& other) = delete;
	// copy assignment
	VertexArray& operator=(const VertexArray& other) = delete;

	void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
	void AddIndexBuffer(const IndexBuffer& ib);
	void Bind() const;
	void Unbind() const;

	inline unsigned int GetSize() const { return buffer_size_; }
	inline unsigned int GetIndicesCount() const { return indices_count_; }

private:
	unsigned int id_;
	unsigned int buffer_size_;
	unsigned int indices_count_;
};
