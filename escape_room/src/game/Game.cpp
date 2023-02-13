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

RigidBody* playerr;

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
    shaders_["basic_white"] = new Shader("res/shaders/basic_white.vert", "res/shaders/basic_white.frag");

    world_ = World();

    camera_ = Camera(
        glm::vec3(0.0f, 1.5f, 0.0f),
        glm::vec3(0.0f, 0.0f, -1.0f),
        glm::vec3(0.0f, 1.0f, 0.0f),
        45.0f,
        16.0f / 9.0f,
        0.1f,
        100.0f
    );
    camera_.SetInputComponent(new DefaultCameraInput());

    phase_ = PLAYING;
    status_ = WALKING;
}

void Game::Populate()
{
    world_.Populate();
}

void Game::Pick(GameObject* picked_object)
{
    picked_object_ = picked_object;
    picked_object->SetPosition(camera_.GetPosition() + camera_.GetDirection());
}

void Game::Update()
{
    if (Mouse::GetMouseButton(MOUSE_BUTTON_LEFT) == PRESS_M)
    {
        GameObject* op = (GameObject*)Physics::CastRay(camera_.GetPosition(), camera_.GetDirection());
        auto result = std::find_if(
            world_.objects_.begin(),
            world_.objects_.end(),
            [op](const auto& mo) {return mo.second == op; });

        //RETURN VARIABLE IF FOUND
        if (result != world_.objects_.end()) {
            std::cout << result->first;
            op->SetInputComponent((InputComponent*)new PickableInputComponent());
            status_ = HOLD;
        }

    }

    /* switch between hold and examine */
    static bool var = false;
    if (status_ == HOLD && Keyboard::GetKey(KEY_Q) == PRESS) {
        status_ = EXAMINE;
    }
    else if (status_ == EXAMINE && Keyboard::GetKey(KEY_Q) == RELEASE) {
        var = true;
    }
    else if (status_ == EXAMINE && Keyboard::GetKey(KEY_Q) == PRESS && var) {
        status_ = HOLD;
    }

    camera_.Update();

    for (auto& obj : world_.objects_)
        obj.second->Update();

    /* update lights */
    static float y = 0.0f, off = 0.04f;

    if (y > 3.0f)
        off = -0.04f;
    else if (y < 0.0f)
        off = 0.04f;
    y += off;
    glm::vec3 pos = world_.point_lights_["point"]->position_;
    world_.point_lights_["point"]->position_ = glm::vec3(pos.x, y, pos.z);
}

void Game::Draw()
{
    camera_.Draw(*shaders_["basic"]);
    for (auto& obj : world_.objects_)
        obj.second->Draw();

    world_.ambient_light_->Draw(*shaders_["basic"]);
    world_.point_lights_["point"]->Draw(*shaders_["basic"]);
}
