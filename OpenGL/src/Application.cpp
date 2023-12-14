#include "Application.h"
#include "Window.h"
#include "Input.h"
#include <iostream>

void Application::run() 
{
    while (!window.shouldClose())
    {
        currentTime = glfwGetTime();
        deltaTime = currentTime - previousTime;
        previousTime = currentTime;

        elapsedTime += deltaTime;
        if (elapsedTime >= 1.0)
            showFPS();

        render.draw();

        window.swapBuffers();

        window.pollEvents();

        frames++;
    }
}

void Application::showFPS()
{
    std::string windowTitle = "FPS: " + std::to_string(static_cast<int>(frames / elapsedTime)) + " (VSync: On)";
    window.setTitle(windowTitle);
    elapsedTime = 0.0;
    frames = 0;
}
