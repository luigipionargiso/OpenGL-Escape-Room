#pragma once

#include <string>

enum TextureType
{
	DIFFUSE, SPECULAR, NORMAL
};

class Texture
{
public:
	Texture(const std::string& path, TextureType type);
	~Texture();

	// move constructor
	Texture(Texture&& other) noexcept;
	// move assignment
	Texture& operator=(Texture&& other) noexcept;

	// copy constructor
	Texture(const Texture& other) = delete;
	// copy assignment
	Texture& operator=(const Texture& other) = delete;

	void Bind(unsigned int slot = 0) const;
	void Unbind() const;

	inline TextureType GetType() const { return type_; }
	inline int GetWidth() const { return width_;  }
	inline int GetHeight() const { return height_;  }

private:
	unsigned int id_;
	TextureType type_;
	std::string filename_;
	unsigned char* local_buffer_;
	int width_, height_, bpp_;
};