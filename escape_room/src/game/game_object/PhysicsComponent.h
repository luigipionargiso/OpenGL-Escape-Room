#pragma once

#include "vendor/glm/glm.hpp"
class GameObject;

class PhysicsComponent
{
public:
	virtual ~PhysicsComponent() {}
	virtual void Update(GameObject& object) = 0;
	virtual void RestartSimulation(GameObject& object) {}
	virtual void SetLinearVelocity(glm::vec3 linear_velocity) {}
};
