#pragma once

typedef double GLdouble;

class MousePositionObserver
{
public:
	virtual ~MousePositionObserver() {}
	virtual void onMouseMove(GLdouble xpos, GLdouble ypos) = 0;
};