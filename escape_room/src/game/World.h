#pragma once

#include <unordered_map>
#include "GameObject.h"

class World
{
public:
	std::unordered_map<std::string, GameObject*> objects_;

	void Populate(Shader& shader);
	void Draw(Shader& shader);

private:
};