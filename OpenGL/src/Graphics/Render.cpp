#include <GL/glew.h>
#include "Render.h"
#include "World/Chunk.h"
#include <iostream>
#include <chrono>

Render::Render()
    : m_texture("Assets/Textures/test.png")
{
    m_texture.bindTexture(0);

    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    glEnable(GL_CULL_FACE);

    float r = 150.0f, g = 180.0f, b = 205.0f, a = 1.0f;
    glClearColor(r / 255.0f, g / 255.0f, b / 255.0f, a);

    glGenQueries(1, &m_gpuTimeQueryID);
}

void Render::draw(float dt)
{
    m_camera.update(dt);

    glBeginQuery(GL_TIME_ELAPSED, m_gpuTimeQueryID);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    drawGrid();
    drawWorld();
    drawCube(lightPos);

    glEndQuery(GL_TIME_ELAPSED);
}

void Render::drawWorld()
{
    m_terrainShader.use();
    m_terrainShader.setLightPosition(lightPos);

    for (const auto& chunkRow : m_world.getChunks())
    for (const auto& chunk : chunkRow)
    {
        glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), chunk->getPosition());
        m_terrainShader.setMvp(modelMatrix, m_camera.getProjectionViewMatrix());
        m_terrainShader.setChunkPosition(chunk->getPosition());

        if (chunk->getVao() == NULL)
            chunk->generateVao();

        glBindVertexArray(chunk->getVao());
        glDrawElements(GL_TRIANGLES, chunk->getIndicesCount(), GL_UNSIGNED_INT, nullptr);
    }
}

void Render::drawCube(const glm::vec3& position)
{
    m_basicShader.use();
    m_basicShader.useColor();
    m_basicShader.setColor(glm::vec4(0.97f, 0.85f, 0.1f, 1.0f));
    glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), position);
    modelMatrix = glm::scale(modelMatrix, glm::vec3(16.0f));
    m_basicShader.setMvp(modelMatrix, m_camera.getProjectionViewMatrix());

    glBindVertexArray(m_cubeMesh.getVao());
    glDrawElements(GL_TRIANGLES, m_cubeMesh.getIndicesCount(), GL_UNSIGNED_INT, nullptr);
}

void Render::drawGrid()
{
    m_basicShader.use();
    m_basicShader.useColor();
    m_basicShader.setColor(glm::vec4(0.9f, 0.9f, 0.9f, 1.0f));
    m_basicShader.setMvp(glm::mat4(1.0f), m_camera.getProjectionViewMatrix());

    glBindVertexArray(m_gridMesh.getVao());
    glDrawElements(GL_LINES, m_gridMesh.getIndicesCount(), GL_UNSIGNED_INT, nullptr);
}

float Render::getGpuTimeMs()
{
    GLuint64 gpuTimeQueryResultNs = 0;
    glGetQueryObjectui64v(m_gpuTimeQueryID, GL_QUERY_RESULT, &gpuTimeQueryResultNs);

    return gpuTimeQueryResultNs / 1e6f;
}
