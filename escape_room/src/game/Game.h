#pragma once

#include <chrono>
#include <fstream>
#include "game/World.h"
#include "camera/Camera.h"
#include "game_object/GameObject.h"
#include "HUDElement.h"
#include "game_phase/GamePhase.h"

enum InputDevice
{
    KEYBOARD_AND_MOUSE, GAMEPAD
};

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

    HUDElement* GetHUDElement(std::string name);
    void SetHUDElement(std::string name, HUDElement* hud);

    Camera& GetActiveCamera() { return camera_; }
    World& GetWorld() { return world_; }
    Shader* GetShader(std::string name);
    InputDevice& GetDevice() { return device_; }
    void SetDevice(InputDevice device) { device_ = device; }

    void StartTimer();
    unsigned int start_time_;
    unsigned int current_time_;
    unsigned int last_record_;

private:
    Game();

    InputDevice device_;
    World world_;
    GamePhase* current_phase_;
    PlayerStatus status_;
    Camera camera_;
    std::unordered_map<std::string, Shader*> shaders_;
    std::unordered_map<std::string, HUDElement*> hud_elements_;

    GameObject* picked_object_;
};

