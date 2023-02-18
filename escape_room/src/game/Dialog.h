#pragma once

#include "game/Game.h"
#include "engine/text_rendering/Text.h"
#include "game/HUDElement.h"

class Dialog
{
public:
	Dialog(std::string text)
		:text_(text), dialog_box_(
			HUDElement(
				new Texture("res/textures/dialog_box.png", IMAGE),
				Game::GetInstance().GetShader("hud"),
				0.98f
			)
		) {}

	void Draw(Shader& shader)
	{
		dialog_box_.Render();
		Text::Render(text_.c_str(), -0.5f, -0.5f, 32.0f);
	}

private:
	HUDElement dialog_box_;
	std::string text_;
};