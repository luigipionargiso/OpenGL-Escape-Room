#pragma once

#include "input/KeyObserver.h"
#include "input/MousePositionObserver.h"
#include "Shader.h"
#include "vendor/glm/glm.hpp"

class Camera : public KeyObserver, public MousePositionObserver
{
private:
	glm::vec3 m_Position;
	glm::vec3 m_Direction;
	glm::vec3 m_Up;
public:
	Camera(
		glm::vec3 position = glm::vec3(0, 0, -5.0),
		glm::vec3 direction = glm::vec3(0),
		glm::vec3 up = glm::vec3(0, 1.0, 0)
	);
	~Camera() = default;

	void onKeyboard(int key, bool pressed);
	void onMouseMove(float xpos, float ypos, bool hovered);

	glm::mat4 LookAt(const glm::vec3 position, const glm::vec3 direction, const glm::vec3 up);
	glm::mat4 SetPosition(const glm::vec3 position);
	glm::mat4 SetDirection(const glm::vec3 direction);
	glm::mat4 SetUpVector(const glm::vec3 up);

	inline glm::mat4 GetViewMatrix() const { return glm::lookAt(m_Position, m_Direction, m_Up); }
	inline glm::vec3 GetPosition() const { return m_Position; }
	inline glm::vec3 GetDirection() const { return m_Direction; }
	inline glm::vec3 GetUpVector() const { return m_Up; }

private:
	void Update();
};
