#include "Mouse.h"

GLdouble scroll_offset = 0.0;
GLdouble last_scroll = 0.0;

void Mouse::ClickNotify(int button, bool pressed)
{
    for (unsigned int i = 0; i < m_ButtonObservers.size(); i++)
        m_ButtonObservers[i]->onMouseClick(button, pressed);
}

void Mouse::PositionNotify(GLdouble xpos, GLdouble ypos)
{
    for (unsigned int i = 0; i < m_PositionObservers.size(); i++)
        m_PositionObservers[i]->onMouseMove(xpos, ypos);
}

void Mouse::ScrollNotify(GLdouble offset)
{
    for (unsigned int i = 0; i < m_ScrollObservers.size(); i++)
        m_ScrollObservers[i]->onMouseScroll(offset);
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

void Mouse::AddMouseScrollObserver(MouseScrollObserver* observer)
{
    m_ScrollObservers.push_back(observer);
}

void Mouse::RemoveMouseScrollObserver(MouseScrollObserver* observer)
{
    m_ScrollObservers.erase(
        std::remove(m_ScrollObservers.begin(), m_ScrollObservers.end(), observer),
        m_ScrollObservers.end()
    );
}

void Mouse::ProcessInput(Window& window)
{
    if (window.IsHovered()) {
        /* Cursor position */
        Point2D pos = window.GetCursorPosition();
        PositionNotify(pos.x, pos.y);

        /* Mouse Scroll */
        //if (scroll_offset != last_scroll) {
            ScrollNotify(scroll_offset);
            last_scroll = scroll_offset;
        //}

        /* Mouse buttons*/
        static bool left_pressed = false;
        static bool right_pressed = false;
        /* da eliminare */
        if (!left_pressed && window.GetMouseButton(GLFW_MOUSE_BUTTON_LEFT)) {
            ClickNotify(GLFW_MOUSE_BUTTON_LEFT, true);
            left_pressed = true;
        }
        else if (left_pressed && !window.GetMouseButton(GLFW_MOUSE_BUTTON_LEFT)) {
            ClickNotify(GLFW_MOUSE_BUTTON_LEFT, false);
            left_pressed = false;
        }

        if (!right_pressed && window.GetMouseButton(GLFW_MOUSE_BUTTON_RIGHT)) {
            ClickNotify(GLFW_MOUSE_BUTTON_RIGHT, true);
            right_pressed = true;
        }
        else if (right_pressed && !window.GetMouseButton(GLFW_MOUSE_BUTTON_RIGHT)) {
            ClickNotify(GLFW_MOUSE_BUTTON_RIGHT, false);
            right_pressed = false;
        }
    }
}