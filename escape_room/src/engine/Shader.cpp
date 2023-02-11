#include "Shader.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "GL/glew.h"

Shader::Shader(const std::string& vertex_shader_filename, const std::string& fragment_shader_filename)
	:id_(0)
{
	std::string vertex_shader = ParseShader(vertex_shader_filename);
	std::string fragment_shader = ParseShader(fragment_shader_filename);
	id_ = CreateShader(vertex_shader, fragment_shader);
}

Shader::~Shader()
{
	glDeleteProgram(id_);
}

void Shader::Bind() const
{
	glUseProgram(id_);
}

void Shader::Unbind() const
{
	glUseProgram(0);
}

void Shader::setUniform1i(const std::string& name, int value)
{
	Bind();
	glUniform1i(GetUniformLocation(name), value);
}

void Shader::setUniform1f(const std::string& name, float value)
{
	Bind();
	glUniform1f(GetUniformLocation(name), value);
}

void Shader::setUniform4f(const std::string& name, float f1, float f2, float f3, float f4)
{
	Bind();
	glUniform4f(GetUniformLocation(name), f1, f2, f3, f4);
}

void Shader::setUniformMat4f(const std::string& name, const glm::mat4& matrix)
{
	Bind();
	glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::setUniform3fv(const std::string& name, const glm::vec3& vector)
{
	Bind();
	glUniform3fv(GetUniformLocation(name), 1, glm::value_ptr(vector));
}

unsigned int Shader::CreateShader(const std::string& vertex_shader, const std::string& fragment_shader)
{
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(vertex_shader, GL_VERTEX_SHADER);
	unsigned int fs = CompileShader(fragment_shader, GL_FRAGMENT_SHADER);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}

unsigned int Shader::CompileShader(const std::string& source, unsigned int type)
{
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE) {
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)_malloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);
		std::cout << "Failed to compile " <<
			(type == GL_VERTEX_SHADER ? "vertex" : "fragment")
			<< " shader!" << std::endl;
		std::cout << message << std::endl;

		glDeleteShader(id);
		return 0;
	}

	return id;
}

std::string Shader::ParseShader(const std::string& filepath)
{
	std::ifstream stream(filepath);
	std::stringstream source;

	if (!stream.is_open()) {
		std::cerr << "Could not open the shader source file '"
			<< filepath << "'" << std::endl;
		exit(EXIT_FAILURE);
	}

	source << stream.rdbuf();
	return source.str();
}

int Shader::GetUniformLocation(const std::string& name) const
{
	auto locationSearch = uniform_location_cache_.find(name);
	if (locationSearch != uniform_location_cache_.end())
		return locationSearch->second;

	int location = glGetUniformLocation(id_, name.c_str());
	if (location == -1)
		std::cerr << "Warning: uniform " << name << " doesn't exist!" << std::endl;

	uniform_location_cache_[name] = location;

	return location;
}