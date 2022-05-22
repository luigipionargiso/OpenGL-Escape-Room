#include <algorithm>
#include "Keyboard.h"

void Keyboard::KeyNotify(int key, bool pressed)
{
    for (unsigned int i = 0; i < observers.size(); i++)
        observers[i]->onKeyboard(key, pressed);
}

void Keyboard::AddKeyObserver(KeyObserver* observer)
{
    observers.push_back(observer);
}

void Keyboard::RemoveKeyObserver(KeyObserver* observer)
{
    observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
}

void Keyboard::ProcessInput(Window& window)
{
    if (window.GetKey(GLFW_KEY_W))
        KeyNotify(GLFW_KEY_W, true);
    if (window.GetKey(GLFW_KEY_A))
        KeyNotify(GLFW_KEY_A, true);
    if (window.GetKey(GLFW_KEY_S))
        KeyNotify(GLFW_KEY_S, true);
    if (window.GetKey(GLFW_KEY_D))
        KeyNotify(GLFW_KEY_D, true);
}
