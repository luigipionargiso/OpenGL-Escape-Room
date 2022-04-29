#define GLEW_STATIC

#include <iostream>
#include "GL/glew.h"
#include "GLFW/glfw3.h"

int main(void) {
    GLFWwindow* window;

    if (!glfwInit())
        return -1;

    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) {
        std::cerr << "Cannot initialize GLEW" << std::endl;
        return -1;
    }

    std::cout << "OpenGL version:" << glGetString(GL_VERSION) << std::endl;

    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        //glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}