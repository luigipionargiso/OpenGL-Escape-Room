#pragma once

#include "GamePhase.h"
#include "game/Dialog.h"

class PillowPhase : public GamePhase
{
public:
    PillowPhase();
    ~PillowPhase();
    void HandleInput();
    void HandlePadInput();
    void Update();
    void Draw();

private:
    Dialog* current_dialog_ = nullptr;
};