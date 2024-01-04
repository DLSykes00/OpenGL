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

private:
    Shader m_shader;
    Texture m_texture;
    Camera m_camera;

    CubeMesh m_cubeMesh;
    GridMesh m_gridMesh;

    float m_cubeAngle = 0.0f;

    void drawCube(float angle);
    void drawGrid();
};
