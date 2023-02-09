#pragma once

#include "World.h"

enum GamePhase
{
    START_MENU, PLAYING, PAUSED, GAMEOVER
};

class Game
{
public:
    static Game& getInstance();

    Game(Game const&) = delete;
    void operator=(Game const&) = delete;

    void Update();

private:
    Game() {}
    GamePhase phase_;
	World world_;
};

