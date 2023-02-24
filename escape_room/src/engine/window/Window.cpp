#include "Window.h"
#include <iostream>
#include "vendor/stb_image/stb_image.h"

const Window* Window::active_ = nullptr;

Window::Window(unsigned int width, unsigned int height, std::string name)
    :glfw_pointer_(nullptr), is_fullscreen_(false)
{
#ifdef DEBUG
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
#endif

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);  //require OpenGL 4 or above
    glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 4);

    glfw_pointer_ = glfwCreateWindow(width, height, name.c_str(), NULL, NULL);
    if (!glfw_pointer_) {
        std::cerr << "Could not create the window" << '\n';
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwSetFramebufferSizeCallback(glfw_pointer_, FramebufferSizeCallback);
}


void Window::MakeContextCurrent() const
{
    glfwMakeContextCurrent(glfw_pointer_);
    glfwSwapInterval(1);
    active_ = this;
    glfwSetInputMode(glfw_pointer_, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
}


void Window::SetWindowIcon(std::string filepath) const
{
    GLint width, height;
    auto image = stbi_load(filepath.c_str(), &width, &height, nullptr, 4);
    GLFWimage icon = GLFWimage{ width, height, image };
    glfwSetWindowIcon(glfw_pointer_, 1, &icon);
}


void Window::ToggleFullscreen()
{
    GLFWmonitor* monitor = glfwGetWindowMonitor(glfw_pointer_);

    /* if there's no monitor, get the primary monitor handle */
    if (!monitor)
        monitor = glfwGetPrimaryMonitor();

    if (is_fullscreen_)
    {
        glfwSetWindowMonitor(glfw_pointer_, NULL, 100, 100, 800, 450, 0);
        is_fullscreen_ = false;
        glfwSetInputMode(glfw_pointer_, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    }
    else
    {
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);
        glfwSetWindowMonitor(
            glfw_pointer_,
            monitor,
            0,
            0,
            mode->width,
            mode->height,
            mode->refreshRate
        );
        is_fullscreen_ = true;
        glfwSetInputMode(glfw_pointer_, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
}


glm::vec2 Window::GetFrameBufferSize() const
{
    int width, height;
    glfwGetFramebufferSize(glfw_pointer_, &width, &height);
    return glm::vec2(width, height);
}

void Window::SwapBuffers()
{
    glfwSwapBuffers(glfw_pointer_);
}

void Window::FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, (width * 9) / 16);
}
