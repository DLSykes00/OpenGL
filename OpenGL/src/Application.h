#pragma once

#include <GL/glew.h>
#include "Window.h"
#include "Render.h"
#include <string>

class Application
{
public:
	void run();

private:
	Window window;
	Render render;

	void showFPS();

	float cubeAngle = 0.0f;

	int frames = 0;
	double currentTime;
	double deltaTime = 0.0;
	double elapsedTime = 0.0;
	double previousTime = 0.0;
};
