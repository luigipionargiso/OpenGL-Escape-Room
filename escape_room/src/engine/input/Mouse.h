#pragma once

#include <vector>
#include "MouseButtonObserver.h"
#include "MousePositionObserver.h"
#include "MouseScrollObserver.h"
#include "engine/window/Window.h"

class Mouse
{
private:
	std::vector<MouseButtonObserver*> m_ButtonObservers;
	std::vector<MousePositionObserver*> m_PositionObservers;
	std::vector<MouseScrollObserver*> m_ScrollObservers;
protected:
	void ClickNotify(int button, bool pressed);
	void PositionNotify(GLdouble xpos, GLdouble ypos);
	void ScrollNotify(GLdouble offset);
public:
	void AddMouseButtonObserver(MouseButtonObserver* observer);
	void RemoveMouseButtonObserver(MouseButtonObserver* observer);

	void AddMousePositionObserver(MousePositionObserver* observer);
	void RemoveMousePositionObserver(MousePositionObserver* observer);

	void AddMouseScrollObserver(MouseScrollObserver* observer);
	void RemoveMouseScrollObserver(MouseScrollObserver* observer);

	void ProcessInput(Window& window);
};