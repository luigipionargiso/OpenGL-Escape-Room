#pragma once

typedef double GLdouble;

class MouseScrollObserver
{
public:
	virtual ~MouseScrollObserver() {}
	virtual void onMouseScroll(GLdouble offset) = 0;
};