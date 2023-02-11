#include "DefaultCameraInput.h"
#include "vendor/glm/glm.hpp"
#include "engine/input/Keyboard.h"
#include "engine/input/Mouse.h"
#include "game/Game.h"

void DefaultCameraInput::Update(Camera* camera)
{
    if (Game::GetInstance().GetStatus() != EXAMINE)
    {
	    UpdatePosition(camera);
	    UpdateRotation(camera);
    }
}

void DefaultCameraInput::UpdatePosition(Camera* camera)
{
    glm::vec3 pos = camera->GetPosition();
    glm::vec3 dir = camera->GetDirection();
    glm::vec3 up = camera->GetUpVector();

    glm::vec3 front = { dir.x, 0.0, dir.z };
    front = glm::normalize(front);

    if (Keyboard::GetKey(KEY_W) == PRESS)
        pos += speed_ * front;

    if (Keyboard::GetKey(KEY_A) == PRESS)
        pos -= glm::normalize(glm::cross(front, up)) * speed_;

    if (Keyboard::GetKey(KEY_S) == PRESS)
        pos -= speed_ * front;

    if (Keyboard::GetKey(KEY_D) == PRESS)
        pos += glm::normalize(glm::cross(front, up)) * speed_;

    camera->SetPosition(pos);
}

void DefaultCameraInput::UpdateRotation(Camera* camera)
{
    glm::vec2 mouse_pos = Mouse::GetCursorPosition();

    static double last_x = 0.0, last_y = 0.0;
    static double yaw = -90.0;
    static double pitch = 0.0;

    static bool first_time = true;
    if (first_time)
    {
        last_x = mouse_pos.x;
        last_y = mouse_pos.y;
        first_time = false;
        return;
    }

    double x_offset = mouse_pos.x - last_x;
    double y_offset = last_y - mouse_pos.y;
    last_x = mouse_pos.x;
    last_y = mouse_pos.y;

    glm::vec2 window_size = Window::GetActiveWindow()->GetFrameBufferSize();

    yaw += x_offset * 720.0 / window_size.x;
    pitch += y_offset * 180.0 / window_size.y;

    if (pitch > 89.0) pitch = 89.0;
    else if (pitch < -89.0) pitch = -89.0;

    glm::vec3 dir = glm::vec3(0.0);
    dir.x = (float)(cos(glm::radians(yaw)) * cos(glm::radians(pitch)));
    dir.y = (float)sin(glm::radians(pitch));
    dir.z = (float)(sin(glm::radians(yaw)) * cos(glm::radians(pitch)));

    camera->SetDirection(dir);
}
