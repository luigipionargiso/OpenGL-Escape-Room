#pragma once

class GameObject;

class PhysicsComponent
{
public:
	virtual ~PhysicsComponent() {}
	virtual void Update(GameObject& object) = 0;
};
