#pragma once

#include "GamePhase.h"
#include "game/Dialog.h"

class StartPhase : public GamePhase
{
public:
    StartPhase();
    ~StartPhase();
    void HandleInput();
    void HandlePadInput();
    void Update();
    void Draw();

private:
    Dialog* current_dialog_ = nullptr;
};