#pragma once

#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>

class Camera
{
public:
    Camera();

    void update(float dt);

    const glm::vec3& getPosition()             const { return m_position; }
    const glm::mat4& getProjectionViewMatrix() const { return m_projectionViewMatrix; }

private:
    float m_fov         = 80.0f;
    float m_aspectRatio = 1.0f;
    float m_zNear       = 0.1f;
    float m_zFar        = 1000.0f;

    
    float m_baseSpeed       = 5.0f;
    float m_translateSpeed  = m_baseSpeed;
    float m_speedMultiplier = 10.0f;
    float m_rotateSpeed     = 90.0f;

    float m_mouseSens      = 0.6f;
    float m_mouseYawSens   = 0.022f;
    float m_mousePitchSens = 0.022f;

    float m_prevMouseX = 0.0f;
    float m_prevMouseY = 0.0f;

    float m_yaw   = 0.0f;
    float m_pitch = 0.0f;
    glm::vec3 m_position = { 0.0f, 16.0f, 0.0f };

    glm::mat4 m_viewMatrix;
    glm::mat4 m_projectionMatrix;
    glm::mat4 m_projectionViewMatrix;

    void handleInput(float dt);

    void setViewMatrix();
    void setProjectionMatrix(float fov, float aspectRatio, float zNear, float zFar);
    void updateProjectionViewMatrix();
};
