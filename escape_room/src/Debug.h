#pragma once

#include <iostream>
#include "GL/glew.h"
#include "GLFW/glfw3.h"

using namespace std;

void GLAPIENTRY errorOccurredGL(GLenum source,
    GLenum type,
    GLuint id,
    GLenum severity,
    GLsizei length,
    const GLchar* message,
    const void* userParam)
{
    cerr << "\n <-- Message from OpenGL -->" << endl;

    cerr << "Message: " << message << endl;

    cerr << "Type: ";
    switch (type) {
        case GL_DEBUG_TYPE_ERROR:
            cerr << "ERROR";
            break;
    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
            cerr << "DEPRECATED_BEHAVIOR";
            break;
    case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
            cerr << "UNDEFINED_BEHAVIOR";
            break;
    case GL_DEBUG_TYPE_PORTABILITY:
            cerr << "PORTABILITY";
            break;
    case GL_DEBUG_TYPE_PERFORMANCE:
            cerr << "PERFORMANCE";
            break;
    case GL_DEBUG_TYPE_OTHER:
            cerr << "OTHER";
            break;
    }
    cerr << endl;

    cerr << "ID: " << id << endl;

    cerr << "Severity: ";
    switch (severity) {
        case GL_DEBUG_SEVERITY_LOW:
            cerr << "LOW";
            break;
        case GL_DEBUG_SEVERITY_MEDIUM:
            cerr << "MEDIUM";
            break;
        case GL_DEBUG_SEVERITY_HIGH:
            cerr << "HIGH";
            break;
        }
    cerr << endl;
    cerr << "<-- Message end -->\n" << endl;
}

void errorOccurredGLFW(int error, const char* description)
{
    cerr << "GLFW Error " << error << ": " << description << '\n';
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