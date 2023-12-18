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

    // Vertices + Indices
    glBindBuffer(GL_ARRAY_BUFFER, cubeMesh.getVertexBuffer());
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeMesh.getIndexBuffer());

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);

    // Texture
    glBindBuffer(GL_ARRAY_BUFFER, cubeMesh.getTextureBuffer());

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);

    // Instance
    glBindBuffer(GL_ARRAY_BUFFER, cubeMesh.getInstanceBuffer());

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    glVertexAttribDivisor(2, 1);

    int tris = static_cast<GLsizei>(cubeMesh.getIndices().size());
    int instances = static_cast<GLsizei>(cubeMesh.getInstances().size());
    glDrawElementsInstanced(GL_TRIANGLES, tris * 3, GL_UNSIGNED_INT, nullptr, instances);
}

void Render::drawGrid()
{
    shader.useBasicShader();
    shader.setMvpMatrix(glm::mat4(1.0f), camera.getViewMatrix(), camera.getProjectionMatrix(), 0.0f);

    glBindBuffer(GL_ARRAY_BUFFER, gridMesh.getVertexBuffer());
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gridMesh.getIndexBuffer());

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);

    int lines = static_cast<GLsizei>(gridMesh.getIndices().size());
    glDrawElements(GL_LINES, lines * 2, GL_UNSIGNED_INT, nullptr);
}
