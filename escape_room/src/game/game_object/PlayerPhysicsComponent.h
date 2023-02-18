#pragma once

#include "PhysicsComponent.h"
#include "engine/physics/Physics.h"
#include "game/game_object/GameObject.h"

class PlayerPhysicsComponent : public PhysicsComponent
{
public:
    PlayerPhysicsComponent(GameObject& player);
    ~PlayerPhysicsComponent();
    void Update(GameObject& object) override;

private:
    RigidBody* rigid_body_;
    glm::vec3 last_positions_[2];
};