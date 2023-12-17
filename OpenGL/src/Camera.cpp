#include "Camera.h"
#include "Input.h"
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

const double _PI = 3.14159265358979323846;

Camera::Camera() { 
    projectionMatrix = glm::perspective(glm::radians(fov), aspectRatio, zNear, zFar);
    viewMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(xRot), glm::vec3(1.0f, 0.0f, 0.0f)); // apply xRot
    viewMatrix = glm::rotate(viewMatrix, glm::radians(yRot), glm::vec3(0.0f, 1.0f, 0.0f)); // apply yRot
    viewMatrix = glm::translate(viewMatrix, glm::vec3(x, y, z)); // apply translation  
}

void Camera::handleInput()
{
    // Translate Forward
    if (Input::key == GLFW_KEY_W && Input::action)
        zi = 0.01f;
    else if (Input::key == GLFW_KEY_W && Input::action == GLFW_RELEASE)
        zi = 0.00f;

    // Translate Backward
    if (Input::key == GLFW_KEY_S && Input::action)
        zi = -0.01f;
    else if (Input::key == GLFW_KEY_S && Input::action == GLFW_RELEASE)
        zi = 0.00f;

    // Translate Left
    if (Input::key == GLFW_KEY_A && Input::action)
        xi = 0.01f;
    else if (Input::key == GLFW_KEY_A && Input::action == GLFW_RELEASE)
        xi = 0.00f;

    // Translate Right
    if (Input::key == GLFW_KEY_D && Input::action)
        xi = -0.01f;
    else if (Input::key == GLFW_KEY_D && Input::action == GLFW_RELEASE)
        xi = 0.00f;

    // Translate Up
    if (Input::key == GLFW_KEY_SPACE && Input::action)
        yi = -0.01f;
    else if (Input::key == GLFW_KEY_SPACE && Input::action == GLFW_RELEASE)
        yi = 0.00f;

    // Translate Down
    if (Input::key == GLFW_KEY_LEFT_CONTROL && Input::action)
        yi = 0.01f;
    else if (Input::key == GLFW_KEY_LEFT_CONTROL && Input::action == GLFW_RELEASE)
        yi = 0.00f;

    // Rotate Left
    if (Input::key == GLFW_KEY_V && Input::action)
        xRoti = 0.2f;
    else if (Input::key == GLFW_KEY_V && Input::action == GLFW_RELEASE)
        xRoti = 0.00f;

    // Rotate Right
    if (Input::key == GLFW_KEY_F && Input::action)
        xRoti = -0.2f;
    else if (Input::key == GLFW_KEY_F && Input::action == GLFW_RELEASE)
        xRoti = 0.00f;

    // Yaw Left
    if (Input::key == GLFW_KEY_Q && Input::action)
        yRoti = -0.2f;
    else if (Input::key == GLFW_KEY_Q && Input::action == GLFW_RELEASE)
        yRoti = 0.00f;

    // Yaw Right
    if (Input::key == GLFW_KEY_E && Input::action)
        yRoti = 0.2f;
    else if (Input::key == GLFW_KEY_E && Input::action == GLFW_RELEASE)
        yRoti = 0.00f;
}

void Camera::updateCamera()
{
    handleInput();

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

    setMatrices();
}

void Camera::setMatrices() {
    viewMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(xRot), glm::vec3(1.0f, 0.0f, 0.0f)); // apply xRot
    viewMatrix = glm::rotate(viewMatrix, glm::radians(yRot), glm::vec3(0.0f, 1.0f, 0.0f)); // apply yRot
    viewMatrix = glm::translate(viewMatrix, glm::vec3(x, y, z)); // apply translation    
}

void Camera::setProjectionMatrix(float aspectRatio) {
    projectionMatrix = glm::perspective(glm::radians(fov), aspectRatio, zNear, zFar);
}
