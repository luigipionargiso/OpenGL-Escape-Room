#pragma once

#include <unordered_map>
#include "engine/window/Window.h"

enum Key
{
	KEY_FIRST,
	KEY_W, KEY_A, KEY_S, KEY_D, KEY_Q,
	KEY_LAST
};

enum KeyStatus
{
	RELEASE,
	PRESS
};

class Keyboard
{
public:
	static KeyStatus GetKey(Key k);
	static void PollEvents(Window& w);
private:
	static std::unordered_map<Key, KeyStatus> keys_;
};