#pragma once

class Render
{
private:
    unsigned int vertexBufferID;
    unsigned int indexBufferID;
    unsigned int textureBufferID;
    unsigned int instanceOffsetBufferID;

    unsigned int vertCount;
    unsigned int instanceCount;

public:
    Render();
    unsigned int drawTriangle();
    unsigned int drawSquare3D();
    unsigned int drawCircle(float s);
    void drawCube();

    unsigned int getVertCount();
    unsigned int getInstanceCount();
};
