#include "GameObject.h"
#include <vendor/glm/gtx/euler_angles.hpp>

GameObject::GameObject(Model* model, InputComponent* input, PhysicsComponent* physics)
    :model_(model), input_(input), physics_(physics), shader_(nullptr)
{
    position_ = glm::vec3(0.0);
    rotation_ = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
    scale_ = glm::vec3(1.0);
    dimensions_ = glm::vec3(0.0f);

    model_matrix_ = glm::mat4(1.0);
}

void GameObject::SetPosition(glm::vec3 world_space_position)
{
    position_ = world_space_position;
}

void GameObject::SetRotationEulerYXZ(glm::vec3 euler_yxz)
{
    rotation_ = glm::toQuat(glm::orientate4(euler_yxz));
}

void GameObject::SetDirection(glm::vec3 dir)
{
    rotation_ = glm::quatLookAt(dir, glm::vec3(0.0f, 1.0f, 0.0f));
}

void GameObject::SetScale(glm::vec3 scale)
{
    scale_ = scale;
}

void GameObject::SetDimensions(glm::vec3 dimensions)
{
    dimensions_ = dimensions;
}

//void GameObject::Rotate(glm::vec3 angles, glm::vec3 rotation_center)
//{
//    //glm::vec3 dist = position_ - rotation_center;
//    //glm::vec3 dist_rot = glm::rotate(dist, angles.x, glm::vec3(1.0, 0.0, 0.0));
//    //dist_rot = glm::rotate(dist_rot, angles.y, glm::vec3(0.0, 1.0, 0.0));
//    //dist_rot = glm::rotate(dist_rot, angles.z, glm::vec3(0.0, 0.0, 1.0));
//    //glm::vec3 offset = dist_rot - dist;
//
//    //position_ += offset;
//    //rotation_euler_ += angles;
//
//    //bb_half_extents_ = model_matrix_ * glm::vec4(bb_half_extents_, 0.0);
//}
//
//void GameObject::Scale(glm::vec3 scale, glm::vec3 scale_center)
//{
//
//}

void GameObject::SetShader(Shader* shader)
{
    shader_ = shader;
}

void GameObject::Update()
{
    if (input_) input_->Update(*this);
    if (physics_) physics_->Update(*this);
}

void GameObject::Draw()
{
    if (!invisible_ && shader_  && model_)
    {
        CalcModelMatrix();
        Shader& shader = *shader_;
        shader.setUniformMat4f("u_Model", model_matrix_);
        model_->Draw(shader);
    }
}

void GameObject::CalcModelMatrix()
{
    glm::mat4 identity = glm::mat4(1.0);

    glm::mat4 scale = glm::scale(identity, scale_);
    glm::mat4 rotation = glm::toMat4(rotation_);
    glm::mat4 translation = glm::translate(identity, position_);

    model_matrix_ = translation * rotation * scale;
}
