#pragma once

#include "GL/glew.h"
#include "GLFW/glfw3.h"

extern GLdouble scroll_offset;

void framebuffer_size_callback(GLFWwindow* window, GLint width, GLint height)
{
    glViewport(0, 0, height*16/9, height);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    scroll_offset = yoffset;
}