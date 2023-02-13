#pragma once

#include "InputComponent.h"
#include "GameObject.h"
#include "game/Game.h"

class PlayerInputComponent : public InputComponent
{
	void Update(GameObject& player)
	{
		player.SetPosition(Game::GetInstance().GetActiveCamera().GetPosition());
	}
};