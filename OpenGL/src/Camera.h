#pragma once

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vector>

class Camera 
{
public:
    Camera();
    void handleInput();
    void updateCamera();
    void setProjectionMatrix(float aspectRatio);
    
    void setAspectRatio(float ar) { aspectRatio = ar; };
    glm::mat4 getViewMatrix() { return viewMatrix; };
    glm::mat4 getProjectionMatrix() { return projectionMatrix; };

private: 
    void setMatrices();

    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;

    glm::vec3 pos;
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
    float xRot = 0.0f;
    float yRot = 0.0f;

    float fov = 70.0f;
    float aspectRatio = 1.0f;
    float zNear = 0.1f;
    float zFar = 300.0f;

    float xi = 0.0f;
    float yi = 0.0f;
    float zi = 0.0f;
    float xRoti = 0.0f;
    float yRoti = 0.0f;
};
