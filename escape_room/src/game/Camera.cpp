#include "Camera.h"
#include "engine/input/Keyboard.h"
#include "engine/input/Mouse.h"
#include "vendor/glm/gtc/type_ptr.hpp"

Camera::Camera(glm::vec3 position, glm::vec3 direction, glm::vec3 up, float fov, float aspect, float near, float far)
	: fov_(fov), aspect_(aspect), near_(near), far_(far)
{
    speed_ = 0.05f;

    position_ = glm::vec3(position.y, position.z, position.x);
    direction_ = glm::vec3(direction.y, direction.z, direction.x);
    up_ = glm::vec3(up.y, up.z, up.x);

	view_matrix_ = glm::lookAt(position_, direction_ + position_, up_);
	projection_matrix_ = glm::perspective(glm::radians(fov_), aspect_, near_, far_);
}

void Camera::Update()
{
	UpdatePosition();
	UpdateRotation();

	view_matrix_ = glm::lookAt(position_, direction_ + position_, up_);
}

void Camera::Draw(Shader& shader)
{
    shader.Bind();
    shader.setUniformMat4f("u_Projection", projection_matrix_);
    shader.setUniformMat4f("u_View", view_matrix_);
    shader.setUniform3fv("u_ViewPos", position_);
}

void Camera::SetPosition(const glm::vec3 position)
{
    position_ = position;
    view_matrix_ = glm::lookAt(position_, direction_ + position_, up_);
}

void Camera::SetDirection(const glm::vec3 direction)
{
    direction_ = direction;
    view_matrix_ = glm::lookAt(position_, direction_ + position_, up_);
}

void Camera::SetUpVector(const glm::vec3 up)
{
    up_ = up;
    view_matrix_ = glm::lookAt(position_, direction_ + position_, up_);
}

void Camera::UpdatePosition()
{
    glm::vec3 front = { direction_.x, 0.0f, direction_.z };
    front = glm::normalize(front);

    if (Keyboard::GetKey(KEY_W) == PRESS)
        position_ += speed_ * front;

    if (Keyboard::GetKey(KEY_A) == PRESS)
        position_ -= glm::normalize(glm::cross(front, up_)) * speed_;

    if (Keyboard::GetKey(KEY_S) == PRESS)
        position_ -= speed_ * front;

    if (Keyboard::GetKey(KEY_D) == PRESS)
        position_ += glm::normalize(glm::cross(front, up_)) * speed_;
}

void Camera::UpdateRotation()
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

    direction_.x = (float)(cos(glm::radians(yaw)) * cos(glm::radians(pitch)));
    direction_.y = (float) sin(glm::radians(pitch));
    direction_.z = (float)(sin(glm::radians(yaw)) * cos(glm::radians(pitch)));
}
