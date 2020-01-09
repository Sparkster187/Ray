#include "Tracer.h"


glm::vec3 Tracer::Colour(Ray CreateRay, PointDistance _pD, Light _light, glm::vec3 _centre, Sphere _colour)
{
	
	glm::vec3 sphereCentre = _centre;// holds the value of the centre of the sphere
	glm::vec3 IntersectPoint = _pD.PointCoord;// holds the point coordinates of the ray when it intersects the sphere
	glm::vec3 lightPosition = _light.lightPosition; // holds the lights position
	glm::vec3 directionalVector = glm::normalize(lightPosition - IntersectPoint);// calculates the directional vector of the light
	glm::vec3 surfaceNormal = glm::normalize(IntersectPoint - sphereCentre);//calculates the surface normal of the sphere
	glm::vec3 diffuse = glm::max(glm::dot(directionalVector, surfaceNormal), 0.0f) * _colour.Colour * _light.lightColour;//calculate the value of the diffuse lighting by finding the dot product of the directional vector and the surface normal 

	return diffuse;//returns the diffuse value
};
