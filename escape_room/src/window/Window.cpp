#include "Window.h"
#include "../vendor/stb_image/stb_image.h"
#include <iostream>
#include <tuple>

GLdouble Window::m_deltaTime = 0.0;
GLdouble Window::m_lastFrame = 0.0;

Window::Window(GLuint width, GLuint height, std::string window_name)
    :m_Window(nullptr), fullscreen(false)
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

    m_Window = glfwCreateWindow(width, height, window_name.c_str(), NULL, NULL);
    if (!m_Window) {
        std::cerr << "Could not create a window" << '\n';
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
}

Window::~Window()
{
}

void Window::MakeCurrent() const
{
    glfwMakeContextCurrent(m_Window);
}

bool Window::IsOpen() const
{
    return !glfwWindowShouldClose(m_Window);
}

void Window::Close() const
{
    glfwWindowShouldClose(m_Window);
}

void Window::SetWindowIcon(std::string icon_filepath) const
{
    GLint width, height;
    GLubyte* image = stbi_load(icon_filepath.c_str(), &width, &height, nullptr, 4);
    GLFWimage icon = GLFWimage{ width, height, image };
    glfwSetWindowIcon(m_Window, 1, &icon);
}

bool Window::GetKey(int key) const
{
    return glfwGetKey(m_Window, key) == GLFW_PRESS;
}

bool Window::GetMouseButton(int key) const
{
    return glfwGetMouseButton(m_Window, key) == GLFW_PRESS;
}

void Window::ToggleFullscreen()
{
    //TO DO
    static GLint width, height, xpos, ypos;
    if (fullscreen)
    {
        glfwSetWindowMonitor(m_Window, NULL, xpos, ypos, width, height, GLFW_DONT_CARE);
    }
    else
    {
        glfwGetWindowSize(m_Window, &width, &height);
        glfwGetWindowPos(m_Window, &xpos, &ypos);
        glfwSetWindowMonitor(m_Window, glfwGetPrimaryMonitor(), xpos, ypos, width, height, GLFW_DONT_CARE);
    }
}

void Window::SetKeyCallback(function keyboard_callback) const
{
    glfwSetKeyCallback(m_Window, (GLFWkeyfun)keyboard_callback);
}

void Window::SetWindowSizeCallback(function resize_callback) const
{
    glfwSetWindowSizeCallback(m_Window, (GLFWwindowsizefun)resize_callback);
}

void Window::SetFrameBufferSizeCallback(function frame_resize_callback) const
{
    glfwSetFramebufferSizeCallback(m_Window, (GLFWframebuffersizefun)frame_resize_callback);
}

Point2D Window::GetCursorPosition() const
{
    double xpos, ypos;
    glfwGetCursorPos(m_Window, &xpos, &ypos);
    return Point2D{ (float)xpos, (float)ypos };
}

bool Window::isHovered() const
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
    m_deltaTime = currentFrame - m_lastFrame;
    m_lastFrame = currentFrame;

    glfwSwapBuffers(m_Window);
}

void Window::SetSwapInterval(GLint interval)
{
    glfwSwapInterval(interval);
}

void Window::PollEvents()
{
    glfwPollEvents();
}

void Window::WaitEvents()
{
    glfwWaitEvents();
}

void Window::WaitEventsTimeout(GLdouble timeout)
{
    glfwWaitEventsTimeout(timeout);
}

void Window::CloseAllWindows()
{
    glfwTerminate();
}
