#pragma once
#include "Ray.h"

struct Light
{
	glm::vec3 Colour;
	glm::vec3 lightPosition;
	glm::vec3 lightColour;
};
