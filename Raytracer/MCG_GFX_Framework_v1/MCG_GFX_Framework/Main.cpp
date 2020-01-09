#include <GLM/glm.hpp>
#include <iostream>
#include <cmath>
#include <thread>
#include <chrono>
#include <ctime>
#include "MCG_GFX_Lib.h"

#include "Ray.h"
#include "Geometry.h"
#include "Camera.h"
#include "Tracer.h"
#include "Light.h"
#include "Sphere.h"

#include <mutex>

std::mutex _mutex;

void Draw(int startPos, int endPos, Geometry _intersect, Sphere _centre[], Tracer _tracer, Light _light, Camera _mCamera)
{
	glm::vec3 pixelColour(1, 0, 0);
	glm::vec2 pixelPosition;
	PointDistance pDistance;
	float radius = 50.0f;// radius of the sphere

	for (int y = startPos; y < endPos; y++)// goes through the y coordinates of the window until it reaches the end
	{
		for (int x = 0; x < 640; x++)// goes through the x coordinates of the window until it reaches the end
		{
			for (int i = 0; i < 2; i++)// value at which i stops is the number of spheres being created
			{
				pixelPosition = glm::ivec2(x, y);// the pixels position on the screen is the at values of x and y

				//	Ray ray(pixelPosition, glm::vec3(0, 0, -1));
				Ray ray = _mCamera.createRay(pixelPosition, glm::ivec2(640, 480));// creates a ray using the create ray function in the camera class

				pDistance = _intersect.Intersection(ray, _centre[i].sphereCentrepoint, radius);//calculates whether the ray has intersected with a sphere

				if (pDistance.hit == true)// the ray does intersect the sphere
				{
					pixelColour = _tracer.Colour(ray, pDistance, _light, _centre[i].sphereCentrepoint, _centre[i]);// pixel colour value is changed to the value set in the tracer.colour function
					pixelColour = pixelColour * 255.0f;//multiply the pixel colour value by 255 so that the colour is clearly visible to the user and more vibrant that if it were left at the value of 1
					_mutex.lock();// mutex lock the draw function so that multiple threads don't access it at the same time and throw an exception
					MCG::DrawPixel(pixelPosition, pixelColour);//draws pixel to the screen
					_mutex.unlock();//unlocks the function so that other threads can access it
				}
				else
				{
					//pixelColour = glm::vec3(1, 1, 1);
				}
				
			}
			
		}
		_mutex.lock();
		MCG::ProcessFrame();
		_mutex.unlock();
	}
}


int main(int argc, char *argv[])
{
	int Size;
	// Variable for storing window dimensions
	glm::ivec2 windowSize(640, 480);

	// Call MCG::Init to initialise and create your window
	// Tell it what size you want the window to be
	if (!MCG::Init(windowSize))
	{
		// We must check if something went wrong
		// (this is very unlikely)
		return -1;
	}

	// Sets every pixel to the same colour
	// parameters are RGBA, numbers are from 0 to 255
	MCG::SetBackground(glm::ivec3(0, 0, 0));

	// Preparing a position to draw a pixel
	glm::ivec2 pixelPosition;

	// Preparing a colour to draw
	// Colours are RGB, each value ranges between 0 and 255
	glm::vec3 pixelColour(1.0f, 0.0f, 0.0f);

	//std::cout << "what size would you like the circle? \n";
	//std::cin >> Size;
	//for (int i = 0; i < 1000; i++)
	//{
	//	glm::ivec2 Circle(pixelPosition.x + Size * sin(i), pixelPosition.y + Size * cos(i));
	//	MCG::DrawPixel(Circle, pixelColour);
	//}
	// Draws a single pixel at the specified coordinates in the specified colour!

	// Do any other DrawPixel calls here
	// ...

	// Displays drawing to screen and holds until user closes window
	// You must call this after all your drawing calls
	// Program will exit after this line
	//return MCG::ShowAndHold();
	
	// This is our game loop
	// It will run until the user presses 'escape' or closes the window

	int nThreads = 50; // number of threads, change value to use a different amount

	Camera main_Camera;
	main_Camera.setPosition(glm::vec3(0, 0, 0));//set the position of the camera
	Geometry Intersect;
	Light light;
	light.lightPosition = glm::vec3(0, -10, 5);// Position of the light in the scene
	Sphere Centre[2];
	
	Centre[0].sphereCentrepoint = glm::vec3(-50, 0, -100);// states where the centre of the sphere is 
	Centre[1].sphereCentrepoint = glm::vec3(50, 0, -100);
	Centre[0].Colour = glm::vec3(1.0f, 0.0f, 0.0f);//colour for first sphere
	Centre[1].Colour = glm::vec3(0.0f, 0.0f, 1.0f);//colour for second sphere
	Tracer tracer;
	light.lightColour = glm::vec3(1.0f, 1.0f, 1.0f); // white light
	std::thread drawThread[50];// size of the array needs to be the same as the number of threads
	
	std::chrono::time_point<std::chrono::system_clock> start, end, drawStart, drawEnd;//create the variable required to time the process

	while( MCG::ProcessFrame() )
	{
		drawStart = std::chrono::system_clock::now();//gets the time when the process starts

		for (int x = 0; x < nThreads; x++)
		{
			start = std::chrono::system_clock::now();
			drawThread[x] = std::thread(Draw, windowSize.y/ nThreads * x, windowSize.y / nThreads * (x+1), Intersect, Centre, tracer, light, main_Camera);// start point is the y coordinate of the window size divided by the number of threads multiplied by x, end point is the same except x is increased by 1
			end = std::chrono::system_clock::now();
			std::chrono::duration<double> elapsed_seconds = end - start;// calculates the time taken for threads tofinish processing their part
			//std::cout << elapsed_seconds.count() << "\n";
		}

		for (int i = 0; i < nThreads; i++)
		{
			drawThread[i].join();//joins the threads
		}

		drawEnd = std::chrono::system_clock::now();// gets the time when the process is complete
		std::chrono::duration<double> timeTaken = drawEnd - drawStart;// subtract the time the process started from the time the process finished to get the amount of time that passed
		std::cout << "The process took "<<timeTaken.count() << " Seconds to finish" <<"\n";// outputs time passed to the user
	}

	return 0;

}
