#pragma once

#include <string>
#include <unordered_map>
#include "vendor/glm/glm.hpp"
#include "vendor/glm/gtc/type_ptr.hpp"

class Shader
{
public:
	Shader(const std::string& vertex_shader_filename, const std::string& fragment_shader_filename);
	~Shader();

	void Bind() const;
	void Unbind() const;

	void setUniform1i(const std::string& name, int value);
	void setUniform1f(const std::string& name, float value);
	void setUniform4f(const std::string& name, float f1, float f2, float f3, float f4);
	void setUniformMat4f(const std::string& name, const glm::mat4& matrix);
	void setUniform3fv(const std::string& name, const glm::vec3& vector);

private:
	unsigned int id_;
	mutable std::unordered_map<std::string, int> uniform_location_cache_;

	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	unsigned int CompileShader(const std::string& source, unsigned int type);
	std::string ParseShader(const std::string& filepath);
	int GetUniformLocation(const std::string& name) const;
};