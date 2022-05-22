#pragma once

#include <vector>
#include "MouseButtonObserver.h"
#include "MousePositionObserver.h"
#include "../window/Window.h"

class Mouse
{
private:
	std::vector<MouseButtonObserver*> m_ButtonObservers;
	std::vector<MousePositionObserver*> m_PositionObservers;
protected:
	void ClickNotify(int button, bool pressed);
	void PositionNotify(float xpos, float ypos, bool hovered);
public:
	void AddMouseButtonObserver(MouseButtonObserver* observer);
	void RemoveMouseButtonObserver(MouseButtonObserver* observer);

	void AddMousePositionObserver(MousePositionObserver* observer);
	void RemoveMousePositionObserver(MousePositionObserver* observer);

	void ProcessInput(Window& window);
};