#pragma once

#include <string>

enum TextureType {DIFFUSE, SPECULAR, NORMAL};

class Texture
{
private:
	unsigned int m_rendererID;
	TextureType m_type;
	std::string m_filePath;
	unsigned char* m_localBuffer;
	int m_width, m_height, m_bpp;
public:
	Texture(const std::string& path, TextureType type);
	~Texture();

	Texture(Texture&& other) noexcept;	// move constructor
	Texture& operator=(Texture&& other) noexcept;	// move assignment

	Texture(const Texture& other) = delete;	// copy constructor
	Texture& operator=(const Texture& other) = delete; // copy assignment

	void Bind(unsigned int slot = 0) const;
	void Unbind() const;

	inline int GetWidth() const { return m_width;  }
	inline int GetHeight() const { return m_height;  }
	inline TextureType GetType() const { return m_type; }
};