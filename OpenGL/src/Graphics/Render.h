#pragma once

#include "Texture.h"
#include "Camera.h"
#include "CubeMesh.h"
#include "GridMesh.h"
#include "World/World.h"
#include "World/Chunk.h"
#include "Shaders/BasicShader.h"
#include "Shaders/TerrainShader.h"

class Chunk;

class Render
{
public:
    Render();

    void draw(float dt);
    
    const Camera& getCamera() const { return m_camera; }
    
    float getGpuTimeMs();

private:
    Camera        m_camera;
    Texture       m_texture;
    World         m_world;
    CubeMesh      m_cubeMesh;
    GridMesh      m_gridMesh;
    BasicShader   m_basicShader;
    TerrainShader m_terrainShader;

    GLuint m_gpuTimeQueryID;
    float  m_timer = 0.0f;

    void drawWorld();
    void drawCube(const glm::vec3& position);
    void drawGrid();

    glm::vec3 lightPos = glm::vec3(0, 256.0f, -256.0f);
};
