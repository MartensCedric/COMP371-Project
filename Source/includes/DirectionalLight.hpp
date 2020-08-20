#pragma once
#include <glm/glm.hpp>

class DirectionalLight
{
public:
	glm::vec3 position = glm::vec3(0, 15.f, 0);
	glm::vec3 direction = glm::normalize(-position);
	glm::vec3 color = glm::vec3(1.0, 1.0, 1.0);
};