#pragma once

#include "GamePhase.h"
#include "game/Dialog.h"

class BallPhase : public GamePhase
{
public:
    BallPhase();
    ~BallPhase();
    void HandleInput();
    void Update();
    void Draw();

private:
    Dialog* current_dialog_ = nullptr;
};