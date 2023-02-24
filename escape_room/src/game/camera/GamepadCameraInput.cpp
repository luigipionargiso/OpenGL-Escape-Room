#include "GamepadCameraInput.h"
#include "vendor/glm/glm.hpp"
#include "engine/input/Gamepad.h"
#include "engine/input/Mouse.h"
#include "game/Game.h"

void GamepadCameraInput::Update(Camera* camera)
{
    if (Game::GetInstance().GetPlayerStatus() != EXAMINE)
    {
        UpdatePosition(camera);
        UpdateRotation(camera);
    }
}

void GamepadCameraInput::UpdatePosition(Camera* camera)
{
    static float t = 0.0f;
    static float initial_pos_y = 1.5f;

    glm::vec3 pos = camera->GetPosition();
    glm::vec3 dir = camera->GetDirection();
    glm::vec3 up = camera->GetUpVector();

    glm::vec3 front = { dir.x, 0.0, dir.z };
    front = glm::normalize(front);

    glm::vec2 left_axis = Gamepad::GetAxisStatus(AXIS_LEFT);

    if (left_axis.x > 0.1f || left_axis.x < -0.1f)
    {
        pos += glm::normalize(glm::cross(front, up)) * speed_ * left_axis.x;
    }

    if (left_axis.y > 0.1f || left_axis.y < -0.1f)
    {
        pos -= front * speed_ * left_axis.y;
    }

    /* swing up and down */
    if (camera->GetPosition() != pos)
    {
        pos.y = initial_pos_y + 0.1f * abs(sinf(t));
        t += 0.1f;
    }

    camera->SetPosition(pos);
}

void GamepadCameraInput::UpdateRotation(Camera* camera)
{
    glm::vec2 right_axis = Gamepad::GetAxisStatus(AXIS_RIGHT);

    static double yaw = -90.0;
    static double pitch = 0.0;

    yaw += right_axis.x;
    pitch -= right_axis.y;

    if (pitch > 89.0) pitch = 89.0;
    else if (pitch < -89.0) pitch = -89.0;

    glm::vec3 dir = glm::vec3(0.0);
    dir.x = (float)(cos(glm::radians(yaw)) * cos(glm::radians(pitch)));
    dir.y = (float)sin(glm::radians(pitch));
    dir.z = (float)(sin(glm::radians(yaw)) * cos(glm::radians(pitch)));

    camera->SetDirection(dir);
}
