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
#include "game_phase/StartPhase.h"

Game& Game::GetInstance()
{
    static Game instance;
    return instance;
}

Shader* Game::GetShader(std::string name)
{
    auto search = shaders_.find(name);
    if (search != shaders_.end())
        return search->second;
    else
        return nullptr;
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

    current_phase_ = new StartPhase();
    status_ = WALKING;

    hud_elements_["hud"] = new HUDElement(new Texture("res/textures/hud.png", IMAGE), shaders_["hud"], -0.99f);
}

void Game::Update()
{
    current_phase_->HandleInput();
    current_phase_->Update();
}

void Game::Draw()
{
    current_phase_->Draw();

    /* draw hud */
    hud_elements_["hud"]->Render();
}

void Game::ChangePhase(GamePhase* new_phase)
{
    delete current_phase_;
    current_phase_ = new_phase;
}
