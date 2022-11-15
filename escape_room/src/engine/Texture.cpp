#include "Texture.h"
#include <iostream>
#include "GL/glew.h"
#include "vendor/stb_image/stb_image.h"

Texture::Texture(const std::string& path, TextureType type)
	:m_rendererID(0), m_type(type), m_filePath(path),
	m_localBuffer(nullptr), m_width(0), m_height(0), m_bpp(0)
{
	stbi_set_flip_vertically_on_load(1);
	m_localBuffer = stbi_load(path.c_str(), &m_width, &m_height, &m_bpp, 4);

	if (m_localBuffer)
	{
		glGenTextures(1, &m_rendererID);
		glBindTexture(GL_TEXTURE_2D, m_rendererID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_localBuffer);
		Unbind();
		stbi_image_free(m_localBuffer);
	}
	else
	{
		std::cerr << "Failed to load image texture: " << stbi_failure_reason() << '\n';
	}
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_rendererID);
}

Texture::Texture(Texture&& other) noexcept
	:m_rendererID(other.m_rendererID),
	m_type(other.m_type),
	m_filePath(other.m_filePath),
	m_localBuffer(other.m_localBuffer),
	m_width(other.m_width),
	m_height(other.m_height),
	m_bpp(other.m_bpp)
{
	other.m_rendererID = 0;
}

Texture& Texture::operator=(Texture&& other) noexcept
{
	if (this != &other)
	{
		m_rendererID = other.m_rendererID;
		m_type = other.m_type;
		m_filePath = other.m_filePath;
		m_localBuffer = other.m_localBuffer;
		m_width = other.m_width;
		m_height = other.m_height;
		m_bpp = other.m_bpp;

		other.m_rendererID = 0;
	}
	return *this;
}

void Texture::Bind(unsigned int slot) const
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, m_rendererID);
}

void Texture::Unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
