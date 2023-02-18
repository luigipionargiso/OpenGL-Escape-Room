#pragma once

#include "vendor/glm/glm.hpp"
#include "engine/Shader.h"

class SpotLight
{
public:
	glm::vec3 position_;
	glm::vec3 direction_;
	float cutoff_;
	glm::vec3 diffuse_color_, specular_color_;

	SpotLight(glm::vec3 position, glm::vec3 direction, float cutoff, glm::vec3 diffuse_color, glm::vec3 specular_color)
		:position_(position), direction_(direction), cutoff_(cutoff), diffuse_color_(diffuse_color), specular_color_(specular_color) {}

	void Draw(Shader& shader)
	{
		shader.setUniform3fv("u_spot.position", position_);
		shader.setUniform3fv("u_spot.direction", direction_);
		shader.setUniform1f("u_spot.cutoff", cutoff_);
		shader.setUniform3fv("u_spot.diffuse_col", diffuse_color_);
		shader.setUniform3fv("u_spot.specular_col", specular_color_);
	}
};

