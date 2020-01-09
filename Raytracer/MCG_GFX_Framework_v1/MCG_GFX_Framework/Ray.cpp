#include "Ray.h"

Ray::Ray(glm::ivec2 _Origin, glm::vec3 _Direction)
{
	//Origin = _Origin;
	Origin.x = _Origin.x;
	Origin.y = _Origin.y;

	Direction = _Direction;
}

Ray::~Ray()
{
}