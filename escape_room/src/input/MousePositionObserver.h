#pragma once

class MousePositionObserver
{
public:
	virtual ~MousePositionObserver() {}
	virtual void onMouseMove(float xpos, float ypos, bool hovered) = 0;
};