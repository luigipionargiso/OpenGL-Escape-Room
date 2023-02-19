#include <iostream>
#include <chrono>
#include <thread>

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "engine/window/Window.h"
#include "engine/input/Keyboard.h"
#include "engine/input/Mouse.h"
#include "engine/physics/Physics.h"
#include "engine/text_rendering/Text.h"
#include "engine/Shader.h"
#include "engine/Texture.h"

#include "game/Game.h"

#ifdef DEBUG
#include "Debug.h"
#endif

/* use Nvidia card */
//#include <windows.h>
//extern "C" {
//    __declspec(dllexport) DWORD NvOptimusEnablement = 1;
//    __declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
//}


int main(void)
{
    if (!glfwInit())
    {
        std::cerr << "Could not initialize GLFW" << '\n';
        exit(EXIT_FAILURE);
    }

    Window window(800, 450, "Escape Room");
    window.MakeContextCurrent();
    glViewport(0, 0, (int)window.GetFrameBufferSize().x, (int)(window.GetFrameBufferSize().x * 9) / 16);

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
    Text::Init(new Texture("res/textures/text/characters.png", IMAGE), new Shader("res/shaders/text.vert", "res/shaders/text.frag"));
    
    Game& game = Game::GetInstance();

    /* game loop constants */
    const auto MS_PER_FRAME = std::chrono::milliseconds(16);
    const long MS_PER_UPDATE = 16;

    /* how far the game clock is behind the real world */
    long lag = 0;

    auto previous = std::chrono::high_resolution_clock::now();
    bool f_was_released = true;

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

        /* toggle fullscreen */
        if (Keyboard::GetKey(KEY_F) == RELEASE) f_was_released = true;
        if (Keyboard::GetKey(KEY_F) == PRESS && f_was_released)
        {
            window.ToggleFullscreen();
            f_was_released = false;
        }

        if (Keyboard::GetKey(KEY_ESC)) break;

        /* update at fixed time steps */
        while (lag >= MS_PER_UPDATE)
        {
            game.Update();
            lag -= MS_PER_UPDATE;
        }

        /* draw */
        Renderer::Clear();
        game.Draw();

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