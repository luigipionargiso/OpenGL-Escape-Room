#pragma once

#include "vendor/glm/glm.hpp"
#include "engine/Shader.h"

class PointLight
{
public:
	glm::vec3 position_;
	glm::vec3 diffuse_color_, specular_color_;

	PointLight(glm::vec3 position, glm::vec3 diffuse_color, glm::vec3 specular_color)
		:position_(position), diffuse_color_(diffuse_color), specular_color_(specular_color) {}

	void Draw(Shader& shader)
	{
		shader.setUniform3fv("u_point.position", position_);
		shader.setUniform3fv("u_point.diffuse_col", diffuse_color_);
		shader.setUniform3fv("u_point.specular_col", specular_color_);
	}
};

