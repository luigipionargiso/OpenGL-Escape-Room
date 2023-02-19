#pragma once

#include "GamePhase.h"
#include "game/Dialog.h"

class LightsOnPhase : public GamePhase
{
public:
    LightsOnPhase();
    ~LightsOnPhase();
    void HandleInput();
    void Update();
    void Draw();

private:
    Dialog* current_dialog_ = nullptr;
};