#pragma once

#include "engine/model_loader/Model.h"
#include "vendor/glm/glm.hpp"
#include "vendor/glm/gtx/quaternion.hpp"
#include "InputComponent.h"
#include "PhysicsComponent.h"

class World;

class GameObject
{
public:
	GameObject(Model* model, InputComponent* input, PhysicsComponent* physics);
	~GameObject();

	GameObject(GameObject&& other) noexcept = default;
	GameObject& operator=(GameObject&& other) noexcept = default;

	void SetPosition(glm::vec3 world_space_position);
	void SetRotation(glm::quat rotation_quaternion);
	void SetRotationEulerYXZ(glm::vec3 euler_yxz);
	void SetDirection(glm::vec3 dir);
	void SetScale(glm::vec3 scale);
	void SetDimensions(glm::vec3 dimensions);

	//void Rotate(glm::vec3 angles, glm::vec3 rotation_center);
	//void Scale(glm::vec3 scale, glm::vec3 scale_center);

	void SetVisibility(bool is_visible) { invisible_ = !is_visible; }
	void SetInputComponent(InputComponent* input) { input_ = input; }
	void SetPhysicsComponent(PhysicsComponent* physics) { physics_ = physics; }


	inline glm::vec3 GetPosition() const { return position_; }
	inline glm::quat GetRotation() const { return rotation_; }
	inline glm::vec3 GetScale() const { return scale_; }
	//inline glm::vec3 GetRotationEulerXYZ() const { return glm::vec3(0.0f); }
	inline glm::vec3 GetDimensions() const { return dimensions_; }
	inline PhysicsComponent* GetPhysicsComponent() const { return physics_; }

	void Update();
	void Draw(Shader& shader);

private:
	Model* model_;

	glm::vec3 position_, scale_;
	glm::quat rotation_;
	glm::vec3 dimensions_;
	glm::mat4 model_matrix_;

	bool invisible_ = false;

	InputComponent* input_;
	PhysicsComponent* physics_;

	void CalcModelMatrix();
};
