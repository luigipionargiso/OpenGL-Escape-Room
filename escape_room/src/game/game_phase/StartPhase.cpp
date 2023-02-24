#include "StartPhase.h"
#include "TorchPhase.h"
#include "engine/input/Mouse.h"
#include "engine/input/Gamepad.h"
#include "engine/physics/Physics.h"
#include "game/Game.h"
#include "game/game_object/GameObject.h"
#include "game/GameUtils.h"
#include "game/camera/GamepadCameraInput.h"
#include <iostream>

StartPhase::StartPhase()
{
    Game& game = Game::GetInstance();

    game.StartTimer();

    if (game.GetDevice() == GAMEPAD)
    {
        game.GetActiveCamera().SetInputComponent(new GamepadCameraInput());
        game.SetHUDElement("hud", new HUDElement(new Texture("res/textures/hud_gamepad.png", IMAGE), game.GetShader("hud"), -0.99f));
    }
    else
    {
        game.SetHUDElement("hud", new HUDElement(new Texture("res/textures/hud.png", IMAGE), game.GetShader("hud"), -0.99f));
    }
}

StartPhase::~StartPhase()
{
    delete current_dialog_;
}

void StartPhase::HandleInput()
{
    static Game& game = Game::GetInstance();
    static World& world = game.GetWorld();
	static bool left_was_released = true;

    if (Mouse::GetMouseButton(MOUSE_BUTTON_LEFT) == RELEASE_M)
        left_was_released = true;

    if (Mouse::GetMouseButton(MOUSE_BUTTON_LEFT) == PRESS_M && left_was_released)
    {
        left_was_released = false;

        if (current_dialog_ != nullptr)
        {
            delete(current_dialog_);
            current_dialog_ = nullptr;
        }
        else
        {
            GameObject* selected = (GameObject*)Physics::CastRay(
                game.GetActiveCamera().GetPosition(),
                game.GetActiveCamera().GetDirection()
            );

            auto result = std::find_if(
                world.objects_.begin(),
                world.objects_.end(),
                [selected](const auto& value) {return value.second == selected; }
            );

            if (result != world.objects_.end() && CheckDistanceLimit(*result->second, *world.objects_["player"]))
            {
                if (result->first.compare("torcia") == 0)
                {
                    game.ChangePhase(new TorchPhase());
                    return;
                }
                else if (result->first.compare("porta") == 0)
                {
                    current_dialog_ = new Dialog("The door is locked.");
                }
                else if (result->first.compare("finestra") == 0)
                {
                    current_dialog_ = new Dialog("The outside world seems to have disappeared.");
                }
            }
        }
    }
}

void StartPhase::HandlePadInput()
{
    static Game& game = Game::GetInstance();
    static World& world = game.GetWorld();
    static bool a_was_released = true;

    if (Gamepad::GetButtonStatus(BUTTON_A) == RELEASE_B)
        a_was_released = true;

    if (Gamepad::GetButtonStatus(BUTTON_A) == PRESS_B && a_was_released)
    {
        a_was_released = false;

        if (current_dialog_ != nullptr)
        {
            delete(current_dialog_);
            current_dialog_ = nullptr;
        }
        else
        {
            GameObject* selected = (GameObject*)Physics::CastRay(
                game.GetActiveCamera().GetPosition(),
                game.GetActiveCamera().GetDirection()
            );

            auto result = std::find_if(
                world.objects_.begin(),
                world.objects_.end(),
                [selected](const auto& value) {return value.second == selected; }
            );

            if (result != world.objects_.end() && CheckDistanceLimit(*result->second, *world.objects_["player"]))
            {
                if (result->first.compare("torcia") == 0)
                {
                    game.ChangePhase(new TorchPhase());
                    return;
                }
                else if (result->first.compare("porta") == 0)
                {
                    current_dialog_ = new Dialog("The door is locked.");
                }
                else if (result->first.compare("finestra") == 0)
                {
                    current_dialog_ = new Dialog("The outside world seems to have disappeared.");
                }
            }
        }
    }
}

void StartPhase::Update()
{
    Game::GetInstance().GetActiveCamera().Update();

    for (auto& obj : Game::GetInstance().GetWorld().objects_)
        obj.second->Update();

    /* calculate elapsed time */
    auto time = std::chrono::system_clock::now();
    unsigned int time_sec = static_cast<unsigned int>(time.time_since_epoch().count())
        * std::chrono::system_clock::period::num
        / static_cast<unsigned int>(std::chrono::system_clock::period::den);

    Game::GetInstance().current_time_ = time_sec - Game::GetInstance().start_time_;
}

void StartPhase::Draw()
{
    Game& game = Game::GetInstance();
    Shader& shader = *game.GetShader("basic");

    /* draw camera */
    game.GetActiveCamera().Draw(shader);

    /* draw lights */
    game.GetWorld().ambient_light_->Draw(shader);
    game.GetWorld().point_light_->Draw(shader);
    game.GetWorld().spot_light_->Draw(shader);

    /* draw world */
    for (auto& obj : game.GetWorld().objects_)
        obj.second->Draw(shader);

    /* draw dialog */
    if (current_dialog_)
        current_dialog_->Draw(*game.GetShader("hud"));

    DrawTime();
}
