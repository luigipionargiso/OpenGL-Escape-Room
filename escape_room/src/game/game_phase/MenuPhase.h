#pragma once

#include "GamePhase.h"
#include "engine/Shader.h"
#include "game/HUDElement.h"
#include "game/Game.h"

enum MenuState
{
    PLAY, SETTINGS, CREDITS, CREDITS_PAGE, USE_KEYBOARD, USE_GAMEPAD, KEYBOARD_BACK, GAMEPAD_BACK
};

class MenuPhase : public GamePhase
{
public:
    MenuPhase();
    ~MenuPhase();
    void HandleInput();
    void HandlePadInput();
    void Update();
    void Draw();

private:
    MenuState state_;
    Shader* hud_shader_;
    std::unordered_map<std::string, HUDElement*> hud_elements_;
};