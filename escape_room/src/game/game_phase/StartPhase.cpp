#include "StartPhase.h"
#include "TorchPhase.h"
#include "engine/input/Mouse.h"
#include "engine/physics/Physics.h"
#include "game/Game.h"
#include "game/game_object/GameObject.h"

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

            if (result != world.objects_.end())
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
            }
        }
    }
}		

void StartPhase::Update()
{
    Game::GetInstance().GetActiveCamera().Update();

    for (auto& obj : Game::GetInstance().GetWorld().objects_)
        obj.second->Update();
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
}
