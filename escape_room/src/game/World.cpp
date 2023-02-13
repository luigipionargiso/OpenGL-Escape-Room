#include "World.h"
#include "engine/physics/Physics.h"
#include "game/game_object/PlayerInputComponent.h"
#include "game/game_object/PlayerPhysicsComponent.h"

void World::Populate()
{
    Game& game = Game::GetInstance();
    GameObject* ptr;

    /* add the player object */
    ptr = new GameObject(nullptr, new PlayerInputComponent(), nullptr);
    objects_["player"] = ptr;
    ptr->SetPosition(glm::vec3(0.0f, 0.8f, 0.0f));
    ptr->SetDimensions(glm::vec3(0.2f, 1.2f, 0.2f));
    ptr->SetPhysicsComponent(
        new PlayerPhysicsComponent(
            Physics::AddRigidBody(ptr, ptr->GetPosition(), ptr->GetRotation(), 70.0f, BOX, ptr->GetDimensions() / 2.0f),
            ptr->GetPosition()
        )
    );
    
    /* add the central cross object */
    ptr = new GameObject(new Model("res/models/cross/cross.fbx"), nullptr, nullptr);
    objects_["cross"] = ptr;
    ptr->SetScale(glm::vec3(0.05f, 16.0f / 9.0f * 0.05f, 0.05f));
    ptr->SetShader(game.GetShader("basic_white"));

    /* add other objects */
    ptr = new GameObject(new Model("res/models/floor/floor.fbx"), nullptr, nullptr);
    objects_["floor"] = ptr;
    ptr->SetDimensions(glm::vec3(4.15f, 0.001f, 5.4f));
    ptr->SetShader(game.GetShader("basic"));
    //Physics::AddRigidBody(ptr, ptr->GetPosition(), ptr->GetRotation(), 0.0f, BOX, ptr->GetDimensions() / 2.0f);

    ptr = new GameObject(new Model("res/models/armadio/armadio.fbx"), nullptr, nullptr);
    objects_["armadio"] = ptr;
    ptr->SetPosition(glm::vec3(1.36503f, 0.88f, -1.91336f));
    ptr->SetDimensions(glm::vec3(1.17f, 1.76f, 0.566553f));
    Physics::AddRigidBody(ptr, ptr->GetPosition(), ptr->GetRotation(), 0.0f, BOX, ptr->GetDimensions() / 2.0f);
    ptr->SetShader(game.GetShader("basic"));

    ptr = new GameObject(new Model("res/models/cassettiera/cassettiera.fbx"), nullptr, nullptr);
    objects_["cassettiera"] = ptr;
    ptr->SetPosition(glm::vec3(-1.71948f, 0.405f, 0.690669f));
    ptr->SetDimensions(glm::vec3(0.532345f, 0.81f, 1.63493f));
    Physics::AddRigidBody(ptr, ptr->GetPosition(), ptr->GetRotation(), 0.0f, BOX, ptr->GetDimensions() / 2.0f);
    ptr->SetShader(game.GetShader("basic"));

    ptr = new GameObject(new Model("res/models/comodino/comodino.fbx"), nullptr, nullptr);
    objects_["comodino"] = ptr;
    ptr->SetPosition(glm::vec3(-1.78922f, 0.498333f, -0.639844f));
    ptr->SetDimensions(glm::vec3(0.412335f, 0.513333f, 0.412335f));
    Physics::AddRigidBody(ptr, ptr->GetPosition(), ptr->GetRotation(), 0.0f, BOX, ptr->GetDimensions() / 2.0f);
    ptr->SetShader(game.GetShader("basic"));

    ptr = new GameObject(new Model("res/models/letto/telaio.fbx"), nullptr, nullptr);
    objects_["telaio_letto"] = ptr;
    ptr->SetPosition(glm::vec3(-0.948316, 0.357138, -1.53501));
    ptr->SetDimensions(glm::vec3(2.065, 0.714276, 1.01383)); // /2 ??
    Physics::AddRigidBody(ptr, ptr->GetPosition(), ptr->GetRotation(), 0.0f, BOX, ptr->GetDimensions() / 2.0f);
    ptr->SetShader(game.GetShader("basic"));


    point_lights_["point"] = new PointLight(glm::vec3(2.0, 2.0, 2.0), glm::vec3(1.0), glm::vec3(1.0));
    ambient_light_ = new AmbientLight(glm::vec3(1.0));
}
