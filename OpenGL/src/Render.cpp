#include <GL/glew.h>
#include "Render.h"

Render::Render()
    : m_texture("Resources/Textures/test.png")
{
    m_shader.useCubeShader();
    m_texture.bindTexture(0);

    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    glEnable(GL_CULL_FACE);

    float r = 10.0f, g = 10.0f, b = 20.0f, a = 1.0f;
    glClearColor(r / 255.0f, g / 255.0f, b / 255.0f, a);
}

void Render::draw(float dt)
{
    m_camera.update(dt);
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);   
    drawGrid();
    drawCube(m_cubeAngle);

    m_cubeAngle += 0.0f * dt;
    if (m_cubeAngle >= 360.0f)
        m_cubeAngle -= 360.0f;
}

 void Render::drawCube(float angle)
{
    m_shader.useCubeShader();
    glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.5f, -1.5f));
    m_shader.setMvpMatrix(modelMatrix, m_camera.getViewMatrix(), m_camera.getProjectionMatrix());
    glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
    m_shader.setUniform4fv("u_rotationMatrix", rotationMatrix);

    glBindVertexArray(m_cubeMesh.getVao());
    glDrawElementsInstanced(GL_TRIANGLES, m_cubeMesh.getIndiciesCount(), GL_UNSIGNED_INT, nullptr, m_cubeMesh.getInstanceCount());
}

void Render::drawGrid()
{
    m_shader.useBasicShader();
    m_shader.setMvpMatrix(glm::mat4(1.0f), m_camera.getViewMatrix(), m_camera.getProjectionMatrix());

    glBindVertexArray(m_gridMesh.getVao());
    glDrawElements(GL_LINES, m_gridMesh.getIndicesCount(), GL_UNSIGNED_INT, nullptr);
}
