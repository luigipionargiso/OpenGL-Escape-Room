#include "PickablePhysicsComponent.h"
#include "GameObject.h"

#define MAX_TICKS 150

PickablePhysicsComponent::PickablePhysicsComponent(GameObject& object, float mass)
{
	rigid_body_ = Physics::AddRigidBody(
		&object,
		object.GetPosition(),
		object.GetRotation(),
		mass,
		BOX,
		object.GetDimensions() / 2.0f
	);
	Physics::SetRigidBodyAttribute(rigid_body_, COLLISION_VISIBILITY, false);
	sim_ticks_ = MAX_TICKS;
}

PickablePhysicsComponent::~PickablePhysicsComponent()
{
	Physics::RemoveRigidBody(rigid_body_);
}

void PickablePhysicsComponent::Update(GameObject& object)
{
	if (sim_ticks_ < MAX_TICKS)
	{
		RigidBodyTranform transform = Physics::Simulate(rigid_body_);
		object.SetPosition(transform.position);
		object.SetRotation(transform.rotation);
		sim_ticks_++;
	}
	else
	{
		Physics::UpdateRigidBody(rigid_body_, object.GetPosition(), object.GetRotation());
	}
}

void PickablePhysicsComponent::SetLinearVelocity(glm::vec3 linear_velocity)
{
	Physics::SetLinearVelocity(rigid_body_, linear_velocity);
}
