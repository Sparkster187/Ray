#pragma once
#ifndef _RAY_H_
#define _RAY_H_

#include <GLM/glm.hpp>
#include <cmath>


class Ray
{
public:
	Ray(glm::ivec2 _pixelPosition, glm::vec3 _Direction);
	~Ray();
	glm::vec3 Origin;
	glm::vec3 Direction;
};
#endif