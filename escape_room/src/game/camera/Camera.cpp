#include "Camera.h"
#include "engine/input/Keyboard.h"
#include "engine/input/Mouse.h"
#include "vendor/glm/gtc/type_ptr.hpp"

Camera::Camera(glm::vec3 position, glm::vec3 direction, glm::vec3 up, float fov, float aspect, float near, float far)
    : position_(position), direction_(direction), up_(up),
    fov_(fov), aspect_(aspect), near_(near), far_(far), input_(nullptr)
{
    view_matrix_ = glm::lookAt(position_, direction_ + position_, up_);
    projection_matrix_ = glm::perspective(glm::radians(fov_), aspect_, near_, far_);
}

void Camera::Update()
{
    if (input_) input_->Update(this);
}

void Camera::Draw(Shader& shader)
{
    view_matrix_ = glm::lookAt(position_, direction_ + position_, up_);
    projection_matrix_ = glm::perspective(glm::radians(fov_), aspect_, near_, far_);

    shader.setUniform3fv("u_view_pos", position_);
    shader.setUniformMat4f("u_View", view_matrix_);
    shader.setUniformMat4f("u_Projection", projection_matrix_);
}

void Camera::SetPosition(const glm::vec3 position)
{
    position_ = position;
}

void Camera::SetDirection(const glm::vec3 direction)
{
    direction_ = direction;
}

void Camera::SetUpVector(const glm::vec3 up)
{
    up_ = up;
}

glm::mat4 Camera::GetViewMatrix()
{
    view_matrix_ = glm::lookAt(position_, direction_ + position_, up_);
    return view_matrix_;
}
