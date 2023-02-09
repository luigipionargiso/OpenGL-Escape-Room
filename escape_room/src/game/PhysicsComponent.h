#pragma once

class World;
class GameObject;

class PhysicsComponent
{
public:
	virtual ~PhysicsComponent() {}
	virtual void Update(GameObject& object, World& world) = 0;
};