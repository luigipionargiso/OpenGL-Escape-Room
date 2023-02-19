#include "KeyPhase.h"
#include "engine/input/Mouse.h"
#include "engine/input/Keyboard.h"
#include "game/GameUtils.h"
#include "game/game_object/PickableInputComponent.h"
#include "game/game_object/PickablePhysicsComponent.h"
#include "GameOverPhase.h"

KeyPhase::KeyPhase()
{
    Game& game = Game::GetInstance();
    World& world = game.GetWorld();

    game.SetPlayerStatus(HOLD);
    world.objects_["donut"]->SetInputComponent(new PickableInputComponent());
    game.SetPickedObject(world.objects_["donut"]);

    current_dialog_ = new Dialog("You have found the key!");
}

KeyPhase::~KeyPhase()
{
    delete(current_dialog_);
}

void KeyPhase::HandleInput()
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
                [selected](const auto& value) { return value.second == selected; }
            );

            if (result != world.objects_.end() && CheckDistanceLimit(*result->second, *world.objects_["player"]))
            {
                if (result->first.compare("porta") == 0)
                {
                    game.ChangePhase(new GameOverPhase());
                }
                else if (result->first.compare("finestra") == 0)
                {
                    current_dialog_ = new Dialog("The outside world seems to have disappeared.");
                }
                else if (result->first.compare("donut") == 0 && game.GetPlayerStatus() == WALKING)
                {
                    game.SetPlayerStatus(HOLD);
                    world.objects_["donut"]->SetInputComponent(new PickableInputComponent());
                    game.SetPickedObject(world.objects_["donut"]);
                }
                else if (result->first.compare("ball") == 0 && game.GetPlayerStatus() == WALKING)
                {
                    game.SetPlayerStatus(HOLD);
                    world.objects_["ball"]->SetInputComponent(new PickableInputComponent());
                    game.SetPickedObject(world.objects_["ball"]);
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
        game.GetPickedObject()->SetInputComponent(nullptr);
        game.GetPickedObject()->SetPosition(game.GetActiveCamera().GetPosition() + game.GetActiveCamera().GetDirection());
        game.GetPickedObject()->GetPhysicsComponent()->SetLinearVelocity(
            game.GetActiveCamera().GetDirection() * 3.0f
        );
        game.GetPickedObject()->GetPhysicsComponent()->RestartSimulation(*game.GetPickedObject());
        game.SetPickedObject(nullptr);
    }
}

void KeyPhase::Update()
{
    Game& game = Game::GetInstance();

    game.GetActiveCamera().Update();

    for (auto& obj : game.GetWorld().objects_)
        obj.second->Update();
}

void KeyPhase::Draw()
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
}
