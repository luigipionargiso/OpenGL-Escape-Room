#pragma once

class GamePhase
{
public:
    virtual void HandleInput() = 0;
    virtual void Update() = 0;
    virtual void Draw() = 0;
};