#pragma once

#include "engine/physics/Physics.h"
#include "PhysicsComponent.h"

class PickablePhysicsComponent : public PhysicsComponent
{
public:
	PickablePhysicsComponent(GameObject& object, float mass);
	~PickablePhysicsComponent();

	void Update(GameObject& object);
	void RestartSimulation(GameObject& object) override;
	void SetLinearVelocity(glm::vec3 linear_velocity) override;

private:
	RigidBody* rigid_body_;
	unsigned int sim_ticks_;
};