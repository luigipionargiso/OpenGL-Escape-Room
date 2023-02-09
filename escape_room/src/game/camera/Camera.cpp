#include "Camera.h"
#include "engine/input/Keyboard.h"
#include "engine/input/Mouse.h"
#include "vendor/glm/gtc/type_ptr.hpp"

Camera::Camera(glm::vec3 position, glm::vec3 direction, glm::vec3 up, float fov, float aspect, float near, float far)
	: fov_(fov), aspect_(aspect), near_(near), far_(far), input_(nullptr)
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
    if (input_)
    {
        input_->Update(this);
        view_matrix_ = glm::lookAt(position_, direction_ + position_, up_);
    }
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
    position_ = glm::vec3(position.y, position.z, position.x);
}

void Camera::SetDirection(const glm::vec3 direction)
{
    direction_ = glm::vec3(direction.y, direction.z, direction.x);
}

void Camera::SetUpVector(const glm::vec3 up)
{
    up_ = glm::vec3(up.y, up.z, up.x);
}