#include "Game.h"
#include <iostream>
#include "engine/input/Mouse.h"
#include "engine/input/Keyboard.h"
#include "engine/physics/Physics.h"
#include "game/camera/DefaultCameraInput.h"
#include "lights/PointLight.h"
#include "game_object/PickableInputComponent.h"
#include "vendor/glm/gtc/constants.hpp"

Game& Game::GetInstance()
{
    static Game instance;
    return instance;
}

Game::Game()
{
    /* initialize shaders */
    shaders_["basic"] = new Shader("res/shaders/basic.vert", "res/shaders/basic.frag");
    shaders_["basic_white"] = new Shader("res/shaders/basic_white.vert", "res/shaders/basic_white.frag");

    Populate();

    camera_ = Camera(
        glm::vec3(0.0f, 1.5f, 0.0f),
        glm::vec3(0.0f, 0.0f, -1.0f),
        glm::vec3(0.0f, 1.0f, 0.0f),
        45.0f,
        16.0f / 9.0f,
        0.1f,
        100.0f
    );
    static DefaultCameraInput camera_input;
    camera_.SetInputComponent(&camera_input);

    phase_ = PLAYING;
    status_ = WALKING;
}

void Game::Populate()
{
    GameObject* ptr;
    world_["cross"] = new GameObject(new Model("res/models/cross/cross.fbx"), nullptr, nullptr);
    world_["cross"]->SetScale(glm::vec3(0.05f, 16.0f / 9.0f * 0.05f, 0.05f));

    world_["player"] = new GameObject(nullptr, nullptr, nullptr);
    world_["player"]->SetPosition(glm::vec3(0.0f, 0.75f, 0.0f));
    world_["player"]->SetDimensions(glm::vec3(0.3f, 1.3f, 1.0f));
    ptr = world_["player"];
    Physics::AddRigidBody(ptr, ptr->GetPosition(), ptr->GetRotation(), 0, CYLINDER, ptr->GetDimensions() / 2.0f);


    world_["floor"] = new GameObject(new Model("res/models/floor/floor.fbx"), nullptr, nullptr);
    world_["floor"]->SetDimensions(glm::vec3(4.15f, 0.001f, 5.4f));
    ptr = world_["floor"];
    Physics::AddRigidBody(ptr, ptr->GetPosition(), ptr->GetRotation(), 0, BOX, ptr->GetDimensions() / 2.0f);

    world_["armadio"] = new GameObject(new Model("res/models/armadio/armadio.fbx"), nullptr, nullptr);
    world_["armadio"]->SetPosition(glm::vec3(1.36503f, 0.88f, -1.91336f));
    world_["armadio"]->SetDimensions(glm::vec3(1.17f, 1.76f, 0.566553f));
    ptr = world_["armadio"];
    Physics::AddRigidBody(ptr, ptr->GetPosition(), ptr->GetRotation(), 0, BOX, ptr->GetDimensions() / 2.0f);

    world_["cassettiera"] = new GameObject(new Model("res/models/cassettiera/cassettiera.fbx"), nullptr, nullptr);
    world_["cassettiera"]->SetPosition(glm::vec3(-1.71948f, 0.405f, 0.690669f));
    world_["cassettiera"]->SetDimensions(glm::vec3(0.532345f, 0.81f, 1.63493f));
    ptr = world_["cassettiera"];
    Physics::AddRigidBody(ptr, ptr->GetPosition(), ptr->GetRotation(), 0, BOX, ptr->GetDimensions() / 2.0f);

    world_["comodino"] = new GameObject(new Model("res/models/comodino/comodino.fbx"), nullptr, nullptr);
    world_["comodino"]->SetPosition(glm::vec3(-1.78922f, 0.498333f, -0.639844f));
    world_["comodino"]->SetDimensions(glm::vec3(0.412335f, 0.513333f, 0.412335f));
    ptr = world_["comodino"];
    Physics::AddRigidBody(ptr, ptr->GetPosition(), ptr->GetRotation(), 0, BOX, ptr->GetDimensions() / 2.0f);

    world_["telaio_letto"] = new GameObject(new Model("res/models/letto/telaio.fbx"), nullptr, nullptr);
    world_["telaio_letto"]->SetPosition(glm::vec3(-0.948316, 0.357138, -1.53501));
    world_["telaio_letto"]->SetDimensions(glm::vec3(2.065, 0.714276, 1.01383) / 2.0f);
    ptr = world_["telaio_letto"];
    Physics::AddRigidBody(ptr, ptr->GetPosition(), ptr->GetRotation(), 0, BOX, ptr->GetDimensions() / 2.0f);


    for (auto& obj : world_)
        obj.second->SetShader(shaders_["basic"]);

    world_["cross"]->SetShader(shaders_["basic_white"]);

    point_lights_["point"] = new PointLight(glm::vec3(2.0, 2.0, 2.0), glm::vec3(1.0), glm::vec3(1.0));
    ambient_light_ = new AmbientLight(glm::vec3(1.0));
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
            world_.begin(),
            world_.end(),
            [op](const auto& mo) {return mo.second == op; });

        //RETURN VARIABLE IF FOUND
        if (result != world_.end()) {
            std::cout << result->first;
            //op->SetInputComponent((InputComponent*)new PickableInputComponent());
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

    for (auto& obj : world_)
        obj.second->Update();


   /* static float gg = 0.0f;
    gg += 0.01f;
    if (gg > glm::two_pi<float>()) { gg -= glm::two_pi<float>(); }

    world_["comodino"]->SetRotationEulerXYZ(glm::vec3(glm::radians(89.0f), glm::radians(89.0f), 0.0f));
    auto angles = world_["comodino"]->GetRotationEulerXYZ();
    std::cout << "(" << glm::degrees(angles.x) << ", " << glm::degrees(angles.y) << ", " << glm::degrees(angles.z) << ")" << '\r';*/

    /* update lights */
    static float y = 0.0f, off = 0.04f;

    if (y > 3.0f)
        off = -0.04f;
    else if (y < 0.0f)
        off = 0.04f;
    y += off;
    glm::vec3 pos = point_lights_["point"]->position_;
    point_lights_["point"]->position_ = glm::vec3(pos.x, y, pos.z);
}

void Game::Draw()
{
    camera_.Draw(*shaders_["basic"]);
    for (auto& obj : world_)
        obj.second->Draw();

    ambient_light_->Draw(*shaders_["basic"]);
    point_lights_["point"]->Draw(*shaders_["basic"]);

    world_["cross"]->Draw();
}
