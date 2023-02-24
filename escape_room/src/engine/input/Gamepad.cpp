#include "Gamepad.h"
#include "GLFW/glfw3.h"

/* initialize the hash map */
std::unordered_map<GamepadButton, GamepadButtonStatus> Gamepad::buttons_ = [] {
    std::unordered_map<GamepadButton, GamepadButtonStatus> buttons;

    for (int k = BUTTON_FIRST; k != BUTTON_LAST; k++)
        buttons[static_cast<GamepadButton>(k)] = RELEASE_B;

    return buttons;
}();

glm::vec2 Gamepad::axis_left_ = glm::vec2(0.0f);
glm::vec2 Gamepad::axis_right_ = glm::vec2(0.0f);

GamepadButtonStatus Gamepad::GetButtonStatus(GamepadButton button)
{
    return buttons_[button];
}

glm::vec2 Gamepad::GetAxisStatus(GamepadAxis axis)
{
    switch (axis)
    {
    case AXIS_LEFT:
        return axis_left_;
    case AXIS_RIGHT:
        return axis_right_;
    }
}

void Gamepad::PollEvents(Window& w)
{
    GLFWgamepadstate state;

    if (glfwGetGamepadState(GLFW_JOYSTICK_1, &state))
    {
        buttons_[BUTTON_A] = static_cast<GamepadButtonStatus>(state.buttons[GLFW_GAMEPAD_BUTTON_B]);
        buttons_[BUTTON_B] = static_cast<GamepadButtonStatus>(state.buttons[GLFW_GAMEPAD_BUTTON_A]);
        buttons_[BUTTON_X] = static_cast<GamepadButtonStatus>(state.buttons[GLFW_GAMEPAD_BUTTON_Y]);
        buttons_[BUTTON_Y] = static_cast<GamepadButtonStatus>(state.buttons[GLFW_GAMEPAD_BUTTON_X]);
        buttons_[LEFT_BUMPER] = static_cast<GamepadButtonStatus>(state.buttons[GLFW_GAMEPAD_BUTTON_LEFT_BUMPER]);
        buttons_[RIGHT_BUMPER] = static_cast<GamepadButtonStatus>(state.buttons[GLFW_GAMEPAD_BUTTON_RIGHT_BUMPER]);

        axis_left_.x = state.axes[GLFW_GAMEPAD_AXIS_LEFT_X];
        axis_left_.y = state.axes[GLFW_GAMEPAD_AXIS_LEFT_Y];
        axis_right_.x = state.axes[GLFW_GAMEPAD_AXIS_RIGHT_X];
        axis_right_.y = state.axes[GLFW_GAMEPAD_AXIS_RIGHT_Y];
    }
}
