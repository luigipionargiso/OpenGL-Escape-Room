#pragma once

#include <iostream>
#include "GL/glew.h"
#include "GLFW/glfw3.h"

void GLAPIENTRY errorOccurredGL(GLenum source,
	GLenum type,
	GLuint id,
	GLenum severity,
	GLsizei length,
	const GLchar* message,
	const void* userParam)
{
	printf("Message from OpenGL:\nSource: 0x%x\nType: 0x%x\n"
		"Id: 0x%x\nSeverity: 0x%x\n", source, type, id, severity);
	printf("%s\n", message);
	exit(-1); // without exit(), OpenGL will constantly print the error message
}

void errorOccurredGLFW(int error, const char* description)
{
	printf("GLFW Error %d: %s\n", error, description);
}


namespace Debug
{
	void EnableDebug()
	{
		glEnable(GL_DEBUG_OUTPUT);
		glDebugMessageCallback(errorOccurredGL, nullptr);

		glfwSetErrorCallback(errorOccurredGLFW);
	}

	void PrintVersionsOnConsole()
	{
		std::cout << "GL_VERSION: " << glGetString(GL_VERSION) << '\n';
		std::cout << "GL_VENDOR: " << glGetString(GL_VENDOR) << '\n';
		std::cout << "GL_RENDERER: " << glGetString(GL_RENDERER) << '\n';
		std::cout << "GLEW_VERSION: " << glewGetString(GLEW_VERSION) << '\n';
		std::cout << "GL_SHADING_LANGUAGE_VERSION: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << '\n';
		std::cout << "GLFW_VERSION: " << glfwGetVersionString() << '\n';
	}
}