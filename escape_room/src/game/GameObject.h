#pragma once

#include "engine/model_loader/Model.h"
#include "vendor/glm/glm.hpp"
#include "InputComponent.h"
#include "PhysicsComponent.h"
class World;

class GameObject
{
public:
	GameObject(Model model, InputComponent* input, PhysicsComponent* physics);
	~GameObject() = default;

	GameObject(GameObject&& other) noexcept = default;
	GameObject& operator=(GameObject&& other) noexcept = default;

	void CorrectOrientation();
	void SetPosition(glm::vec3 world_space_position);
	void SetRotationEulerXYZ(glm::vec3 euler_xyz);
	void SetScale(glm::vec3 scale);
	void Rotate(glm::vec3 angles, glm::vec3 rotation_center);
	void Scale(glm::vec3 scale, glm::vec3 scale_center);

	void SetVisibility(bool is_visible) { invisible_ = !is_visible; }
	void SetShader(Shader* shader);

	inline glm::vec3 GetPosition() const { return position_; }
	inline glm::vec3 GetRotationEulerXYZ() const { return rotation_euler_; }
	inline glm::vec3 GetScale() const { return scale_; }
	inline glm::vec3 GetBBHalfExtents() const { return bb_half_extents_; }

	void Update(World& world);
	void Draw() const;

private:
	Model model_;
	glm::vec3 position_, rotation_euler_, scale_;
	glm::vec3 bb_half_extents_;

	Shader* shader_;
	glm::mat4 model_matrix_;

	bool invisible_ = false;

	InputComponent* input_;
	PhysicsComponent* physics_;
};
