#pragma once

#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>

class Camera 
{
public:
    Camera();

    void update(float dt);
    
    const glm::mat4& getViewMatrix() const { return m_viewMatrix; };
    const glm::mat4& getProjectionMatrix() const { return m_projectionMatrix; };

private: 
    float m_fov = 80.0f;
    float m_aspectRatio = 1.0f;
    float m_zNear = 0.1f;
    float m_zFar = 300.0f;

    float m_translateSpeed = 2.0f;
    float m_rotateSpeed = 90.0f;
    float m_mouseSens = 0.6f;
    float m_mouseYawSens = 0.022f;
    float m_mousePitchSens = 0.022f;

    float m_prevMouseX = 0.0f;
    float m_prevMouseY = 0.0f;

    glm::vec3 m_position = { 0.0f, 2.0f, 0.0f };
    float m_pitch = 0.0f, m_yaw = 0.0f;

    glm::mat4 m_viewMatrix;
    glm::mat4 m_projectionMatrix;

    void handleInput(float dt);

    void setViewMatrix();
    void setProjectionMatrix(float fov, float aspectRatio, float zNear, float zFar);
};
