#include "Camera.h"
#include "Input.h"
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

Camera::Camera()
{ 
    setProjectionMatrix(fov, aspectRatio, zNear, zFar);
    setViewMatrix();
}

void Camera::handleInput(float dt)
{
    // Translate
    if (Input::getKey(GLFW_KEY_W) == Input::getKey(GLFW_KEY_S))
        zi = 0.0f;
    else if (Input::getKey(GLFW_KEY_W))
        zi = translateSpeed * dt;    
    else if (Input::getKey(GLFW_KEY_S))
        zi = -translateSpeed * dt;
    
    if (Input::getKey(GLFW_KEY_A) == Input::getKey(GLFW_KEY_D))
        xi = 0.0f;
    else if (Input::getKey(GLFW_KEY_A))
        xi = translateSpeed * dt;
    else if (Input::getKey(GLFW_KEY_D))
        xi = -translateSpeed * dt;
    
    if (Input::getKey(GLFW_KEY_SPACE) == Input::getKey(GLFW_KEY_LEFT_CONTROL))
        yi = 0.0f;
    else if (Input::getKey(GLFW_KEY_SPACE))
        yi = translateSpeed * dt;
    else if (Input::getKey(GLFW_KEY_LEFT_CONTROL))
        yi = -translateSpeed * dt;
    
    // Rotate
    if (Input::getKey(GLFW_KEY_F) == Input::getKey(GLFW_KEY_V))
        xRoti = 0.0f;
    else if (Input::getKey(GLFW_KEY_F))
        xRoti = -rotateSpeed * dt;
    else if (Input::getKey(GLFW_KEY_V))
        xRoti = rotateSpeed * dt;
    
    if (Input::getKey(GLFW_KEY_Q) == Input::getKey(GLFW_KEY_E))
        yRoti = 0.0f;
    else if (Input::getKey(GLFW_KEY_Q))
        yRoti = -rotateSpeed * dt;
    else if (Input::getKey(GLFW_KEY_E))
        yRoti = rotateSpeed * dt;
}

void Camera::updateCamera(float dt)
{
    if (Input::getWindowResized())
    {
        aspectRatio = static_cast<float>(Input::getWx()) / static_cast<float>(Input::getWy());
        setProjectionMatrix(fov, aspectRatio, zNear, zFar);
        Input::setWindowResized(false);
    }

    handleInput(dt);
    updatePosition();
    setViewMatrix();
}

void Camera::updatePosition()
{
    const float _PI = 3.1415926536f;

    xRot += xRoti;
    yRot += yRoti;

    if (xRot >= 360.0f)
        xRot -= 360.0f;
    else if (xRot < 0.0f)
        xRot += 360.0f;

    if (yRot >= 360.0f)
        yRot -= 360.0f;
    else if (yRot < 0.0f)
        yRot += 360.0f;

    x += (xi * -std::cosf((yRot * _PI) / 180.0f)) + (zi * std::sinf((yRot * _PI) / 180.0f));
    y += yi;
    z += (xi * std::sinf((yRot * _PI) / 180.0f)) + (zi * std::cosf((yRot * _PI) / 180.0f));

    std::cout << "angle|x|y|z: " << yRot << " | " << x << " | " << y << " | " << z << std::endl;
}

void Camera::setViewMatrix()
{
    viewMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(xRot), glm::vec3(1.0f, 0.0f, 0.0f)); // apply xRot
    viewMatrix = glm::rotate(viewMatrix, glm::radians(yRot), glm::vec3(0.0f, 1.0f, 0.0f)); // apply yRot
    viewMatrix = glm::translate(viewMatrix, glm::vec3(-x, -y, z)); // apply translation    
}

void Camera::setProjectionMatrix(float fov, float aspectRatio, float zNear, float zFar)
{
    projectionMatrix = glm::perspective(glm::radians(fov), aspectRatio, zNear, zFar);
}
