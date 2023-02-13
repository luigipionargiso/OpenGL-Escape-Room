#pragma once

#include "game/World.h"
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

    void Populate();
    void Update();
    void Draw();

    Camera& GetActiveCamera() { return camera_; }
    GameStatus GetStatus() { return status_; }
    Shader* GetShader(std::string name);

private:
    Game();
    void Pick(GameObject* picked_object);

    World world_;
    GamePhase phase_;
    GameStatus status_;
    Camera camera_;
    std::unordered_map<std::string, Shader*> shaders_;

    GameObject* picked_object_;
};

