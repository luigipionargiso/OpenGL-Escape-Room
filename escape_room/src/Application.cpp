#include <iostream>
#include <chrono>
#include <thread>
#include <stdlib.h>
#include "GL/glew.h"
#include "GLFW/glfw3.h"

#ifdef DEBUG
#include "Debug.h"
#endif

#include "engine/Shader.h"
#include "engine/window/Window.h"
#include "engine/input/Keyboard.h"
#include "engine/input/Mouse.h"
#include "game/camera/Camera.h"
#include "game/camera/DefaultCameraInput.h"

#include "vendor/glm/glm.hpp"
#include "vendor/glm/gtc/matrix_transform.hpp"

#include "engine/model_loader/Model.h"
#include <game/GameObject.h>
#include "game/World.h"

#include "engine/physics/Physics.h"

#include <windows.h>
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

int main(void)
{
    if (!glfwInit())
    {
        std::cerr << "Could not initialize GLFW" << '\n';
        exit(EXIT_FAILURE);
    }

    Window window(800, 600, "Hello World");
    window.MakeContextCurrent();

    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Could not initialize GLEW" << '\n';
        exit(EXIT_FAILURE);
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

    Physics::Initialize();

    // shader
    Shader shader("res/shaders/basic.vert", "res/shaders/basic.frag");
    shader.Bind();
    Shader shader_w("res/shaders/basic_white.vert", "res/shaders/basic_white.frag");
    shader_w.Bind();

    Camera camera(
        glm::vec3(0.0f, 0.0f, 1.5f),
        glm::vec3(-1.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 0.0f, 1.0f),
        45.0f,
        16.0f/9.0f,
        0.1f,
        100.0f
    );
    DefaultCameraInput camera_input;
    camera.SetInputComponent(&camera_input);

    float y = 2.0f, off = 0.01f;
    shader.Bind();
    shader.setUniform3fv("u_Light.ambient", glm::vec3(1.0, 1.0, 1.0));
    shader.setUniform3fv("u_Light.diffuse", glm::vec3(1.0, 1.0, 1.0));
    shader.setUniform3fv("u_Light.specular", glm::vec3(1.0, 1.0, 1.0));

    /*auto start = std::chrono::high_resolution_clock::now();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> duration = end - start;
    std::cout << duration.count() << "s " << '\n';*/

    World world;
    world.Populate(shader);

    /* game loop constants */
    const auto MS_PER_FRAME = std::chrono::milliseconds(16);
    const long MS_PER_UPDATE = 16;

    /* how far the game clock is behind the real world */
    long lag = 0;

    auto previous = std::chrono::high_resolution_clock::now();

    GameObject cross(Model("res/models/cross/cross.fbx"), nullptr, nullptr);
    //cross.CorrectOrientation();
    cross.SetScale(glm::vec3(0.05, 16.0 / 9.0 * 0.05, 1.0));
    cross.SetShader(&shader_w);

    while (window.IsOpen())
    {
        /* measure time between frames */
        auto current = std::chrono::high_resolution_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(current - previous);
        previous = current;
        lag += (long)elapsed.count();

        /* handle input */
        Window::PollEvents();
        Keyboard::PollEvents(window);
        Mouse::PollEvents(window);

        if (Mouse::GetMouseButton(MOUSE_BUTTON_LEFT) == PRESS)
        {
            GameObject* op = (GameObject*)Physics::CastRay(camera.GetPosition(), camera.GetDirection());
            auto result = std::find_if(
                world.objects_.begin(),
                world.objects_.end(),
                [op](const auto& mo) {return mo.second == op; });

            //RETURN VARIABLE IF FOUND
            if (result != world.objects_.end())
                std::cout << result->first;

        }


        /* update at fixed time steps */
        while (lag >= MS_PER_UPDATE)
        {
            camera.Update();

            if (y > 3.0f)
                off = -0.04f;
            else if (y < 0.0f)
                off = 0.04f;
            y += off;

            lag -= MS_PER_UPDATE;
        }

        /* draw */
        Renderer::Clear();

        camera.Draw(shader);

        shader.Bind();
        shader.setUniform3fv("u_Light.position", glm::vec3(2.0, y, 2.0));

        world.Draw(shader);

        shader_w.Bind();
        cross.Draw();

        /* limit frame rate to 60 FPS */
        auto sleep_time = std::chrono::duration_cast<std::chrono::milliseconds>(
            current + MS_PER_FRAME - std::chrono::high_resolution_clock::now()
            );
        std::this_thread::sleep_for(sleep_time);

        window.SwapBuffers();
    }

    Window::CloseAllWindows();

    return 0;
}