#pragma once
#ifndef _GEOMETRY_H_
#define _GEOMETRY_H_

#include <GLM/glm.hpp>
#include <cmath>

class Ray;

struct PointDistance
{
	glm::vec3 PointCoord;
	bool hit;
	float DistanceFromCentre;
};

class Geometry
{
public:
	PointDistance Intersection (Ray _ray, glm::vec3 _sphereCentrePoint, float _radius);
	
	
};
#endif // !_GEOMETRY_H_
