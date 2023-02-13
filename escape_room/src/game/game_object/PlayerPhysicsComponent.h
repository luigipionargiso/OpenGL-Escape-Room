#pragma once

#include "PhysicsComponent.h"
#include "engine/physics/Physics.h"
#include "game/game_object/GameObject.h"

class PlayerPhysicsComponent : public PhysicsComponent
{
public:
	PlayerPhysicsComponent(RigidBody* rigid_body, glm::vec3 position)
		:rigid_body_(rigid_body), last_position_(position) {}
	void Update(GameObject& object) override;

private:
	RigidBody* rigid_body_;
	glm::vec3 last_position_;
};