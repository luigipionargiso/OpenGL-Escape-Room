#pragma once

#include "GamePhase.h"
#include "game/Dialog.h"

class GameOverPhase : public GamePhase
{
public:
    GameOverPhase();
    ~GameOverPhase();
    void HandleInput();
    void HandlePadInput() {}
    void Update();
    void Draw();

private:
    Dialog* current_dialog_ = nullptr;
    unsigned int elapsed_time_;
    bool new_record_ = false;
};