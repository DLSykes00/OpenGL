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

void Camera::handleInput()
{
    // Translate
    if (Input::getKey(GLFW_KEY_W) == Input::getKey(GLFW_KEY_S))
        zi = 0.0f;
    else if (Input::getKey(GLFW_KEY_W))
        zi = translateSpeed;    
    else if (Input::getKey(GLFW_KEY_S))
        zi = -translateSpeed;
    
    if (Input::getKey(GLFW_KEY_A) == Input::getKey(GLFW_KEY_D))
        xi = 0.0f;
    else if (Input::getKey(GLFW_KEY_A))
        xi = translateSpeed;
    else if (Input::getKey(GLFW_KEY_D))
        xi = -translateSpeed;
    
    if (Input::getKey(GLFW_KEY_SPACE) == Input::getKey(GLFW_KEY_LEFT_CONTROL))
        yi = 0.0f;
    else if (Input::getKey(GLFW_KEY_SPACE))
        yi = -translateSpeed;
    else if (Input::getKey(GLFW_KEY_LEFT_CONTROL))
        yi = translateSpeed;
    
    // Rotate
    if (Input::getKey(GLFW_KEY_F) == Input::getKey(GLFW_KEY_V))
        xRoti = 0.0f;
    else if (Input::getKey(GLFW_KEY_F))
        xRoti = -rotateSpeed;
    else if (Input::getKey(GLFW_KEY_V))
        xRoti = rotateSpeed;
    
    if (Input::getKey(GLFW_KEY_Q) == Input::getKey(GLFW_KEY_E))
        yRoti = 0.0f;
    else if (Input::getKey(GLFW_KEY_Q))
        yRoti = -rotateSpeed;
    else if (Input::getKey(GLFW_KEY_E))
        yRoti = rotateSpeed;
}

void Camera::updateCamera()
{
    if (Input::getWindowResized()) {
        aspectRatio = static_cast<float>(Input::getWx()) / static_cast<float>(Input::getWy());
        setProjectionMatrix(fov, aspectRatio, zNear, zFar);
        Input::setWindowResized(false);
    }

    handleInput();
    updatePosition();
    setViewMatrix();
}

void Camera::updatePosition()
{
    const double _PI = 3.14159265358979323846;

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

    x += (xi * std::cos((yRot * _PI) / 180)) + (zi * -std::sin((yRot * _PI) / 180));
    y += yi;
    z += (xi * std::sin((yRot * _PI) / 180)) + (zi * std::cos((yRot * _PI) / 180));

    std::cout << "angle|x|y|z: " << yRot << " | " << x << " | " << y << " | " << z << std::endl;
}

void Camera::setViewMatrix()
{
    viewMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(xRot), glm::vec3(1.0f, 0.0f, 0.0f)); // apply xRot
    viewMatrix = glm::rotate(viewMatrix, glm::radians(yRot), glm::vec3(0.0f, 1.0f, 0.0f)); // apply yRot
    viewMatrix = glm::translate(viewMatrix, glm::vec3(x, y, z)); // apply translation    
}

void Camera::setProjectionMatrix(float fov, float aspectRatio, float zNear, float zFar)
{
    projectionMatrix = glm::perspective(glm::radians(fov), aspectRatio, zNear, zFar);
}
