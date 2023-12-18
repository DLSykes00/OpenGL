#pragma once

#include <GL/glew.h>
#include "Window.h"
#include "Render.h"

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
	float currentTime;
	float deltaTime = 0.0;
	float elapsedTime = 0.0;
	float previousTime = 0.0;
};
