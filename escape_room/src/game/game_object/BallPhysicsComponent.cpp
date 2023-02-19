#include "BallPhysicsComponent.h"
#include "GameObject.h"

#define MAX_TICKS 200

BallPhysicsComponent::BallPhysicsComponent(GameObject& object, float mass)
{
	rigid_body_ = Physics::AddRigidBody(
		&object,
		object.GetPosition(),
		object.GetRotation(),
		mass,
		SPHERE,
		object.GetDimensions() / 2.0f
	);
	Physics::SetRigidBodyAttribute(rigid_body_, COLLISION_VISIBILITY, false);
	sim_ticks_ = MAX_TICKS;
}

BallPhysicsComponent::~BallPhysicsComponent()
{
	Physics::RemoveRigidBody(rigid_body_);
}

void BallPhysicsComponent::Update(GameObject& object)
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

void BallPhysicsComponent::RestartSimulation(GameObject& object)
{
	Physics::UpdateRigidBody(rigid_body_, object.GetPosition(), object.GetRotation());
	sim_ticks_ = 0;
}

void BallPhysicsComponent::SetLinearVelocity(glm::vec3 linear_velocity)
{
	Physics::SetLinearVelocity(rigid_body_, linear_velocity);
}
