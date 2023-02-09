#pragma once

#include <string>
#include <tuple>
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "vendor/glm/glm.hpp"

class Window
{
public:
    Window(unsigned int width, unsigned int height, std::string name);
    ~Window() = default;

    inline bool IsOpen() const { return !glfwWindowShouldClose(glfw_pointer_); }
    inline void Close() const { glfwSetWindowShouldClose(glfw_pointer_, GLFW_TRUE); }
    inline bool IsHovered() const { return glfwGetWindowAttrib(glfw_pointer_, GLFW_HOVERED); }
    inline GLFWwindow* GetGLFWPointer() { return glfw_pointer_; }

    void MakeContextCurrent() const;
    void SwapBuffers();
    void ToggleFullscreen();
    void SetWindowIcon(std::string filepath) const;
    glm::vec2 GetFrameBufferSize() const;
    
    static void PollEvents() { glfwPollEvents(); }
    static void CloseAllWindows() { glfwTerminate(); }
    static const Window* GetActiveWindow() { return active_; };

private:
    GLFWwindow* glfw_pointer_;
    bool is_fullscreen_;
    static const Window* active_;

    static void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
};