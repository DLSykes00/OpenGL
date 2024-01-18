#include "GridMesh.h"
#include <vector>

struct Vertex
{
    glm::vec3 position;
    glm::vec2 texture;
};

GridMesh::GridMesh()
{
    std::vector<glm::vec3> vertices;
    for (int i = -(m_gridSlices / 2); i <= m_gridSlices / 2; i++)
    for (int j = -(m_gridSlices / 2); j <= m_gridSlices / 2; j++)
    {
        float x = static_cast<float>(i);
        float y = 0.001f;
        float z = static_cast<float>(-j);
        vertices.push_back(glm::vec3(x, y, z));
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

    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex::position), vertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex::position), (GLvoid*)0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)(sizeof(Vertex::position)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glGenBuffers(1, &m_ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(glm::uvec2), indices.data(), GL_STATIC_DRAW);
}

GridMesh::~GridMesh()
{
    glDeleteVertexArrays(1, &m_vao);
    glDeleteBuffers(1, &m_vbo);
    glDeleteBuffers(1, &m_ebo);
}
