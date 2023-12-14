#pragma once

#include "Shader.h"
#include "Texture.h"
#include "Camera.h"

class Render
{
public:
    Render();
    void draw();
    void drawCube();

    uint32_t drawTriangle();
    uint32_t drawSquare3D();
    uint32_t drawCircle(float s);

private:
    uint32_t vertexBufferID;
    uint32_t indexBufferID;
    uint32_t textureBufferID;
    uint32_t instanceOffsetBufferID;

    uint32_t vertCount = 0;
    uint32_t instanceCount = 0;

    float cubeAngle = 0.0f;

    Shader shader;
    Texture texture;
    Camera camera;
};
