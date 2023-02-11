#pragma once

#include "camera/Camera.h"
#include "game_object/GameObject.h"
#include "lights/PointLight.h"
#include "lights/AmbientLight.h"

enum GameStatus
{
    WALKING, HOLD, EXAMINE
};

enum GamePhase
{
    START_MENU, PLAYING, PAUSED, GAMEOVER
};

class Game
{
public:
    static Game& GetInstance();

    Game(Game const&) = delete;
    void operator=(Game const&) = delete;

    void Update();
    void Draw();

    Camera& GetActiveCamera() { return camera_; }

    GameStatus GetStatus() { return status_; }

private:
    Game();
    void Populate();
    void Pick(GameObject* picked_object);

    GamePhase phase_;
    GameStatus status_;
    Camera camera_;
    std::unordered_map<std::string, GameObject*> world_;
    std::unordered_map<std::string, Shader*> shaders_;
    std::unordered_map<std::string, PointLight*> point_lights_;
    AmbientLight* ambient_light_;

    GameObject* picked_object_;
};

