#include "PlayerPhysicsComponent.h"
#include "game/Game.h"
#include "game/game_object/GameObject.h"

PlayerPhysicsComponent::PlayerPhysicsComponent(GameObject& player)
{
    rigid_body_ = Physics::AddRigidBody(
        &player,
        player.GetPosition(),
        player.GetRotation(),
        50.0f,
        BOX,
        player.GetDimensions() / 2.0f
    );
    Physics::SetRigidBodyAttribute(rigid_body_, RAY_VISIBILITY, false);

    last_positions_[0] = player.GetPosition();
    last_positions_[1] = player.GetPosition();
}

PlayerPhysicsComponent::~PlayerPhysicsComponent()
{
    Physics::RemoveRigidBody(rigid_body_);
}

void PlayerPhysicsComponent::Update(GameObject& player)
{
    /* update player position in the physics world */
    Physics::UpdateRigidBody(rigid_body_, player.GetPosition(), player.GetRotation());

    if (Physics::CheckCollision(rigid_body_))
    {
        glm::vec3 new_pos = player.GetPosition() + (last_positions_[0] - last_positions_[1]) * 1.5f;
        player.SetPosition(new_pos);
        Game::GetInstance().GetActiveCamera().SetPosition(new_pos);
    }
    else
    {
        last_positions_[0] = last_positions_[1];
        last_positions_[1] = player.GetPosition();
    }
}
