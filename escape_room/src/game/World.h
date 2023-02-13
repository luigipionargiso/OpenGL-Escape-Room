#pragma once

#include "game/game_object/GameObject.h"
#include "game/lights/AmbientLight.h"
#include "game/lights/PointLight.h"

class World
{
public:
	World() = default;
	void Populate();

	std::unordered_map<std::string, GameObject*> objects_;
	std::unordered_map<std::string, PointLight*> point_lights_;
	AmbientLight* ambient_light_;

};