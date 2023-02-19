#pragma once

#include "game/game_object/GameObject.h"
#include "game/lights/AmbientLight.h"
#include "game/lights/PointLight.h"
#include "game/lights/SpotLight.h"

class World
{
public:
	World() = default;
	void Populate();

	std::unordered_map<std::string, GameObject*> objects_;
	AmbientLight* ambient_light_;
	PointLight* point_light_;
	SpotLight* spot_light_;

private:
	void LoadWalls();
	void LoadForniture();
	void LoadMovableObjects();
};