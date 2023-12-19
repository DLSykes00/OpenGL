#include <GL/glew.h>
#include "GridMesh.h"
#include <vector>

GridMesh::GridMesh()
{
    std::vector<glm::vec3> vertices;
    for (int i = 0; i <= gridSlices; i++)
    {
        for (int j = 0; j <= gridSlices; j++)
        {
            float x = static_cast<float>(i - (gridSlices / 2.0f));
            float y = 0.0f;
            float z = static_cast<float>(-j);
            vertices.push_back(glm::vec3(x, y, z));
        }
    }

    std::vector<glm::uvec2> indices;
    int rowLen = gridSlices + 1;
    int noVert = static_cast<int>(vertices.size());
    for (int i = 0; i < rowLen; i++)
    {
        indices.push_back(glm::uvec2(i * rowLen, (i + 1) * rowLen - 1));
        indices.push_back(glm::uvec2(i, vertices.size() - rowLen + i));
    }
    indicesCount = static_cast<GLsizei>(indices.size() * sizeof(glm::uvec2));


    GLuint vertexBuffer, indexBuffer;
  
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(glm::uvec2), indices.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
}
