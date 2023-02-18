#include "World.h"
#include "engine/physics/Physics.h"
#include "game/game_object/PlayerInputComponent.h"
#include "game/game_object/PlayerPhysicsComponent.h"
#include "game/game_object/PickablePhysicsComponent.h"
#include "game/game_object/StaticPhysicsComponent.h"

void World::Populate()
{
    Game& game = Game::GetInstance();
    GameObject* ptr;

    /* add the player object */
    ptr = new GameObject(nullptr, new PlayerInputComponent(), nullptr);
    objects_["player"] = ptr;
    ptr->SetPosition(glm::vec3(0.0f, 0.8f, 0.0f));
    ptr->SetDimensions(glm::vec3(0.1f, 0.8f, 0.1f));
    ptr->SetPhysicsComponent(new PlayerPhysicsComponent(*ptr));

    /* add other objects */
    ptr = new GameObject(new Model("res/models/floor/floor.fbx"), nullptr, nullptr);
    objects_["floor"] = ptr;
    ptr->SetDimensions(glm::vec3(4.15f, 0.10f, 5.4f));
    ptr->SetPhysicsComponent(new StaticPhysicsComponent(*ptr, false));

    ptr = new GameObject(new Model("res/models/armadio/armadio.fbx"), nullptr, nullptr);
    objects_["armadio"] = ptr;
    ptr->SetPosition(glm::vec3(1.36503f, 0.88f, -1.90509f));
    ptr->SetDimensions(glm::vec3(1.17f, 1.76f, 0.567f));
    ptr->SetPhysicsComponent(new StaticPhysicsComponent(*ptr, false));

    ptr = new GameObject(new Model("res/models/cassettiera/cassettiera.fbx"), nullptr, nullptr);
    objects_["cassettiera"] = ptr;
    ptr->SetPosition(glm::vec3(-1.71948f, 0.405f, 0.690669f));
    ptr->SetDimensions(glm::vec3(0.532345f, 0.81f, 1.63493f));
    ptr->SetPhysicsComponent(new StaticPhysicsComponent(*ptr, false));

    ptr = new GameObject(new Model("res/models/comodino/comodino.fbx"), nullptr, nullptr);
    objects_["comodino"] = ptr;
    ptr->SetPosition(glm::vec3(-1.78922f, 0.498333f, -0.639844f));
    ptr->SetDimensions(glm::vec3(0.412335f, 0.513333f, 0.412335f));
    ptr->SetPhysicsComponent(new StaticPhysicsComponent(*ptr, false));

    ptr = new GameObject(new Model("res/models/letto/telaio.fbx"), nullptr, nullptr);
    objects_["telaio_letto"] = ptr;
    ptr->SetPosition(glm::vec3(-0.948316f, 0.357138f, -1.53501f));
    ptr->SetDimensions(glm::vec3(2.065f, 0.714f, 1.014f)); // /2 ??
    ptr->SetPhysicsComponent(new StaticPhysicsComponent(*ptr, false));

    ptr = new GameObject(new Model("res/models/letto/letto.fbx"), nullptr, nullptr);
    objects_["letto"] = ptr;
    ptr->SetPosition(glm::vec3(-0.988657f, 0.32068f, -1.53501f));
    ptr->SetDimensions(glm::vec3(1.97185f, 0.522479f, 1.2496f));
    ptr->SetPhysicsComponent(new StaticPhysicsComponent(*ptr, false));

    ptr = new GameObject(new Model("res/models/letto/cuscino.fbx"), nullptr, nullptr);
    objects_["cuscino"] = ptr;
    ptr->SetPosition(glm::vec3(-1.68435f, 0.440846f, -1.52372f));
    ptr->SetDimensions(glm::vec3(0.425f, 0.113f, 0.732f));
    ptr->SetPhysicsComponent(new StaticPhysicsComponent(*ptr, true));

    ptr = new GameObject(new Model("res/models/pareti/sx.fbx"), nullptr, nullptr);
    objects_["parete_sx"] = ptr;
    ptr->SetPosition(glm::vec3(0.0f, 1.5f, -2.2f));
    ptr->SetDimensions(glm::vec3(4.0f, 3.0f, 0.1f));
    ptr->SetPhysicsComponent(new StaticPhysicsComponent(*ptr, false));

    ptr = new GameObject(new Model("res/models/pareti/parete_finestra.fbx"), nullptr, nullptr);
    objects_["parete_finestra"] = ptr;
    ptr->SetPosition(glm::vec3(2.1f, 1.5f, 0.4f));
    ptr->SetDimensions(glm::vec3(0.2f, 3.0f, 5.2f));
    ptr->SetPhysicsComponent(new StaticPhysicsComponent(*ptr, false));

    ptr = new GameObject(new Model("res/models/libri/libro_zelda.fbx"), nullptr, nullptr);
    objects_["libro_zelda"] = ptr;
    ptr->SetPosition(glm::vec3(1.72534f, 0.79195f, 1.94128f));
    ptr->SetDimensions(glm::vec3(0.260681f, 0.0439f, 0.185234f));
    ptr->SetPhysicsComponent(new PickablePhysicsComponent(*ptr, 1.0f));

    /* add lights */
    ambient_light_ = new AmbientLight(glm::vec3(0.08f));
    point_light_ = new PointLight(glm::vec3(0.0f, 1.95f, 0.42f), glm::vec3(0.0), glm::vec3(0.0));
    spot_light_ = new SpotLight(
        glm::vec3(-1.038f, 0.385f, -1.308f),
        glm::normalize(glm::vec3(1.0f, 0.0f, -0.7f)),
        cos(glm::radians(15.0f)),
        glm::vec3(1.0),
        glm::vec3(1.0)
    );
}
