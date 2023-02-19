#pragma once

#include "GamePhase.h"
#include "game/Dialog.h"

class KeyPhase : public GamePhase
{
public:
    KeyPhase();
    ~KeyPhase();
    void HandleInput();
    void Update();
    void Draw();

private:
    Dialog* current_dialog_ = nullptr;
};