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
    void drawCube(float angle);
    void drawGrid();

    CubeMesh cubeMesh;
    GridMesh gridMesh;

    Shader shader;
    Texture texture;
    Camera camera;

    float cubeAngle = 0.0f;
};
