#include "StaticPhysicsComponent.h"
#include "GameObject.h"

StaticPhysicsComponent::StaticPhysicsComponent(GameObject& object, bool is_selectable)
	:is_selectable_(is_selectable)
{
	rigid_body_ = Physics::AddRigidBody(
		&object,
		object.GetPosition(),
		object.GetRotation(),
		0.0f,
		BOX,
		object.GetDimensions() / 2.0f
	);
	if (!is_selectable_)
		Physics::SetRigidBodyAttribute(rigid_body_, RAY_VISIBILITY, false);
}

StaticPhysicsComponent::~StaticPhysicsComponent()
{
	Physics::RemoveRigidBody(rigid_body_);
}
