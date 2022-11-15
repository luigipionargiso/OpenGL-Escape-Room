#pragma once

class KeyObserver
{
public:
	virtual ~KeyObserver() {}
	virtual void onKeyboard(int key, bool pressed) = 0;
};