#pragma once

#include "game/World.h"
#include "camera/Camera.h"
#include "game_object/GameObject.h"
#include "HUDElement.h"
#include "game_phase/GamePhase.h"

enum PlayerStatus
{
    WALKING, HOLD, EXAMINE
};

class Game
{
public:
    static Game& GetInstance();

    Game(Game const&) = delete;
    void operator=(Game const&) = delete;

    void Update();
    void Draw();

    void ChangePhase(GamePhase* new_phase);
    PlayerStatus& GetPlayerStatus() { return status_; }
    void SetPlayerStatus(PlayerStatus status) { status_ = status; }

    GameObject* GetPickedObject() { return picked_object_; }
    void SetPickedObject(GameObject* obj) { picked_object_ = obj; }

    Camera& GetActiveCamera() { return camera_; }
    World& GetWorld() { return world_; }
    Shader* GetShader(std::string name);

private:
    Game();

    World world_;
    GamePhase* current_phase_;
    PlayerStatus status_;
    Camera camera_;
    std::unordered_map<std::string, Shader*> shaders_;
    std::unordered_map<std::string, HUDElement*> hud_elements_;

    GameObject* picked_object_;
};

