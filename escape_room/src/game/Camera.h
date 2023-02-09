#pragma once

#include "vendor/glm/glm.hpp"
#include <engine/Shader.h>

class Camera
{
public:
	Camera(
		glm::vec3 position,
		glm::vec3 direction,
		glm::vec3 up,
		float fov,
		float aspect,
		float near,
		float far
	);
	~Camera() = default;
	void Update();
	void Draw(Shader& shader);

	void SetPosition(const glm::vec3 position);
	void SetDirection(const glm::vec3 direction);
	void SetUpVector(const glm::vec3 up);

	inline glm::vec3 GetPosition() const { return glm::vec3(position_.z, position_.x, position_.y); }
	inline glm::vec3 GetDirection() const { return glm::vec3(direction_.z, direction_.x, direction_.y); }
	inline glm::vec3 GetUpVector() const { return glm::vec3(up_.z, up_.x, up_.y); }
	inline glm::mat4 GetViewMatrix() const { return view_matrix_; }
	inline glm::mat4 GetProjectionMatrix() const { return projection_matrix_; }

private:
	glm::vec3 position_;
	glm::vec3 direction_;
	glm::vec3 up_;
	float fov_, aspect_, near_, far_;
	float speed_;
	glm::mat4 view_matrix_;
	glm::mat4 projection_matrix_;

	void UpdatePosition();
	void UpdateRotation();
};

