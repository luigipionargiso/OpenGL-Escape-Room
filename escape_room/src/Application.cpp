#define GLEW_STATIC

#include <iostream>

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Texture.h"
#include "window/Window.h"
#include "Debug.h"
#include "window/Callbacks.h"
#include "input/Keyboard.h"
#include "input/Mouse.h"

#include "vendor/glm/glm.hpp"
#include "vendor/glm/gtc/matrix_transform.hpp"

int main(void)
{
    Window window(800, 600, "Hello World");
    window.MakeCurrent();
    Window::SetSwapInterval(1);

    window.SetFrameBufferSizeCallback((function)framebuffer_size_callback);
    //glfwSetCursorPosCallback(window.GetGLFWWindow(), mouse_callback);
    //window.SetKeyCallback((function)key_callback2);

    if (glewInit() != GLEW_OK) {
        std::cerr << "Cannot initialize GLEW" << std::endl;
        return -1;
    }

#ifdef DEBUG
    Debug::EnableDebug();
    Debug::PrintVersionsOnConsole();
#endif

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);

    /*float positions[16] = {
        -50.0f, -50.0f, 0.0f, 0.0f,
         50.0f,  50.0f, 1.0f, 1.0f,
         50.0f, -50.0f, 1.0f, 0.0f,
        -50.0f,  50.0f, 0.0f, 1.0f
    };*/

    float positions[40] = {
        -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, //0
         0.5f, -0.5f, -0.5f,  0.0f, 0.0f, //1
         0.5f,  0.5f, -0.5f,  0.0f, 1.0f, //2
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, //3
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, //4
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f, //5
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f, //6
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, //7
    };

    /* Array and Vertex Buffers */
    VertexArray va;
    VertexBuffer vb(positions, 40 * sizeof(float));
    VertexBufferLayout layout;
    layout.Push<float>(3);
    layout.Push<float>(2);
    va.AddBuffer(vb, layout);

    //index buffer
    /*unsigned int indices[6] = {
        0, 2, 1, 1, 3, 0
    };*/
    unsigned int indices[36] = {
        0, 1, 2, 0, 3, 2,
        4, 0, 3, 4, 3, 7,
        4, 5, 7, 5, 6, 7,
        5, 1, 6, 1, 2, 6,
        7, 6, 3, 6, 2, 3,
        4, 5, 0, 5, 1, 0
    };
    IndexBuffer ib(indices, 36);

    // shader
    Shader shader("res/shaders/basic.vert", "res/shaders/basic.frag");
    shader.Bind();
    
    // uniform
    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
    shader.setUniformMat4f("u_Model", model);

    //glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -5.0f));
    /*view = glm::rotate(view, glm::radians(45.0f), glm::vec3(0.0, 1.0, 0.0));
    view = glm::rotate(view, glm::radians(30.0f), glm::vec3(0.0, 0.0, 1.0));*/
    //shader.setUniformMat4f("u_View", view);
    Camera camera2;
    glm::mat4 view = camera2.LookAt(glm::vec3(0, 0, -5.0), glm::vec3(0), glm::vec3(0, 1.0, 0));

    glm::mat4 proj = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
    shader.setUniformMat4f("u_Projection", proj);

    // texture
    //Texture texture("res/textures/image.jpg");
    Texture texture("C:/Users/luigi/Pictures/1. Fotografia/tmp/sacra di san michele/_DSC3341-1.jpg");
    texture.Bind();
    shader.setUniform1i("u_Texture", 0);

    Renderer renderer;

    Camera camera;

    Keyboard key;
    key.AddKeyObserver(&camera);

    Mouse mouse;
    mouse.AddMousePositionObserver(&camera);

    while (window.IsOpen())
    {
        key.ProcessInput(window);
        mouse.ProcessInput(window);

        renderer.Clear();

        view = camera.GetViewMatrix();
        shader.setUniformMat4f("u_View", view);

        renderer.DrawIndexed(va, ib, shader);

        window.SwapFrameBuffer();
        window.PollEvents();
    }

    Window::CloseAllWindows();

    return 0;
}