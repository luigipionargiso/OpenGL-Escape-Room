#pragma once

#include "engine/window/Window.h"
#include "vendor/glm/glm.hpp"

enum MouseButton
{
	MOUSE_BUTTON_LEFT, MOUSE_BUTTON_RIGHT
};

enum MouseButtonStatus
{
	RELEASE_M,
	PRESS_M
};

class Mouse
{
public:
	static glm::vec2 GetCursorPosition();
	static MouseButtonStatus GetMouseButton(MouseButton button);
	static void PollEvents(Window& w);
private:
	static double cursor_x_, cursor_y_;
	static MouseButtonStatus left_, right_;
};

