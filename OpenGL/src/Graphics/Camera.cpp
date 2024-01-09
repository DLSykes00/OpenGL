#include "Camera.h"
#include "Input.h"
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

Camera::Camera()
{
    setViewMatrix();
    setProjectionMatrix(m_fov, m_aspectRatio, m_zNear, m_zFar);
}

void Camera::update(float dt)
{
    if (Input::getWindowResized())
    {
        if (Input::getWindowHeight() > 0)
        {
            m_aspectRatio = static_cast<float>(Input::getWindowWidth()) / static_cast<float>(Input::getWindowHeight());
            setProjectionMatrix(m_fov, m_aspectRatio, m_zNear, m_zFar);
        }
        Input::setWindowResized(false);
    }

    handleInput(dt);
    setViewMatrix();
}

void Camera::handleInput(float dt)
{
    float dx = 0.0f, dy = 0.0f, dz = 0.0f, dpitch = 0.0f, dyaw = 0.0f;

    // Translate
    if (Input::getKey(GLFW_KEY_W))
        dz -= m_translateSpeed * dt;
    if (Input::getKey(GLFW_KEY_S))
        dz += m_translateSpeed * dt;

    if (Input::getKey(GLFW_KEY_A))
        dx -= m_translateSpeed * dt;
    if (Input::getKey(GLFW_KEY_D))
        dx += m_translateSpeed * dt;

    if (Input::getKey(GLFW_KEY_SPACE))
        dy += m_translateSpeed * dt;
    if (Input::getKey(GLFW_KEY_LEFT_CONTROL))
        dy -= m_translateSpeed * dt;

    const float PI = 3.1415926536f;
    m_position.x += dx *  std::cosf(m_yaw * PI / 180.0f) + dz * std::sinf(m_yaw * PI / 180.0f);
    m_position.y += dy;
    m_position.z += dx * -std::sinf(m_yaw * PI / 180.0f) + dz * std::cosf(m_yaw * PI / 180.0f);

    // Rotate
    if (Input::getKey(GLFW_KEY_F))
        dpitch += m_rotateSpeed * dt;
    if (Input::getKey(GLFW_KEY_V))
        dpitch -= m_rotateSpeed * dt;

    if (Input::getKey(GLFW_KEY_Q))
        dyaw += m_rotateSpeed * dt;
    if (Input::getKey(GLFW_KEY_E))
        dyaw -= m_rotateSpeed * dt;

    dyaw   += (m_prevMouseX - Input::getMouseX()) * m_mouseYawSens   * m_mouseSens;
    dpitch += (m_prevMouseY - Input::getMouseY()) * m_mousePitchSens * m_mouseSens;
    m_prevMouseY = Input::getMouseY();
    m_prevMouseX = Input::getMouseX();
    
    m_yaw   += dyaw;
    m_pitch += dpitch;

    if (m_yaw >= 180.0f)
        m_yaw -= 360.0f;
    else if (m_yaw < -180.0f)
        m_yaw += 360.0f;

    if (m_pitch >= 180.0f)
        m_pitch -= 360.0f;
    else if (m_pitch < -180.0f)
        m_pitch += 360.0f;
}

void Camera::setViewMatrix()
{
    glm::mat4 viewMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(-m_pitch), glm::vec3(1.0f, 0.0f, 0.0f));
    viewMatrix = glm::rotate(viewMatrix, glm::radians(-m_yaw), glm::vec3(0.0f, 1.0f, 0.0f));
    viewMatrix = glm::translate(viewMatrix, glm::vec3(-m_position.x, -m_position.y, -m_position.z));

    m_viewMatrix = viewMatrix;
}

void Camera::setProjectionMatrix(float fov, float aspectRatio, float zNear, float zFar)
{
    m_projectionMatrix = glm::perspective(glm::radians(fov), aspectRatio, zNear, zFar);
}
