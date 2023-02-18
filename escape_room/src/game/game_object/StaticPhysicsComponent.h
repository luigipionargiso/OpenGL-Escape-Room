#pragma once

#include "engine/physics/Physics.h"
#include "PhysicsComponent.h"

class StaticPhysicsComponent : public PhysicsComponent
{
public:
	StaticPhysicsComponent(GameObject& object, bool is_selectable);
	~StaticPhysicsComponent();

	void Update(GameObject& object) {}

private:
	RigidBody* rigid_body_;
	bool is_selectable_;
};