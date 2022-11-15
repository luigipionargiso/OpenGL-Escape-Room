#pragma once

#include <vector>
#include "KeyObserver.h"
#include "engine/window/Window.h"

class Keyboard
{
private:
	std::vector<KeyObserver*> observers;
protected:
	void KeyNotify(int key, bool pressed);
public:
	void AddKeyObserver(KeyObserver* observer);
	void RemoveKeyObserver(KeyObserver* observer);

	void ProcessInput(Window& window);
};
