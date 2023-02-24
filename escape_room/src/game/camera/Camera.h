#pragma once

#include "vendor/glm/glm.hpp"
#include "engine/Shader.h"
#include "CameraInputComponent.h"

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
	Camera() = default;
	~Camera() = default;

	void Update();
	void Draw(Shader& shader);

	void SetPosition(const glm::vec3 position);
	void SetDirection(const glm::vec3 direction);
	void SetUpVector(const glm::vec3 up);
	void SetInputComponent(CameraInputComponent* input);

	inline glm::vec3 GetPosition() const { return position_; }
	inline glm::vec3 GetDirection() const { return direction_; }
	inline glm::vec3 GetUpVector() const { return up_; }
	glm::mat4 GetViewMatrix();

private:
	glm::vec3 position_;
	glm::vec3 direction_;
	glm::vec3 up_;
	float fov_, aspect_, near_, far_;
	glm::mat4 view_matrix_;
	glm::mat4 projection_matrix_;

	CameraInputComponent* input_;
};

