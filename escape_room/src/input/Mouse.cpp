#include "Mouse.h"

void Mouse::ClickNotify(int button, bool pressed)
{
    for (unsigned int i = 0; i < m_ButtonObservers.size(); i++)
        m_ButtonObservers[i]->onMouseClick(button, pressed);
}

void Mouse::PositionNotify(float xpos, float ypos, bool hovered)
{
    for (unsigned int i = 0; i < m_PositionObservers.size(); i++)
        m_PositionObservers[i]->onMouseMove(xpos, ypos, hovered);
}

void Mouse::AddMouseButtonObserver(MouseButtonObserver* observer)
{
    m_ButtonObservers.push_back(observer);
}

void Mouse::RemoveMouseButtonObserver(MouseButtonObserver* observer)
{
    m_ButtonObservers.erase(
        std::remove(m_ButtonObservers.begin(), m_ButtonObservers.end(), observer),
        m_ButtonObservers.end()
    );
}

void Mouse::AddMousePositionObserver(MousePositionObserver* observer)
{
    m_PositionObservers.push_back(observer);
}

void Mouse::RemoveMousePositionObserver(MousePositionObserver* observer)
{
    m_PositionObservers.erase(
        std::remove(m_PositionObservers.begin(), m_PositionObservers.end(), observer),
        m_PositionObservers.end()
    );
}

void Mouse::ProcessInput(Window& window)
{
    auto pos = window.GetCursorPosition();
    PositionNotify(pos.x, pos.y, window.isHovered());

    if (window.GetMouseButton(GLFW_MOUSE_BUTTON_LEFT))
        ClickNotify(GLFW_MOUSE_BUTTON_LEFT, true);
    if (window.GetMouseButton(GLFW_MOUSE_BUTTON_RIGHT))
        ClickNotify(GLFW_MOUSE_BUTTON_RIGHT, true);
}
