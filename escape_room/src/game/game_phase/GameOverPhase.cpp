#include "GameOverPhase.h"
#include "engine/input/Mouse.h"
#include "engine/input/Keyboard.h"
#include "game/GameUtils.h"
#include "game/game_object/PickableInputComponent.h"
#include "game/game_object/PickablePhysicsComponent.h"
#include "GameOverPhase.h"

GameOverPhase::GameOverPhase()
{
}

GameOverPhase::~GameOverPhase()
{
}

void GameOverPhase::HandleInput()
{
}

void GameOverPhase::Update()
{
}

void GameOverPhase::Draw()
{
    Text::Render("You completed the game", -0.3f, 0.0f, 32.0f);
}
