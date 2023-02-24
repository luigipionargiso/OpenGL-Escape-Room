#include "TorchPhase.h"
#include "engine/input/Mouse.h"
#include "engine/input/Keyboard.h"
#include "engine/input/Gamepad.h"
#include "engine/physics/Physics.h"
#include "game/Game.h"
#include "game/game_object/GameObject.h"
#include "game/game_object/PickableInputComponent.h"
#include "PillowPhase.h"
#include "game/GameUtils.h"

TorchPhase::TorchPhase()
{
	Game& game = Game::GetInstance();

    /* lower ambient light */
    game.GetWorld().ambient_light_->color_ = glm::vec3(0.1f);

	/* delete the torch */
	delete(game.GetWorld().objects_["torcia"]);
	game.GetWorld().objects_.erase("torcia");

    /* replace the wall */
    game.GetWorld().objects_["parete_frontale"]->SetVisibility(false);
    game.GetWorld().objects_["parete_frontale_VAR"]->SetVisibility(true);

    current_dialog_ = new Dialog("You have obtained a torch!");
}

TorchPhase::~TorchPhase()
{
    delete(current_dialog_);
}

void TorchPhase::HandleInput()
{
    static Game& game = Game::GetInstance();
    static World& world = game.GetWorld();
    static bool left_was_released = false;
    static bool e_was_released = true;

    if (Mouse::GetMouseButton(MOUSE_BUTTON_LEFT) == RELEASE_M)
        left_was_released = true;
    if (Keyboard::GetKey(KEY_E) == RELEASE)
        e_was_released = true;

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
                if (result->first.compare("cuscino") == 0)
                {
                    game.ChangePhase(new PillowPhase());
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
                else if (result->first.compare("libro_zelda") == 0 && game.GetPlayerStatus() == WALKING)
                {
                    game.SetPlayerStatus(HOLD);
                    world.objects_["libro_zelda"]->SetInputComponent(new PickableInputComponent());
                    game.SetPickedObject(world.objects_["libro_zelda"]);
                }
            }
        }
    }

    if (Keyboard::GetKey(KEY_E) == PRESS && e_was_released)
    {
        e_was_released = false;
        if (game.GetPlayerStatus() == HOLD) game.SetPlayerStatus(EXAMINE);
        else if (game.GetPlayerStatus() == EXAMINE) game.SetPlayerStatus(HOLD);
    }

    if (game.GetPlayerStatus() == HOLD && Keyboard::GetKey(KEY_SPACE) == PRESS)
    {
        /* drop object */
        game.SetPlayerStatus(WALKING);
        game.GetPickedObject()->SetInputComponent(nullptr);
        game.GetPickedObject()->GetPhysicsComponent()->RestartSimulation(*game.GetPickedObject());
        game.SetPickedObject(nullptr);
    }
    else if (game.GetPlayerStatus() == HOLD && Mouse::GetMouseButton(MOUSE_BUTTON_RIGHT) == PRESS_M)
    {
        /* throw object */
        game.SetPlayerStatus(WALKING);
        game.GetPickedObject()->SetPosition(game.GetActiveCamera().GetPosition() + game.GetActiveCamera().GetDirection());
        game.GetPickedObject()->SetInputComponent(nullptr);
        game.GetPickedObject()->GetPhysicsComponent()->SetLinearVelocity(
            game.GetActiveCamera().GetDirection() * 3.0f
        );
        game.GetPickedObject()->GetPhysicsComponent()->RestartSimulation(*game.GetPickedObject());
        game.SetPickedObject(nullptr);
    }
}

void TorchPhase::HandlePadInput()
{
    static Game& game = Game::GetInstance();
    static World& world = game.GetWorld();
    static bool a_was_released = false;
    static bool x_was_released = true;

    if (Gamepad::GetButtonStatus(BUTTON_A) == RELEASE_B)
        a_was_released = true;
    if (Gamepad::GetButtonStatus(BUTTON_X) == RELEASE_B)
        x_was_released = true;

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
                if (result->first.compare("cuscino") == 0)
                {
                    game.ChangePhase(new PillowPhase());
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
                else if (result->first.compare("libro_zelda") == 0 && game.GetPlayerStatus() == WALKING)
                {
                    game.SetPlayerStatus(HOLD);
                    world.objects_["libro_zelda"]->SetInputComponent(new PickableInputComponent());
                    game.SetPickedObject(world.objects_["libro_zelda"]);
                }
            }
        }
    }

    if (Gamepad::GetButtonStatus(BUTTON_X) == PRESS_B && x_was_released)
    {
        x_was_released = false;
        if (game.GetPlayerStatus() == HOLD) game.SetPlayerStatus(EXAMINE);
        else if (game.GetPlayerStatus() == EXAMINE) game.SetPlayerStatus(HOLD);
    }

    if (game.GetPlayerStatus() == HOLD && Gamepad::GetButtonStatus(LEFT_BUMPER) == PRESS_B)
    {
        /* drop object */
        game.SetPlayerStatus(WALKING);
        game.GetPickedObject()->SetInputComponent(nullptr);
        game.GetPickedObject()->GetPhysicsComponent()->RestartSimulation(*game.GetPickedObject());
        game.SetPickedObject(nullptr);
    }
    else if (game.GetPlayerStatus() == HOLD && Gamepad::GetButtonStatus(RIGHT_BUMPER) == PRESS_B)
    {
        /* throw object */
        game.SetPlayerStatus(WALKING);
        game.GetPickedObject()->SetPosition(game.GetActiveCamera().GetPosition() + game.GetActiveCamera().GetDirection());
        game.GetPickedObject()->SetInputComponent(nullptr);
        game.GetPickedObject()->GetPhysicsComponent()->SetLinearVelocity(
            game.GetActiveCamera().GetDirection() * 3.0f
        );
        game.GetPickedObject()->GetPhysicsComponent()->RestartSimulation(*game.GetPickedObject());
        game.SetPickedObject(nullptr);
    }
}

void TorchPhase::Update()
{
	Game& game = Game::GetInstance();

	game.GetActiveCamera().Update();

	for (auto& obj : game.GetWorld().objects_)
		obj.second->Update();

	game.GetWorld().spot_light_->position_ = game.GetActiveCamera().GetPosition();
	game.GetWorld().spot_light_->direction_ = glm::normalize(game.GetActiveCamera().GetDirection());

    /* calculate elapsed time */
    auto time = std::chrono::system_clock::now();
    unsigned int time_sec = static_cast<unsigned int>(time.time_since_epoch().count())
        * std::chrono::system_clock::period::num
        / static_cast<unsigned int>(std::chrono::system_clock::period::den);

    Game::GetInstance().current_time_ = time_sec - Game::GetInstance().start_time_;
}

void TorchPhase::Draw()
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
