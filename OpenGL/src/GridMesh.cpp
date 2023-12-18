#include <GL/glew.h>
#include "GridMesh.h"

GridMesh::GridMesh()
{
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
    int rowLen = gridSlices + 1;
    int noVert = static_cast<int>(vertices.size());
    for (int i = 0; i < rowLen; i++)
    {
        indices.push_back(glm::uvec2(i * rowLen, (i + 1) * rowLen - 1));
        indices.push_back(glm::uvec2(i, vertices.size() - rowLen + i));
    }

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(glm::uvec2), indices.data(), GL_STATIC_DRAW);
}
