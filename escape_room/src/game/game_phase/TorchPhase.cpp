#include "TorchPhase.h"
#include "engine/input/Mouse.h"
#include "engine/input/Keyboard.h"
#include "engine/physics/Physics.h"
#include "game/Game.h"
#include "game/game_object/GameObject.h"
#include "game/game_object/PickableInputComponent.h"

TorchPhase::TorchPhase()
{
	Game& game = Game::GetInstance();

	/* delete the torch */
	delete(game.GetWorld().objects_["torch"]);
	game.GetWorld().objects_.erase("torch");

    current_dialog_ = new Dialog("You have obtained a torch!");
}

TorchPhase::~TorchPhase()
{
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

            if (result != world.objects_.end())
            {
                if (result->first.compare("cuscino") == 0)
                {
                    world.objects_["cuscino"]->SetInputComponent(new PickableInputComponent());
                    //game.ChangePhase(new PillowPhase());
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
        picked_object_->SetInputComponent(nullptr);
        picked_object_->GetPhysicsComponent()->RestartSimulation();
    }
    else if (game.GetPlayerStatus() == HOLD && Mouse::GetMouseButton(MOUSE_BUTTON_LEFT) == PRESS_M)
    {
        /* throw object */
        game.SetPlayerStatus(WALKING);
        picked_object_->SetInputComponent(nullptr);
        picked_object_->GetPhysicsComponent()->SetLinearVelocity(
            game.GetActiveCamera().GetDirection() * 3.0f
        );
        picked_object_->GetPhysicsComponent()->RestartSimulation();
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
}
