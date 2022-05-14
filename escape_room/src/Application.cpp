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

#include "vendor/glm/glm.hpp"
#include "vendor/glm/gtc/matrix_transform.hpp"

//#include <windows.h>
//#ifdef __cplusplus
//extern "C" {
//#endif
//
//    __declspec(dllexport) DWORD NvOptimusEnablement = 1;
//    __declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
//
//#ifdef __cplusplus
//}
//#endif

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
    exit(-1); // shut down the program gracefully (it does cleanup stuff too)
              // without exit(), OpenGL will constantly print the error message... make sure to kill your program.
}

int main(void) {
    GLFWwindow* window;

    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    //glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(800, 600, "Hello World", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) {
        std::cerr << "Cannot initialize GLEW" << std::endl;
        return -1;
    }

    //debug
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(errorOccurredGL, nullptr);

    std::cout << "GLEW version: " << glewGetString(GLEW_VERSION) << std::endl;
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "Shading Language version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
    std::cout << "GL_VENDOR: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "GL_RENDERER: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "GLFW version: " << glfwGetVersionString() << std::endl;

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    float positions[16] = {
        -50.0f, -50.0f, 0.0f, 0.0f,
         50.0f,  50.0f, 1.0f, 1.0f,
         50.0f, -50.0f, 1.0f, 0.0f,
        -50.0f,  50.0f, 0.0f, 1.0f
    };

    unsigned int indices[6] = {
        0, 2, 1, 1, 3, 0
    };

    /* Array and Vertex Buffers */
    VertexArray va;
    VertexBuffer vb(positions, 4 * 4 * sizeof(float));
    VertexBufferLayout layout;
    layout.Push<float>(2);
    layout.Push<float>(2);
    va.AddBuffer(vb, layout);

    //index buffer
    IndexBuffer ib(indices, 6);

    //transformatiomn matrices
    glm::mat4 proj = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f);
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(300.0f, 300.0f, 0.0f));

    glm::mat4 mvp = proj * view * model;

    // shader
    Shader shader("res/shaders/basic.vert", "res/shaders/basic.frag");
    shader.Bind();

    // uniform
    shader.setUniform4f("u_color", 0.8f, 0.4f, 0.1f, 1.0f);
    shader.setUniformMat4f("u_MVP", mvp);

    // texture
    Texture texture("res/textures/image.jpg");
    texture.Bind();
    shader.setUniform1i("u_Texture", 0);

    Renderer renderer;

    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        renderer.Draw(va, ib, shader);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}