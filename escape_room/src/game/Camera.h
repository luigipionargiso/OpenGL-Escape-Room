#pragma once

#include "engine/input/KeyObserver.h"
#include "engine/input/MousePositionObserver.h"
#include "engine/input/MouseScrollObserver.h"
#include "vendor/glm/glm.hpp"
#include "vendor/glm/gtc/type_ptr.hpp"

class Camera : public KeyObserver, public MousePositionObserver, public MouseScrollObserver
{
private:
	glm::vec3 m_Position;
	glm::vec3 m_Direction;
	glm::vec3 m_Up;
	float m_FoV, m_Aspect, m_Near, m_Far;

public:
	Camera(glm::vec3 position, glm::vec3 direction, glm::vec3 up);
	~Camera() = default;

	void onKeyboard(int key, bool pressed);
	void onMouseMove(double xpos, double ypos);
	void onMouseScroll(double offset);

	glm::mat4 LookAt(const glm::vec3 position, const glm::vec3 direction, const glm::vec3 up);
	glm::mat4 SetPosition(const glm::vec3 position);
	glm::mat4 SetDirection(const glm::vec3 direction);
	glm::mat4 SetUpVector(const glm::vec3 up);
	/* proj setters */

	inline glm::mat4 GetViewMatrix() const { return glm::lookAt(m_Position, m_Direction + m_Position, m_Up); }
	inline glm::mat4 GetProjMatrix() const { return glm::perspective(glm::radians(m_FoV), m_Aspect, m_Near, m_Far); }
	inline glm::vec3 GetPosition() const { return m_Position; }
	inline glm::vec3 GetDirection() const { return m_Direction; }
	inline glm::vec3 GetUpVector() const { return m_Up; }
};
