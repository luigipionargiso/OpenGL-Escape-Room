#include "Window.h"
#include "Callbacks.h"
#include <iostream>
#include <tuple>
#include "vendor/stb_image/stb_image.h"

GLdouble Window::deltaTime = 0.0;
GLdouble Window::lastFrame = 0.0;

Window::Window(GLuint width, GLuint height, std::string window_name)
    :m_Window(nullptr), m_fullscreen(false)
{
    if (!glfwInit())
    {
        std::cerr << "Could not initialize GLFW" << '\n';
        exit(EXIT_FAILURE);
    }

    #ifdef DEBUG
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
    #endif // DEBUG

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    //glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 4);

    m_Window = glfwCreateWindow(width, height, window_name.c_str(), NULL, NULL);
    if (!m_Window) {
        std::cerr << "Could not create a window" << '\n';
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    /* set some callbacks from Callbacks.h */
    glfwSetFramebufferSizeCallback(m_Window, framebuffer_size_callback);
    glfwSetScrollCallback(m_Window, scroll_callback);
}

bool Window::GetKey(int key) const
{
    return glfwGetKey(m_Window, key) == GLFW_PRESS;
}

bool Window::GetMouseButton(int key) const
{
    return glfwGetMouseButton(m_Window, key) == GLFW_PRESS;
}

void Window::SetWindowIcon(std::string icon_filepath) const
{
    GLint width, height;
    GLubyte* image = stbi_load(icon_filepath.c_str(), &width, &height, nullptr, 4);
    GLFWimage icon = GLFWimage{ width, height, image };
    glfwSetWindowIcon(m_Window, 1, &icon);
}


void Window::ToggleFullscreen()
{
    //TO DO
   /* static GLint width, height, xpos, ypos;
    if (m_fullscreen)
    {
        glfwSetWindowMonitor(m_Window, NULL, xpos, ypos, width, height, GLFW_DONT_CARE);
    }
    else
    {
        glfwGetWindowSize(m_Window, &width, &height);
        glfwGetWindowPos(m_Window, &xpos, &ypos);
        glfwSetWindowMonitor(m_Window, glfwGetPrimaryMonitor(), xpos, ypos, width, height, GLFW_DONT_CARE);
    }*/
}

Point2D Window::GetCursorPosition() const
{
    GLdouble xpos, ypos;
    glfwGetCursorPos(m_Window, &xpos, &ypos);
    return Point2D{ xpos, ypos };
}

bool Window::IsHovered() const
{
    return glfwGetWindowAttrib(m_Window, GLFW_HOVERED);
}

std::tuple<GLint, GLint> Window::GetFrameBufferSize() const
{
    GLint width, height;
    glfwGetFramebufferSize(m_Window, &width, &height);
    return std::make_tuple(width, height);
}

void Window::SwapFrameBuffer()
{
    GLdouble currentFrame = GetTime();
    Window::deltaTime = currentFrame - Window::lastFrame;
    Window::lastFrame = currentFrame;

    glfwSwapBuffers(m_Window);
}
