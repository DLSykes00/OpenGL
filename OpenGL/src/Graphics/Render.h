#pragma once

#include "Shader.h"
#include "Texture.h"
#include "Camera.h"
#include "GridMesh.h"
#include "CubeMesh.h"

class Render
{
public:
    Render();

    void draw(float dt);
    
    const Camera& getCamera() const { return m_camera; }
    
    float getGpuTimeMs();

private:
    Shader   m_shader;
    Camera   m_camera;
    Texture  m_texture;
    CubeMesh m_cubeMesh;
    GridMesh m_gridMesh;

    float m_cubeAngle = 0.0f;

    GLuint m_gpuTimeQueryID;

    void drawGrid();
    void drawCube(float angle);
};
