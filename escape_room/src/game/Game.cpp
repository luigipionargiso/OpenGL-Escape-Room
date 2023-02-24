#include "Game.h"
#include <iostream>
#include "engine/input/Mouse.h"
#include "engine/input/Keyboard.h"
#include "engine/physics/Physics.h"
#include "game/camera/DefaultCameraInput.h"
#include "lights/PointLight.h"
#include "game_object/PickableInputComponent.h"
#include "vendor/glm/gtc/constants.hpp"
#include "game/game_object/PlayerPhysicsComponent.h"
#include "game_object/PickablePhysicsComponent.h"
#include "game_phase/MenuPhase.h"

Game& Game::GetInstance()
{
    static Game instance;
    return instance;
}

HUDElement* Game::GetHUDElement(std::string name)
{
    auto search = hud_elements_.find(name);
    if (search != hud_elements_.end())
        return search->second;
    else
        return nullptr;
}

void Game::SetHUDElement(std::string name, HUDElement* hud)
{
    hud_elements_[name] = hud;
}

Shader* Game::GetShader(std::string name)
{
    auto search = shaders_.find(name);
    if (search != shaders_.end())
        return search->second;
    else
        return nullptr;
}

void Game::StartTimer()
{
    /* set start time */
    auto time = std::chrono::system_clock::now();
    start_time_ = static_cast<unsigned int>(time.time_since_epoch().count())
        * std::chrono::system_clock::period::num
        / static_cast<unsigned int>(std::chrono::system_clock::period::den);

    /* read last record */
    std::ifstream file("res/record.txt");
    if (!file.is_open())
    {
        std::cerr << "Failed to open the record file!" << std::endl;
        exit(EXIT_FAILURE);
    }

    unsigned int value;
    if (file >> value)
        last_record_ = value;
    else
        last_record_ = 0;

    file.close();
}

Game::Game()
{
    /* initialize shaders */
    shaders_["basic"] = new Shader("res/shaders/basic.vert", "res/shaders/basic.frag");
    shaders_["hud"] = new Shader("res/shaders/hud.vert", "res/shaders/hud.frag");

    world_ = World();
    world_.Populate();

    camera_ = Camera(
        glm::vec3(-0.6f, 1.5f, 2.8f),
        glm::vec3(0.0f, 0.0f, -1.0f),
        glm::vec3(0.0f, 1.0f, 0.0f),
        45.0f,
        16.0f / 9.0f,
        0.1f,
        100.0f
    );
    camera_.SetInputComponent(new DefaultCameraInput());

    current_phase_ = new MenuPhase();
    status_ = WALKING;
    
    current_time_ = 0;

    device_ = KEYBOARD_AND_MOUSE;
}

void Game::Update()
{
    if (device_ == GAMEPAD)
        current_phase_->HandlePadInput();
    else
        current_phase_->HandleInput();
    current_phase_->Update();
}

void Game::Draw()
{
    current_phase_->Draw();

    /* draw hud */
    if(hud_elements_["hud"])
        hud_elements_["hud"]->Render();
}

void Game::ChangePhase(GamePhase* new_phase)
{
    delete current_phase_;
    current_phase_ = new_phase;
}
