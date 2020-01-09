#pragma once
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>
#include <cmath>
#include "Ray.h"

class Camera
{
public:
	Camera();
	void matrixes(glm::mat4 _viewingMatrix, glm::mat4 _projectionMatrix);

	Ray createRay(glm::ivec2 _PixelCoord, glm::ivec2 _windowSize);//create Ray Function

	glm::mat4 viewingMatrix;//view matrix
	glm::mat4 projectionMatrix;//projection matrix

	glm::vec3 rotation;
	glm::vec3 position;
	glm::vec3 scale;

	void setPosition(glm::vec3 _cPosition);
	glm::mat4 getMatrix();
	glm::mat4 getViewingMatrix();
	glm::mat4 getProjectionMatrix(float width, float height);
};
#endif