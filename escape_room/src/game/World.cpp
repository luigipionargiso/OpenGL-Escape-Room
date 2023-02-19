#include "World.h"
#include "engine/physics/Physics.h"
#include "game/game_object/PlayerInputComponent.h"
#include "game/game_object/PlayerPhysicsComponent.h"
#include "game/game_object/PickablePhysicsComponent.h"
#include "game/game_object/StaticPhysicsComponent.h"

void World::Populate()
{
    /* add the player object */
    objects_["player"] = new GameObject(nullptr);
    objects_["player"]->SetPosition(glm::vec3(-0.6f, 1.5f, 2.8f)); /* same as the camera*/
    objects_["player"]->SetDimensions(glm::vec3(0.2f, 2.3f, 0.2f));
    objects_["player"]->SetInputComponent(new PlayerInputComponent());
    objects_["player"]->SetPhysicsComponent(new PlayerPhysicsComponent(*objects_["player"]));

    LoadWalls();
    LoadForniture();
    LoadMovableObjects();

    /* add lights */
    ambient_light_ = new AmbientLight(glm::vec3(0.1f));
    point_light_ = new PointLight(glm::vec3(0.0f, 1.95f, 0.42f), glm::vec3(0.0), glm::vec3(0.0));
    spot_light_ = new SpotLight(
        glm::vec3(-1.038f, 0.48f, -1.308f),
        glm::normalize(glm::vec3(1.0f, 0.0f, -0.7f)),
        cos(glm::radians(15.0f)),
        glm::vec3(1.0),
        glm::vec3(1.0)
    );
}

void World::LoadWalls()
{
    GameObject* ptr;

    ptr = new GameObject(new Model("res/models/floor/floor.fbx"));
    objects_["floor"] = ptr;
    //ptr->SetDimensions(glm::vec3(4.15f, 0.1f, 5.4f));
    ptr->SetDimensions(glm::vec3(5.0f, 0.1f, 7.0f));
    ptr->SetPhysicsComponent(new StaticPhysicsComponent(*ptr, false));

    ptr = new GameObject(new Model("res/models/pareti/soffitto.fbx"));
    objects_["soffitto"] = ptr;
    ptr->SetPosition(glm::vec3(0.0f, 3.0f, 0.4f));
    ptr->SetDimensions(glm::vec3(5.0f, 0.1f, 7.0f));
    ptr->SetPhysicsComponent(new StaticPhysicsComponent(*ptr, false));

    ptr = new GameObject(new Model("res/models/pareti/sx.fbx"));
    objects_["parete_sx"] = ptr;
    ptr->SetPosition(glm::vec3(0.0f, 1.5f, -2.2f));
    ptr->SetDimensions(glm::vec3(4.0f, 3.0f, 0.1f));
    ptr->SetPhysicsComponent(new StaticPhysicsComponent(*ptr, false));

    ptr = new GameObject(new Model("res/models/pareti/dx.fbx"));
    objects_["parete_dx"] = ptr;
    ptr->SetPosition(glm::vec3(0.0f, 1.5f, 3.1f));
    ptr->SetDimensions(glm::vec3(4.0f, 2.9f, 0.1f));
    ptr->SetPhysicsComponent(new StaticPhysicsComponent(*ptr, false));

    ptr = new GameObject(new Model("res/models/pareti/frontale.fbx"));
    objects_["parete_frontale"] = ptr;
    ptr->SetPosition(glm::vec3(-2.03f, 1.5f, 0.4f));
    ptr->SetDimensions(glm::vec3(0.1f, 2.9f, 5.2f));
    ptr->SetPhysicsComponent(new StaticPhysicsComponent(*ptr, false));

    ptr = new GameObject(new Model("res/models/pareti/frontale_VAR.fbx"));
    objects_["parete_frontale_VAR"] = ptr;
    ptr->SetPosition(glm::vec3(-2.03f, 1.5f, 0.4f));
    ptr->SetVisibility(false);

    ptr = new GameObject(new Model("res/models/pareti/parete_finestra.fbx"));
    objects_["parete_finestra"] = ptr;
    ptr->SetPosition(glm::vec3(2.1f, 1.5f, 0.4f));
    ptr->SetDimensions(glm::vec3(0.1f, 3.0f, 5.2f));
    ptr->SetPhysicsComponent(new StaticPhysicsComponent(*ptr, false));

    ptr = new GameObject(new Model("res/models/porta/porta.fbx"));
    objects_["porta"] = ptr;
    ptr->SetPosition(glm::vec3(-0.6f, 1.1f, 2.98376f));
    ptr->SetDimensions(glm::vec3(1.0f, 2.2f, 0.2f));
    ptr->SetPhysicsComponent(new StaticPhysicsComponent(*ptr, true));

    ptr = new GameObject(new Model("res/models/finestra/finestra.fbx"));
    objects_["finestra"] = ptr;
    ptr->SetPosition(glm::vec3(2.1f, 1.55f, 0.0f));
    ptr->SetDimensions(glm::vec3(0.30f, 1.5f, 2.0f));
    ptr->SetPhysicsComponent(new StaticPhysicsComponent(*ptr, true));
}

void World::LoadForniture()
{
    GameObject* ptr;

    ptr = new GameObject(new Model("res/models/armadio/armadio.fbx"));
    objects_["armadio"] = ptr;
    ptr->SetPosition(glm::vec3(1.36503f, 0.88f, -1.90509f));
    ptr->SetDimensions(glm::vec3(1.17f, 1.76f, 0.567f));
    ptr->SetPhysicsComponent(new StaticPhysicsComponent(*ptr, false));

    ptr = new GameObject(new Model("res/models/libreria/libreria.fbx"));
    objects_["libreria"] = ptr;
    ptr->SetPosition(glm::vec3(1.58565f, 1.01f, 2.851f));
    ptr->SetDimensions(glm::vec3(0.8f, 2.02f, 0.28f));

    ptr = new GameObject(new Model("res/models/scrivania/scrivania.fbx"));
    objects_["scrivania"] = ptr;
    ptr->SetPosition(glm::vec3(1.679f, 0.75f, 1.85679f));
    ptr->SetDimensions(glm::vec3(0.6f, 0.04f, 1.4f));
    ptr->SetPhysicsComponent(new StaticPhysicsComponent(*ptr, false));

    ptr = new GameObject(new Model("res/models/cassettiera/cassettiera.fbx"));
    objects_["cassettiera"] = ptr;
    ptr->SetPosition(glm::vec3(-1.71948f, 0.405f, 0.690669f));
    ptr->SetDimensions(glm::vec3(0.4f, 0.81f, 1.63493f));
    ptr->SetPhysicsComponent(new StaticPhysicsComponent(*ptr, false));

    ptr = new GameObject(new Model("res/models/cassettiera/cassetto.fbx"));
    objects_["cassetto"] = ptr;
    ptr->SetPosition(glm::vec3(-1.4786f, 0.62f, 0.30f));
    ptr->SetDimensions(glm::vec3(0.493513f, 0.22f, 0.293169f));
    ptr->SetPhysicsComponent(new StaticPhysicsComponent(*ptr, true));

    ptr = new GameObject(new Model("res/models/comodino/comodino.fbx"));
    objects_["comodino"] = ptr;
    ptr->SetPosition(glm::vec3(-1.78922f, 0.498333f, -0.639844f));
    ptr->SetDimensions(glm::vec3(0.3f, 0.25f, 0.412335f));
    ptr->SetPhysicsComponent(new StaticPhysicsComponent(*ptr, false));

    ptr = new GameObject(new Model("res/models/letto/telaio.fbx"));
    objects_["telaio_letto"] = ptr;
    ptr->SetPosition(glm::vec3(-0.948316f, 0.357138f, -1.53501f));

    ptr = new GameObject(new Model("res/models/letto/letto.fbx"));
    objects_["letto"] = ptr;
    ptr->SetPosition(glm::vec3(-0.988657f, 0.29f, -1.53501f));
    ptr->SetDimensions(glm::vec3(1.97185f, 0.25f, 1.2496f));
    ptr->SetPhysicsComponent(new StaticPhysicsComponent(*ptr, false));

    ptr = new GameObject(new Model("res/models/canestro/canestro.fbx"));
    objects_["canestro"] = ptr;
    ptr->SetPosition(glm::vec3(-1.79444f, 2.03352f, 2.13473f));
    Physics::AddRigidBody(
        nullptr,
        glm::vec3(-1.78f, 1.86f, 2.32f),
        glm::quat(1.0f, 0.0f, 0.0f, 0.0f),
        0.0f,
        BOX,
        glm::vec3(0.42f, 0.05f, 0.03f) / 2.0f
    );
    Physics::AddRigidBody(
        nullptr,
        glm::vec3(-1.78f, 1.86f, 1.96f),
        glm::quat(1.0f, 0.0f, 0.0f, 0.0f),
        0.0f,
        BOX,
        glm::vec3(0.42f, 0.05f, 0.03f) / 2.0f
    );
    Physics::AddRigidBody(
        nullptr,
        glm::vec3(-1.6f, 1.86f, 2.14f),
        glm::quat(1.0f, 0.0f, 0.0f, 0.0f),
        0.0f,
        BOX,
        glm::vec3(0.03f, 0.05f, 4.2f) / 2.0f
    );

}

void World::LoadMovableObjects()
{
    GameObject* ptr;

    ptr = new GameObject(new Model("res/models/letto/cuscino.fbx"));
    objects_["cuscino"] = ptr;
    ptr->SetPosition(glm::vec3(-1.68435f, 0.4f, -1.52372f));
    ptr->SetDimensions(glm::vec3(0.3f, 0.1f, 0.5f));
    ptr->SetPhysicsComponent(new PickablePhysicsComponent(*ptr, 2.0f));

    ptr = new GameObject(new Model("res/models/torcia/torcia.fbx"));
    objects_["torcia"] = ptr;
    ptr->SetPosition(glm::vec3(-1.038f, 0.48f, -1.308f));
    ptr->SetDimensions(glm::vec3(0.185473f, 0.06026f, 0.06026f));
    ptr->SetPhysicsComponent(new StaticPhysicsComponent(*ptr, true));

    ptr = new GameObject(new Model("res/models/posters/donut.fbx"));
    objects_["donut"] = ptr;
    ptr->SetPosition(glm::vec3(-1.99775f, 1.2f, 0.7f));
    ptr->SetDimensions(glm::vec3(0.1f, 0.6f, 0.4f));
}
