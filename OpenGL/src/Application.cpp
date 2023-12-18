#include "Application.h"
#include "Window.h"
#include "Input.h"
#include <iostream>
#include <string>

void Application::run() 
{
    while (!window.shouldClose())
    {
        currentTime = static_cast<float>(glfwGetTime());
        deltaTime = currentTime - previousTime;
        previousTime = currentTime;

        elapsedTime += deltaTime;
        if (elapsedTime >= 1.0f)
            showFPS();

        render.draw(deltaTime);

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
