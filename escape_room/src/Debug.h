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
    cout << "\n <-- Message from OpenGL -->" << endl;

    cout << "Message: " << message << endl;

    cout << "Type: ";
    switch (type) {
        case GL_DEBUG_TYPE_ERROR:
            cout << "ERROR";
            break;
    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
            cout << "DEPRECATED_BEHAVIOR";
            break;
    case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
            cout << "UNDEFINED_BEHAVIOR";
            break;
    case GL_DEBUG_TYPE_PORTABILITY:
            cout << "PORTABILITY";
            break;
    case GL_DEBUG_TYPE_PERFORMANCE:
            cout << "PERFORMANCE";
            break;
    case GL_DEBUG_TYPE_OTHER:
            cout << "OTHER";
            break;
    }
    cout << endl;

    cout << "ID: " << id << endl;

    cout << "Severity: ";
    switch (severity) {
        case GL_DEBUG_SEVERITY_LOW:
            cout << "LOW";
            break;
        case GL_DEBUG_SEVERITY_MEDIUM:
            cout << "MEDIUM";
            break;
        case GL_DEBUG_SEVERITY_HIGH:
            cout << "HIGH";
            break;
        }
    cout << endl;
    cout << "<-- Message end -->\n" << endl;
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