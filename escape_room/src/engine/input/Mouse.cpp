#include "Mouse.h"
#include "GLFW/glfw3.h"

double Mouse::cursor_x_ = 0.0;
double Mouse::cursor_y_ = 0.0;
MouseButtonStatus Mouse::left_ = RELEASE_M;
MouseButtonStatus Mouse::right_ = RELEASE_M;

glm::vec2 Mouse::GetCursorPosition()
{
	return glm::vec2(cursor_x_, cursor_y_);
}

MouseButtonStatus Mouse::GetMouseButton(MouseButton button)
{
	switch (button)
	{
	case MOUSE_BUTTON_LEFT:
		return left_;
	case MOUSE_BUTTON_RIGHT:
		return right_;
	}
}

void Mouse::PollEvents(Window& w)
{
	if (w.IsHovered())
	{
		glfwGetCursorPos(w.GetGLFWPointer(), &cursor_x_, &cursor_y_);
		left_ = static_cast<MouseButtonStatus>(glfwGetMouseButton(w.GetGLFWPointer(), GLFW_MOUSE_BUTTON_LEFT));
		right_ = static_cast<MouseButtonStatus>(glfwGetMouseButton(w.GetGLFWPointer(), GLFW_MOUSE_BUTTON_RIGHT));
	}
}
