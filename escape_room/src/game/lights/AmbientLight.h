#pragma once

#include "vendor/glm/glm.hpp"
#include "engine/Shader.h"

class AmbientLight
{
public:
	glm::vec3 color_;

	AmbientLight(glm::vec3 color)
		:color_(color) {}

	void Draw(Shader& shader)
	{
		shader.setUniform3fv("u_ambient", color_);
	}
};

