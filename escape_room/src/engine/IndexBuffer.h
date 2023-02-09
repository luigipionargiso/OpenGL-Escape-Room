#pragma once

class IndexBuffer
{
public:
	IndexBuffer() = default;
	IndexBuffer(const unsigned int* data, unsigned int count);
	~IndexBuffer();

	// move constructor
	IndexBuffer(IndexBuffer&& other) noexcept;
	// move assignment
	IndexBuffer& operator=(IndexBuffer&& other) noexcept;

	// copy constructor
	IndexBuffer(const IndexBuffer& other) = delete;
	// copy assignment
	IndexBuffer& operator=(const IndexBuffer& other) = delete;

	void Bind() const;
	void Unbind() const;

	inline unsigned int getCount() const { return count_; };

private:
	unsigned int id_;
	unsigned int count_;
};