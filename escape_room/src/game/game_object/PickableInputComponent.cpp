#include "PickableInputComponent.h"
#include "game/Game.h"
#include "vendor/glm/glm.hpp"
#include "vendor/glm/gtx/vector_angle.hpp"
#include "vendor/glm/gtc/constants.hpp"
#include "cmath"
#include <iostream>
#include "engine/input/Mouse.h"
#include "engine/input/Keyboard.h"
#include "engine/input/Gamepad.h"
#include "engine/window/Window.h"

void PickableInputComponent::Update(GameObject& object)
{
    Camera& camera = Game::GetInstance().GetActiveCamera();
    glm::vec3 camera_dir = camera.GetDirection();
    glm::mat4 inv_view_matrix = glm::inverse(camera.GetViewMatrix()); /* transponse instead of inverse? */

    static glm::vec3 examine_rotation = glm::vec3(0.0f);

    if (Game::GetInstance().GetPlayerStatus() == HOLD)
    {
        object.SetPosition(glm::vec3(inv_view_matrix * glm::vec4(0.5f, 0.0f, -1.0f, 1.0f)));
        object.SetDirection(glm::normalize(camera_dir));
        examine_rotation = glm::vec3(0.0f);
    }
    else if (Game::GetInstance().GetPlayerStatus() == EXAMINE)
    {
        object.SetPosition(glm::vec3(inv_view_matrix * glm::vec4(0.0f, 0.0f, -1.0f, 1.0f)));

        if (Game::GetInstance().GetDevice() == KEYBOARD_AND_MOUSE)
        {
            if (Keyboard::GetKey(KEY_W) == PRESS) {
                examine_rotation.x += 0.03f;
            }
            if (Keyboard::GetKey(KEY_S) == PRESS) {
                examine_rotation.x -= 0.03f;
            }
            if (Keyboard::GetKey(KEY_A) == PRESS) {
                examine_rotation.y -= 0.03f;
            }
            if (Keyboard::GetKey(KEY_D) == PRESS) {
                examine_rotation.y += 0.03f;
            }
        }
        else
        {
            examine_rotation.x += Gamepad::GetAxisStatus(AXIS_LEFT).x * 0.05f;
            examine_rotation.y += Gamepad::GetAxisStatus(AXIS_LEFT).y * 0.05f;
        }

        object.SetRotationEulerYXZ(examine_rotation);
    }
}
