#pragma once

class VertexBuffer
{
public:
	VertexBuffer() = default;
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();

	// move constructor
	VertexBuffer(VertexBuffer&& other) noexcept;
	// move assignment
	VertexBuffer& operator=(VertexBuffer&& other) noexcept;

	// copy constructor
	VertexBuffer(const VertexBuffer& other) = delete;
	// copy assignment
	VertexBuffer& operator=(const VertexBuffer& other) = delete;

	void Bind() const;
	void Unbind() const;

	unsigned int GetSize() const { return size_; }

private:
	unsigned int id_;
	unsigned int size_;
};