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
    
    void setAspectRatio(float ar) { aspectRatio = ar; };
    const glm::mat4& getViewMatrix() const { return viewMatrix; };
    const glm::mat4& getProjectionMatrix() const { return projectionMatrix; };

private: 
    void updatePosition();
    void setViewMatrix();
    void setProjectionMatrix(float fov, float aspectRatio, float zNear, float zFar);

    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;

    float fov = 70.0f;
    float aspectRatio = 1.0f;
    float zNear = 0.1f;
    float zFar = 300.0f;

    float x = 0.0f, xi = 0.0f;
    float y = 0.0f, yi = 0.0f;
    float z = 0.0f, zi = 0.0f;
    float xRot = 0.0f, xRoti = 0.0f;
    float yRot = 0.0f, yRoti = 0.0f;

    float translateSpeed = 0.02f;
    float rotateSpeed = 0.2f;
};
