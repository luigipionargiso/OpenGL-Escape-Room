#include "Shader.h"
#include "Renderer.h"

#include <iostream>
#include <fstream>
#include <sstream>

Shader::Shader(const std::string& vertex_shader_filename, const std::string& fragment_shader_filename)
	:m_RendererID(0)
{
	std::string vertexShader = ParseShader("res/shaders/basic.vert");
	std::string fragmentShader = ParseShader("res/shaders/basic.frag");
	m_RendererID = CreateShader(vertexShader, fragmentShader);
}

Shader::~Shader()
{
	glDeleteProgram(m_RendererID);
}

void Shader::Bind() const
{
	glUseProgram(m_RendererID);
}

void Shader::Unbind() const
{
	glUseProgram(0);
}

void Shader::setUniform1i(const std::string& name, int value)
{
	glUniform1i(GetUniformLocation(name), value);
}

void Shader::setUniform1f(const std::string& name, float value)
{
	glUniform1i(GetUniformLocation(name), value);
}

void Shader::setUniform4f(const std::string& name, float f1, float f2, float f3, float f4)
{
	glUniform4f(GetUniformLocation(name), f1, f2, f3, f4);
}

void Shader::setUniformMat4f(const std::string& name, const glm::mat4& matrix)
{
	glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]);
}

unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(vertexShader, GL_VERTEX_SHADER);
	unsigned int fs = CompileShader(fragmentShader, GL_FRAGMENT_SHADER);

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
		char* message = (char*)alloca(length * sizeof(char));
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
	auto locationSearch = m_UniformLocationCache.find(name);
	if (locationSearch != m_UniformLocationCache.end())
		return locationSearch->second;

	int location = glGetUniformLocation(m_RendererID, name.c_str());
	if (location == -1)
		std::cerr << "Warning: uniform " << name << " doesn't exist!" << std::endl;

	m_UniformLocationCache[name] = location;

	return location;
}