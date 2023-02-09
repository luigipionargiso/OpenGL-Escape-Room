#include "Texture.h"
#include <iostream>
#include "GL/glew.h"
#include "vendor/stb_image/stb_image.h"

Texture::Texture(const std::string& path, TextureType type)
	:id_(0), type_(type), filename_(path),
	local_buffer_(nullptr), width_(0), height_(0), bpp_(0)
{
	stbi_set_flip_vertically_on_load(1);
	local_buffer_ = stbi_load(path.c_str(), &width_, &height_, &bpp_, 4);

	if (local_buffer_)
	{
		glGenTextures(1, &id_);
		glBindTexture(GL_TEXTURE_2D, id_);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width_, height_, 0, GL_RGBA, GL_UNSIGNED_BYTE, local_buffer_);
		Unbind();
		stbi_image_free(local_buffer_);
	}
	else
	{
		std::cerr << "Failed to load image texture (" 
			<< path
			<< ") "
			<< '\n'
			<< stbi_failure_reason()
			<< '\n';
	}
}

Texture::~Texture()
{
	glDeleteTextures(1, &id_);
}

Texture::Texture(Texture&& other) noexcept
	:id_(other.id_),
	type_(other.type_),
	filename_(other.filename_),
	local_buffer_(other.local_buffer_),
	width_(other.width_),
	height_(other.height_),
	bpp_(other.bpp_)
{
	other.id_ = 0;
}

Texture& Texture::operator=(Texture&& other) noexcept
{
	if (this != &other)
	{
		id_ = other.id_;
		type_ = other.type_;
		filename_ = other.filename_;
		local_buffer_ = other.local_buffer_;
		width_ = other.width_;
		height_ = other.height_;
		bpp_ = other.bpp_;

		other.id_ = 0;
	}
	return *this;
}

void Texture::Bind(unsigned int slot) const
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, id_);
}

void Texture::Unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
