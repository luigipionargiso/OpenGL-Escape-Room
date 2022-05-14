#pragma once

#include <string>
#include <unordered_map>

#include "vendor/glm/glm.hpp"

class Shader
{
private:
	unsigned int m_RendererID;
	mutable std::unordered_map<std::string, int> m_UniformLocationCache;
public:
	Shader(const std::string& vertex_shader_filename, const std::string& fragment_shader_filename);
	~Shader();

	void Bind() const;
	void Unbind() const;

	void setUniform1i(const std::string& name, int value);
	void setUniform1f(const std::string& name, float value);
	void setUniform4f(const std::string& name, float f1, float f2, float f3, float f4);
	void setUniformMat4f(const std::string& name, const glm::mat4& matrix);

private:
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	unsigned int CompileShader(const std::string& source, unsigned int type);
	std::string ParseShader(const std::string& filepath);
	int GetUniformLocation(const std::string& name) const;
};