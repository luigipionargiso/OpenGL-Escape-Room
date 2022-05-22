#pragma once

class MouseButtonObserver
{
public:
	virtual ~MouseButtonObserver() {}
	virtual void onMouseClick(int button, bool pressed) = 0;
};