#include "Camera.h"
#include "engine/window/Window.h"

Camera::Camera(glm::vec3 position, glm::vec3 direction, glm::vec3 up)
    : m_Position(position), m_Direction(direction), m_Up(glm::vec3(up)),
        m_FoV(45.0f), m_Aspect(16.0f/9.0f), m_Near(0.1f), m_Far(100.0f) {}

void Camera::onKeyboard(int key, bool pressed)
{
    glm::vec3 front = { m_Direction.x, 0.0f, m_Direction.z };
    front = glm::normalize(front);

    float camera_speed = 2.0f * (float)Window::GetDeltaTime();

    if (key == GLFW_KEY_W)
        m_Position += camera_speed * front;

    else if (key == GLFW_KEY_S)
        m_Position -= camera_speed * front;

    else if (key == GLFW_KEY_A)
        m_Position -= glm::normalize(glm::cross(front, m_Up)) * camera_speed;

    else if (key == GLFW_KEY_D)
        m_Position += glm::normalize(glm::cross(front, m_Up)) * camera_speed;
}

void Camera::onMouseMove(double xpos, double ypos)
{
    static double lastX = 0.0, lastY = 0.0;
    static double yaw = -90.0f;
    static double pitch = 0.0;

    double xoffset = xpos - lastX;
    double yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    double sensitivity = 0.3f;
    yaw += xoffset * sensitivity;
    pitch += yoffset * sensitivity;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    m_Direction.x = (float)(cos(glm::radians(yaw)) * cos(glm::radians(pitch)));
    m_Direction.y = (float)sin(glm::radians(pitch));
    m_Direction.z = (float)(sin(glm::radians(yaw)) * cos(glm::radians(pitch)));
}

void Camera::onMouseScroll(double offset)
{
    m_FoV -= (float)(offset * 1.0);
    if (m_FoV < 15.0f)
        m_FoV = 15.0f;
    if (m_FoV > 45.0f)
        m_FoV = 45.0f;
}

glm::mat4 Camera::LookAt(glm::vec3 position, glm::vec3 direction, glm::vec3 up)
{
    m_Position = position;
    m_Direction = direction;
    m_Up = up;
    return glm::lookAt(m_Position, m_Direction + m_Position, m_Up);
}

glm::mat4 Camera::SetPosition(glm::vec3 position)
{
    m_Position = position;
    return glm::lookAt(m_Position, m_Direction + m_Position, m_Up);
}

glm::mat4 Camera::SetDirection(glm::vec3 direction)
{
    m_Direction = direction;
    return glm::lookAt(m_Position, m_Direction + m_Position, m_Up);
}

glm::mat4 Camera::SetUpVector(const glm::vec3 up)
{
    m_Up = up;
    return glm::lookAt(m_Position, m_Direction + m_Position, m_Up);
}