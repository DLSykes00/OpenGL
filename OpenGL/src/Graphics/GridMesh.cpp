#include "GridMesh.h"
#include <vector>

GridMesh::GridMesh()
{
    std::vector<glm::vec3> vertices;
    for (int i = 0; i <= m_gridSlices; i++)
    {
        for (int j = 0; j <= m_gridSlices; j++)
        {
            float x = static_cast<float>(i - (m_gridSlices / 2) - 0.5f);
            float y = 0.0f;
            float z = static_cast<float>(-j);
            vertices.push_back(glm::vec3(x, y, z));
        }
    }

    std::vector<glm::uvec2> indices;
    int rowLen = m_gridSlices + 1;
    int noVert = static_cast<int>(vertices.size());
    for (int i = 0; i < rowLen; i++)
    {
        indices.push_back(glm::uvec2(i * rowLen, (i + 1) * rowLen - 1));
        indices.push_back(glm::uvec2(i, vertices.size() - rowLen + i));
    }
    m_indicesCount = static_cast<GLsizei>(indices.size() * sizeof(glm::uvec2));


    GLuint vertexBuffer, indexBuffer;

    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(glm::uvec2), indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    glEnableVertexAttribArray(0);
}
