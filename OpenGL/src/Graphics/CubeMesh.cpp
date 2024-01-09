#include "CubeMesh.h"
#include <array>
#include <vector>

struct Vertex
{
    glm::vec3 position;
    glm::vec2 texture;
};

CubeMesh::CubeMesh()
{
    // Vertices
    std::array<Vertex, 24> vertices =
    {
        // Front
        Vertex{ glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec2(0.0f, 0.0f) }, // 0
        Vertex{ glm::vec3( 0.5f, -0.5f,  0.5f), glm::vec2(1.0f, 0.0f) }, // 1
        Vertex{ glm::vec3( 0.5f,  0.5f,  0.5f), glm::vec2(1.0f, 1.0f) }, // 2
        Vertex{ glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec2(0.0f, 1.0f) }, // 3
        // Left
        Vertex{ glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 0.0f) }, // 4
        Vertex{ glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec2(1.0f, 0.0f) }, // 5
        Vertex{ glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec2(1.0f, 1.0f) }, // 6
        Vertex{ glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec2(0.0f, 1.0f) }, // 7
        // Back
        Vertex{ glm::vec3( 0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 0.0f) }, // 8
        Vertex{ glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(1.0f, 0.0f) }, // 9
        Vertex{ glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec2(1.0f, 1.0f) }, // 10
        Vertex{ glm::vec3( 0.5f,  0.5f, -0.5f), glm::vec2(0.0f, 1.0f) }, // 11
        // Right
        Vertex{ glm::vec3(0.5f, -0.5f,  0.5f), glm::vec2(0.0f, 0.0f) }, // 12
        Vertex{ glm::vec3(0.5f, -0.5f, -0.5f), glm::vec2(1.0f, 0.0f) }, // 13
        Vertex{ glm::vec3(0.5f,  0.5f, -0.5f), glm::vec2(1.0f, 1.0f) }, // 14
        Vertex{ glm::vec3(0.5f,  0.5f,  0.5f), glm::vec2(0.0f, 1.0f) }, // 15
        // Top
        Vertex{ glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec2(0.0f, 0.0f) }, // 16
        Vertex{ glm::vec3( 0.5f,  0.5f,  0.5f), glm::vec2(1.0f, 0.0f) }, // 17
        Vertex{ glm::vec3( 0.5f,  0.5f, -0.5f), glm::vec2(1.0f, 1.0f) }, // 18
        Vertex{ glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec2(0.0f, 1.0f) }, // 19
        // Bottom
        Vertex{ glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 0.0f) }, // 20
        Vertex{ glm::vec3( 0.5f, -0.5f, -0.5f), glm::vec2(1.0f, 0.0f) }, // 21
        Vertex{ glm::vec3( 0.5f, -0.5f,  0.5f), glm::vec2(1.0f, 1.0f) }, // 22
        Vertex{ glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec2(0.0f, 1.0f) }, // 23
    };

    std::array<glm::uvec3, 12> indices =
    {
        glm::uvec3(0,  1,  2), glm::uvec3(2,  3,  0), // Front
        glm::uvec3(4,  5,  6), glm::uvec3(6,  7,  4), // Left
        glm::uvec3(8,  9, 10), glm::uvec3(10, 11,  8), // Back
        glm::uvec3(12, 13, 14), glm::uvec3(14, 15, 12), // Right
        glm::uvec3(16, 17, 18), glm::uvec3(18, 19, 16), // Top
        glm::uvec3(20, 21, 22), glm::uvec3(22, 23, 20), // Bottom
    };
    m_indicesCount = static_cast<GLsizei>(indices.size() * 3);

    // Instances
    std::vector<glm::vec3> instances;

    int size = 3;
    int spacing = 5;
    for (int i = 0; i < size; i++)
    {
        float x = static_cast<float>((spacing * i) - (spacing * (size-1)) / 2);
        for (int j = 0; j < size; j++)
        {
            float z = static_cast<float>(spacing * -j);
            instances.push_back(glm::vec3(x, 0.0f, z));
        }
    }
    //instances.push_back(glm::vec3(-1.0f, 0.0f, 0.0f));
    //instances.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
    m_instanceCount = static_cast<GLsizei>(instances.size());

    GLuint vertexBuffer, indexBuffer, instanceBuffer;
    // Create vao
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    // Vertices + Indices
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(sizeof(glm::vec3)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(glm::uvec3), indices.data(), GL_STATIC_DRAW);

    // Instance
    glGenBuffers(1, &instanceBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, instanceBuffer);
    glBufferData(GL_ARRAY_BUFFER, instances.size() * sizeof(glm::vec3), instances.data(), GL_STATIC_DRAW);

    glVertexAttribDivisor(2, 1);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    glEnableVertexAttribArray(2);
}
