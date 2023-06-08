#pragma once
#include <GLFW/glfw3.h>
#include <vector>

class Camera 
{
public:
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
    float xRot = 0.0f;
    float yRot = 0.0f;

    float xi = 0.0f;
    float yi = 0.0f;
    float zi = 0.0f;
    float xRoti = 0.0f;
    float yRoti = 0.0f;

    void handleInput();
    void updateCamera();
};

