#include "GameOverPhase.h"
#include "engine/input/Mouse.h"
#include "engine/input/Keyboard.h"
#include "game/GameUtils.h"
#include "game/game_object/PickableInputComponent.h"
#include "game/game_object/PickablePhysicsComponent.h"
#include "GameOverPhase.h"
#include <iostream>

GameOverPhase::GameOverPhase()
{
    Game& game = Game::GetInstance();
    game.GetHUDElement("hud")->SetVisibility(false);

    /* calculate end time */
    auto time = std::chrono::system_clock::now();
    unsigned int end_time = static_cast<unsigned int>(time.time_since_epoch().count())
        * std::chrono::system_clock::period::num
        / static_cast<unsigned int>(std::chrono::system_clock::period::den);

    elapsed_time_ = end_time - game.start_time_;

    if (elapsed_time_ < game.last_record_ || game.last_record_ == 0)
    {
        new_record_ = true;

        std::ofstream file("res/record.txt");
        if (!file.is_open()) {
            std::cerr << "Failed to open record file!" << std::endl;
            exit(EXIT_FAILURE);
        }

        file << elapsed_time_;

        file.close();
    }
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
    Text::Render("You completed the game in", -0.40f, 0.0f, 32.0f);

    int min = elapsed_time_ / 60;
    int sec = elapsed_time_ % 60;
    std::string record =  TwoDigitsFormat(min) + ":" + TwoDigitsFormat(sec);
    Text::Render(record.c_str(), -0.08f, -0.2f, 32.0f);

    if(new_record_)
        Text::Render("(new record!)", -0.20f, -0.4f, 32.0f);
}
