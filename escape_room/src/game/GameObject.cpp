#include "GameObject.h"
#include <vendor/glm/gtx/rotate_vector.hpp>

GameObject::GameObject(Model model, InputComponent* input, PhysicsComponent* physics)
    :model_(std::move(model)), input_(input), physics_(physics), shader_(nullptr)
{
    position_ = glm::vec3(0.0);
    rotation_euler_ = glm::vec3(0.0);
    scale_ = glm::vec3(1.0);
    bb_half_extents_ = model_.GetAABB().max;
    //bb_half_extents_ = glm::vec3(model_.GetAABB().max.y, model_.GetAABB().max.z, model_.GetAABB().max.x);
    model_matrix_ = glm::mat4(1.0);
}

void GameObject::CorrectOrientation()
{
    model_matrix_ = glm::rotate(model_matrix_, glm::radians(-90.0f), glm::vec3(1.0, 0.0, 0.0));
    model_matrix_ = glm::rotate(model_matrix_, glm::radians(-90.0f), glm::vec3(0.0, 0.0, 1.0));
    //bb_half_extents_ = model_matrix_ * glm::vec4(bb_half_extents_, 0.0);
}

void GameObject::SetPosition(glm::vec3 world_space_position)
{
    model_matrix_ = glm::rotate(model_matrix_, -rotation_euler_.z, glm::vec3(0.0, 0.0, 1.0));
    model_matrix_ = glm::rotate(model_matrix_, -rotation_euler_.y, glm::vec3(0.0, 1.0, 0.0));
    model_matrix_ = glm::rotate(model_matrix_, -rotation_euler_.x, glm::vec3(1.0, 0.0, 0.0));

    model_matrix_ = glm::translate(model_matrix_, world_space_position - position_);
    position_ = world_space_position;

    model_matrix_ = glm::rotate(model_matrix_, rotation_euler_.x, glm::vec3(1.0, 0.0, 0.0));
    model_matrix_ = glm::rotate(model_matrix_, rotation_euler_.y, glm::vec3(0.0, 1.0, 0.0));
    model_matrix_ = glm::rotate(model_matrix_, rotation_euler_.z, glm::vec3(0.0, 0.0, 1.0));
}

void GameObject::SetRotationEulerXYZ(glm::vec3 euler_xyz)
{
    model_matrix_ = glm::rotate(model_matrix_, -rotation_euler_.x, glm::vec3(1.0, 0.0, 0.0));
    model_matrix_ = glm::rotate(model_matrix_, euler_xyz.x, glm::vec3(1.0, 0.0, 0.0));

    model_matrix_ = glm::rotate(model_matrix_, -rotation_euler_.y, glm::vec3(0.0, 1.0, 0.0));
    model_matrix_ = glm::rotate(model_matrix_, euler_xyz.y, glm::vec3(0.0, 1.0, 0.0));

    model_matrix_ = glm::rotate(model_matrix_, -rotation_euler_.z, glm::vec3(0.0, 0.0, 1.0));
    model_matrix_ = glm::rotate(model_matrix_, euler_xyz.z, glm::vec3(0.0, 0.0, 1.0));

    rotation_euler_ = euler_xyz;
    //bb_half_extents_ = model_matrix_ * glm::vec4(bb_half_extents_, 0.0);
}

void GameObject::SetScale(glm::vec3 scale)
{
    model_matrix_ = glm::scale(model_matrix_, glm::vec3(1.0) / scale_);
    model_matrix_ = glm::scale(model_matrix_, scale);
    scale_ = scale;
}

void GameObject::Rotate(glm::vec3 angles, glm::vec3 rotation_center)
{
    glm::vec3 dist = position_ - rotation_center;
    glm::vec3 dist_rot = glm::rotate(dist, angles.x, glm::vec3(1.0, 0.0, 0.0));
    dist_rot = glm::rotate(dist_rot, angles.y, glm::vec3(0.0, 1.0, 0.0));
    dist_rot = glm::rotate(dist_rot, angles.z, glm::vec3(0.0, 0.0, 1.0));
    glm::vec3 offset = dist_rot - dist;
    model_matrix_ = glm::translate(model_matrix_, offset);
    position_ += offset;

    model_matrix_ = glm::rotate(model_matrix_, angles.x, glm::vec3(1.0, 0.0, 0.0));
    model_matrix_ = glm::rotate(model_matrix_, angles.y, glm::vec3(0.0, 1.0, 0.0));
    model_matrix_ = glm::rotate(model_matrix_, angles.z, glm::vec3(0.0, 0.0, 1.0));
    rotation_euler_ += angles;

    //bb_half_extents_ = model_matrix_ * glm::vec4(bb_half_extents_, 0.0);
}

void GameObject::Scale(glm::vec3 scale, glm::vec3 scale_center)
{

}

void GameObject::SetShader(Shader* shader)
{
    if(shader)  shader_ = shader;
}

void GameObject::Update(World& world)
{
    if (input_) input_->Update(*this);
    if (physics_) physics_->Update(*this, world);
}

void GameObject::Draw() const
{
    if (!invisible_ && shader_)
    {
        Shader& shader = *shader_;
        shader.Bind();
        shader.setUniformMat4f("u_Model", model_matrix_);
        model_.Draw(shader);
    }
}
