#pragma once
#ifndef _TRACER_H_
#define _TRACER_H_

#include "Sphere.h"
#include "Geometry.h"
#include "Ray.h"
#include "Light.h"

#include <GLM/glm.hpp>
#include <cmath>

class Tracer
{
public:
	glm::vec3 Colour(Ray CreateRay, PointDistance _pD, Light _lightPosition, glm::vec3 _centre, Sphere _colour);// colour / lighting function
};

#endif