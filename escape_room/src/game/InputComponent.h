#pragma once

class GameObject;

class InputComponent
{
public:
	virtual ~InputComponent() {}
	virtual void Update(GameObject& object) = 0;
};
