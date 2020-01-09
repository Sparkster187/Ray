#pragma once
#ifndef _SPHERE_H_
#define _SPHERE_H_

#include <GLM/glm.hpp>
#include <cmath>

class Ray;

class Sphere
{
public:
	glm::vec3 sphereCentrepoint;//variable to store the centre point of the sphere
	glm::vec3 Colour;//variable to store the colour of the sphere
};
#endif // !_SPHERE_H_
