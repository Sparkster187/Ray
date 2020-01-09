#include "Camera.h"


Camera::Camera()
{
	viewingMatrix = getViewingMatrix();//has the same value as the matrix returned by getViewingMatrix
	projectionMatrix = getProjectionMatrix(640, 480);// has the 
}

void Camera::setPosition(glm::vec3 _cPosition)
{
	position = _cPosition;
}

glm::mat4 Camera::getMatrix()
{
	glm::mat4 Mat = glm::mat4(1.0f);
	Mat = glm::translate(Mat, position);

	/*Mat = glm::rotate(Mat, rotation.x, glm::vec3(1, 0, 0));
	Mat = glm::rotate(Mat, rotation.y, glm::vec3(0, 1, 0));
	Mat = glm::rotate(Mat, rotation.z, glm::vec3(0, 0, 1));

	Mat = glm::scale(Mat, scale);*/

	return Mat;
}

glm::mat4 Camera::getViewingMatrix()
{
	glm::mat4 tmp = getMatrix();
	return glm::inverse(tmp);
}

glm::mat4 Camera::getProjectionMatrix(float width, float height)
{
	glm::mat4 rtn = glm::perspective(glm::radians(45.0f), width / height, 0.1f, 100.0f);
	return rtn;
}
Ray Camera::createRay(glm::ivec2 _PixelCoord, glm::ivec2 _windowSize)
{
	glm::vec2 screen;
	glm::vec4 nearPlane;
	glm::vec4 farPlane;

	screen.x = (((float)_PixelCoord.x / (float)_windowSize.x)* 2.0f) - 1.0f;
	screen.y = (((float)_PixelCoord.y / (float)_windowSize.y)* 2.0f) - 1.0f;

	nearPlane = glm::vec4(screen.x, screen.y, -1.0f, -1.0f);
	farPlane = glm::vec4(screen.x, screen.y, 1.0f, -1.0f);

	nearPlane = glm::inverse(projectionMatrix) * nearPlane;
	nearPlane = glm::inverse(viewingMatrix) * nearPlane;
	nearPlane /= nearPlane.w;
	
	farPlane = glm::inverse(projectionMatrix) * farPlane;
	farPlane = glm::inverse(viewingMatrix) * farPlane;
	farPlane /= farPlane.w;

	glm::vec3 origin = glm::vec3(nearPlane);
	glm::vec3 direction = glm::normalize(glm::vec3(farPlane - nearPlane));

	Ray ray(origin, direction);

	return ray;
}
