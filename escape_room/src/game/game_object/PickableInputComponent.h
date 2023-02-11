#pragma once

#include "InputComponent.h"

class PickableInputComponent : public InputComponent
{
	void Update(GameObject& object) override;
};

