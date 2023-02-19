#pragma once

#include "GamePhase.h"
#include "game/Dialog.h"

class GameOverPhase : public GamePhase
{
public:
    GameOverPhase();
    ~GameOverPhase();
    void HandleInput();
    void Update();
    void Draw();

private:
    Dialog* current_dialog_ = nullptr;
};