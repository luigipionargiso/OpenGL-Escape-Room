#pragma once

#include "GamePhase.h"
#include "game/Dialog.h"

class TorchPhase : public GamePhase
{
public:
    TorchPhase();
    ~TorchPhase();
    void HandleInput();
    void Update();
    void Draw();

private:
    Dialog* current_dialog_ = nullptr;
    GameObject* picked_object_ = nullptr;
};