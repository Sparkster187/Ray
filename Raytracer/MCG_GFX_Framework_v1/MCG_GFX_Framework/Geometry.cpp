#include "Geometry.h"
#include "Ray.h"
#include <iostream>

PointDistance Geometry::Intersection(Ray _ray, glm::vec3 _sphereCentrePoint, float _radius)
{
	PointDistance pD;
	pD.hit = false;

	//equation variables
	glm::vec3 a = _ray.Origin;
	glm::vec3 P = _sphereCentrePoint;
	glm::vec3 n = _ray.Direction;

	//glm::vec3 P2 = _centrePoint2;
	//find X
	glm::vec3 one = P - a; //(P - a)

	glm::vec3 two = n;//n

	float three = glm::dot((P - a), n); //((P - a )dot n)

	glm::vec3 four = three * two; //((P - a )dot n)  *n

	glm::vec3 X = a + four;

	//float d = glm::length(P - a - four);
	float d = glm::length(P - a - glm::dot((P - a), n) * n);

	//float d2 = glm::length(P2 - a - glm::dot((P2 - a), n) * n);

	if (d <= _radius)
	{
		pD.hit = true;
		pD.PointCoord = _ray.Origin;
		// calculate actual interesection point and return
	}
	
	else if (d > _radius)
	{
		pD.hit = false;
		
	}

	return pD;
};