#include <iostream>

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#ifdef DEBUG
#include "Debug.h"
#endif

#include "engine/VertexArray.h"
#include "engine/VertexBuffer.h"
#include "engine/VertexBufferLayout.h"
#include "engine/IndexBuffer.h"
#include "engine/Shader.h"
#include "engine/Texture.h"
#include "engine/window/Window.h"
#include "engine/input/Keyboard.h"
#include "engine/input/Mouse.h"
#include "game/Camera.h"

#include "vendor/glm/glm.hpp"
#include "vendor/glm/gtc/matrix_transform.hpp"

#include "engine/model_loader/Model.h"

#include <chrono>

int main(void)
{
    Window window(800, 600, "Hello World");
    window.MakeCurrent();
    window.SetSwapInterval(1);

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
    glEnable(GL_MULTISAMPLE);

    //glEnable(GL_CULL_FACE);

    /*
    float vertices[] = {
        // positions          // normals           // texture coords
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
    };

    VertexArray va;
    VertexBuffer vb(vertices, sizeof(vertices));
    VertexBufferLayout layout;
    layout.Push<float>(3);
    layout.Push<float>(3);
    layout.Push<float>(2);
    va.AddBuffer(vb, layout);*/

    // shader
    Shader shader("res/shaders/basic.vert", "res/shaders/basic.frag");
    shader.Bind();
    
    // tranformation matrices
    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
    //model = glm::scale(model, glm::vec3(0.01f, 0.01f, 0.01f));
    shader.setUniformMat4f("u_Model", model);

    // texture
    /*Texture diffuse("res/textures/_DSC3341-1.jpg", DIFFUSE);
    Texture specular("res/textures/specular.jpg", SPECULAR);

    diffuse.Bind(0);
    shader.setUniform1i("u_Material.diffuse", 0);

    specular.Bind(1);
    shader.setUniform1i("u_Material.specular", 1);*/

    Camera camera(
        glm::vec3(0, 0, 0.0),
        glm::vec3(0, 0, -1.0),
        glm::vec3(0, 1.0, 0)
    );

    Keyboard key;
    key.AddKeyObserver(&camera);

    Mouse mouse;
    mouse.AddMousePositionObserver(&camera);
    mouse.AddMouseScrollObserver(&camera);

    float y = 1.0f, off = 0.01f;
    shader.setUniform3fv("u_Light.ambient", glm::vec3(1.0, 1.0, 1.0));
    shader.setUniform3fv("u_Light.diffuse", glm::vec3(1.0, 1.0, 1.0));
    shader.setUniform3fv("u_Light.specular", glm::vec3(1.0, 1.0, 1.0));

    auto start = std::chrono::high_resolution_clock::now();
    Model backpack("res/cube/cube3.fbx");
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> duration = end - start;
    std::cout << duration.count() << "s " << '\n';

    while (window.IsOpen())
    {
        Renderer::Clear();
        key.ProcessInput(window);
        mouse.ProcessInput(window);

        shader.Bind();

        glm::mat4 proj = camera.GetProjMatrix();
        shader.setUniformMat4f("u_Projection", proj);
        glm::mat4 view = camera.GetViewMatrix();
        shader.setUniformMat4f("u_View", view);

        if (y > 1.0f)
            off = -0.01f;
        else if (y < -1.0f)
            off = 0.01f;
        y += off;
        shader.setUniform3fv("u_Light.position", glm::vec3(2.0, y, 2.0));
        shader.setUniform3fv("u_ViewPos", camera.GetPosition());

        //Renderer::Draw(va, shader);

        backpack.Draw(shader);

        window.SwapFrameBuffer();
        window.PollEvents();
    }

    Window::CloseAllWindows();

    return 0;
}