#include "Camera.h"
#include "window/Window.h"

Camera::Camera(glm::vec3 position, glm::vec3 direction, glm::vec3 up)
    : m_Position(position), m_Direction(direction), m_Up(glm::vec3(up)) {}

void Camera::onKeyboard(int key, bool pressed)
{
    glm::vec3 front = m_Direction;
    front.y = 0.0;
    float camera_speed = 2.5f * (GLfloat)Window::GetDeltaTime();

    if (key == GLFW_KEY_W)
        m_Position += camera_speed * front;

    if (key == GLFW_KEY_S)
        m_Position -= camera_speed * front;

    if (key == GLFW_KEY_A)
        m_Position -= glm::normalize(glm::cross(front, m_Up)) * camera_speed;

    if (key == GLFW_KEY_D)
        m_Position += glm::normalize(glm::cross(front, m_Up)) * camera_speed;
}

void Camera::onMouseMove(float xpos, float ypos, bool hovered)
{
    static float lastX = 0.0, lastY = 0.0;
    static float yaw = -90.0f;
    static float pitch;

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 1.0f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    m_Direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    m_Direction.y = sin(glm::radians(pitch));
    m_Direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
}

glm::mat4 Camera::LookAt(glm::vec3 position, glm::vec3 direction, glm::vec3 up)
{
    m_Position = position;
    m_Direction = direction;
    m_Up = up;
    return glm::lookAt(m_Position, m_Direction, m_Up);
}

glm::mat4 Camera::SetPosition(glm::vec3 position)
{
    m_Position = position;
    return glm::lookAt(m_Position, m_Direction, m_Up);
}

glm::mat4 Camera::SetDirection(glm::vec3 direction)
{
    m_Direction = direction;
    return glm::lookAt(m_Position, m_Direction, m_Up);
}

glm::mat4 Camera::SetUpVector(const glm::vec3 up)
{
    m_Up = up;
    return glm::lookAt(m_Position, m_Direction, m_Up);
}
