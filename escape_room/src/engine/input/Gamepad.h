#pragma once

#include <unordered_map>
#include "engine/window/Window.h"

enum GamepadAxis
{
	AXIS_LEFT, AXIS_RIGHT
};

enum GamepadButton
{
	BUTTON_FIRST,
	BUTTON_A, BUTTON_B, BUTTON_X, BUTTON_Y, LEFT_BUMPER, RIGHT_BUMPER,
	BUTTON_LAST
};

enum GamepadButtonStatus
{
	RELEASE_B,
	PRESS_B
};

class Gamepad
{
public:
	static GamepadButtonStatus GetButtonStatus(GamepadButton button);
	static glm::vec2 GetAxisStatus(GamepadAxis axis);
	static void PollEvents(Window& w);
private:
	static std::unordered_map<GamepadButton, GamepadButtonStatus> buttons_;
	static glm::vec2 axis_left_, axis_right_;
};