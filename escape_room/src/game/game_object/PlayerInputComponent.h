#pragma once

#include "InputComponent.h"
#include "GameObject.h"
#include "game/Game.h"

class PlayerInputComponent : public InputComponent
{
	void Update(GameObject& player)
	{
		glm::vec3 cam_pos = Game::GetInstance().GetActiveCamera().GetPosition();
		player.SetPosition(cam_pos);
	}
};