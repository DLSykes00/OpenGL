#pragma once

#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

class Camera 
{
public:
    Camera();
    void updateCamera(float dt);
    
    void setAspectRatio(float ar) { aspectRatio = ar; };
    const glm::mat4& getViewMatrix() const { return viewMatrix; };
    const glm::mat4& getProjectionMatrix() const { return projectionMatrix; };

private: 
    void handleInput(float dt);
    void updatePosition();
    void setViewMatrix();
    void setProjectionMatrix(float fov, float aspectRatio, float zNear, float zFar);

    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;

    float fov = 70.0f;
    float aspectRatio = 1.0f;
    float zNear = 0.1f;
    float zFar = 300.0f;

    // Change to vector format
    float x = 0.0f, y = 1.0f, z = 0.0f;
    float xi = 0.0f, yi = 0.0f, zi = 0.0f;

    float xRot = 0.0f, yRot = 0.0f;
    float xRoti = 0.0f, yRoti = 0.0f;

    float translateSpeed = 2.0f;
    float rotateSpeed = 45.0f;
};
