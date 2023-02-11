#include "Keyboard.h"
#include "../window/Window.h"
#include "GLFW/glfw3.h"

/* initialize the hash map */
std::unordered_map<Key, KeyStatus> Keyboard::keys_ = [] {
    std::unordered_map<Key, KeyStatus> keys_;

    for (int k = KEY_FIRST; k != KEY_LAST; k++)
        keys_[static_cast<Key>(k)] = RELEASE;

    return keys_;
}();

KeyStatus Keyboard::GetKey(Key k)
{
    return keys_.at(k);
}

void Keyboard::PollEvents(Window& w)
{
    keys_[KEY_W] = static_cast<KeyStatus>(glfwGetKey(w.GetGLFWPointer(), GLFW_KEY_W));
    keys_[KEY_A] = static_cast<KeyStatus>(glfwGetKey(w.GetGLFWPointer(), GLFW_KEY_A));
    keys_[KEY_S] = static_cast<KeyStatus>(glfwGetKey(w.GetGLFWPointer(), GLFW_KEY_S));
    keys_[KEY_D] = static_cast<KeyStatus>(glfwGetKey(w.GetGLFWPointer(), GLFW_KEY_D));

    keys_[KEY_Q] = static_cast<KeyStatus>(glfwGetKey(w.GetGLFWPointer(), GLFW_KEY_Q));
}
