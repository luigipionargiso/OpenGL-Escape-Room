#include "PlayerPhysicsComponent.h"
#include "game/Game.h"

void PlayerPhysicsComponent::Update(GameObject& player)
{
    /* update player position in the physics world */
    Physics::UpdateRigidBody(rigid_body_, player.GetPosition(), player.GetRotation());

    if (Physics::CheckCollision(rigid_body_))
    {
        glm::vec3 new_pos = player.GetPosition() + (last_position_ - player.GetPosition()) * 1.5f;

        Physics::UpdateRigidBody(rigid_body_, new_pos, player.GetRotation());
        player.SetPosition(new_pos);
        Game::GetInstance().GetActiveCamera().SetPosition(new_pos);
        last_position_ = new_pos;
    }
    else
    {
        last_position_ = player.GetPosition();
    }
}
