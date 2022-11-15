#pragma once

class IndexBuffer
{
private:
	unsigned int m_rendererID;
	unsigned int m_count;
public:
	IndexBuffer() = default;
	IndexBuffer(const unsigned int* data, unsigned int count);
	~IndexBuffer();

	IndexBuffer(IndexBuffer&& other) noexcept;	// move constructor
	IndexBuffer& operator=(IndexBuffer&& other) noexcept;	// move assignment

	IndexBuffer(const IndexBuffer& other) = delete;	// copy constructor
	IndexBuffer& operator=(const IndexBuffer& other) = delete; // copy assignment

	void Bind() const;
	void Unbind() const;

	inline unsigned int getCount() const { return m_count; };
};