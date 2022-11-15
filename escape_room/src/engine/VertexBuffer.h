#pragma once

class VertexBuffer
{
private:
	unsigned int m_rendererID;
	unsigned int m_size;
public:
	VertexBuffer() = default;
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();

	VertexBuffer(VertexBuffer&& other) noexcept;	// move constructor
	VertexBuffer& operator=(VertexBuffer&& other) noexcept;	// move assignment

	VertexBuffer(const VertexBuffer& other) = delete;	// copy constructor
	VertexBuffer& operator=(const VertexBuffer& other) = delete; // copy assignment

	void Bind() const;
	void Unbind() const;

	unsigned int GetSize() const { return m_size; }
};