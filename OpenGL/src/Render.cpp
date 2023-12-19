#include <GL/glew.h>
#include "Render.h"

Render::Render()
    : texture("Resources/Textures/test.png")
{
    shader.useCubeShader();
    shader.setUniform1i("u_Texture", 0);
    texture.bindTexture(0);
}

void Render::draw(float dt)
{
    camera.updateCamera(dt);
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);   
    drawGrid();
    drawCube(cubeAngle);

    cubeAngle += 90.0f * dt;
    if (cubeAngle >= 360.0f)
        cubeAngle -= 360.0f;
}

 void Render::drawCube(float angle)
{
    shader.useCubeShader();
    glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.5f, -5.5f));
    shader.setMvpMatrix(modelMatrix, camera.getViewMatrix(), camera.getProjectionMatrix(), angle);

    glBindVertexArray(cubeMesh.getVao());
    glDrawElementsInstanced(GL_TRIANGLES, cubeMesh.getIndiciesCount(), GL_UNSIGNED_INT, nullptr, cubeMesh.getInstanceCount());
}

void Render::drawGrid()
{
    shader.useBasicShader();
    shader.setMvpMatrix(glm::mat4(1.0f), camera.getViewMatrix(), camera.getProjectionMatrix(), 0.0f);

    glBindVertexArray(gridMesh.getVao());
    glDrawElements(GL_LINES, gridMesh.getIndicesCount(), GL_UNSIGNED_INT, nullptr);
}
