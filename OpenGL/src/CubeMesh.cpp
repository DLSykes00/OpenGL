#include <GL/glew.h>
#include "CubeMesh.h"
#include <vector>

CubeMesh::CubeMesh()
{
    // Vertices
    std::vector<glm::vec3> vertices;
    vertices.push_back(glm::vec3(-0.5f, -0.5f, -0.5f)); //0
    vertices.push_back(glm::vec3(-0.5f,  0.5f, -0.5f)); //1
    vertices.push_back(glm::vec3( 0.5f,  0.5f, -0.5f)); //2
    vertices.push_back(glm::vec3( 0.5f, -0.5f, -0.5f)); //3
    vertices.push_back(glm::vec3( 0.5f, -0.5f,  0.5f)); //4
    vertices.push_back(glm::vec3(-0.5f, -0.5f,  0.5f)); //5
    vertices.push_back(glm::vec3(-0.5f,  0.5f,  0.5f)); //6
    vertices.push_back(glm::vec3( 0.5f,  0.5f,  0.5f)); //7
  
    // Faces (tris)
    std::vector<glm::uvec3> indices;
    // front
    indices.push_back(glm::uvec3(0, 1, 2));
    indices.push_back(glm::uvec3(2, 3, 0));
    // left
    indices.push_back(glm::uvec3(0, 5, 6));
    indices.push_back(glm::uvec3(6, 1, 0));
    // back
    indices.push_back(glm::uvec3(4, 7, 6));
    indices.push_back(glm::uvec3(6, 5, 4));
    // right
    indices.push_back(glm::uvec3(4, 3, 2));
    indices.push_back(glm::uvec3(2, 7, 4));
    // top
    indices.push_back(glm::uvec3(1, 6, 7));
    indices.push_back(glm::uvec3(7, 2, 1));
    // bottom
    indices.push_back(glm::uvec3(3, 4, 5));
    indices.push_back(glm::uvec3(5, 0, 3));
    indicesCount = static_cast<GLsizei>(indices.size() * sizeof(glm::uvec3));

    // Textures (uv)
    std::vector<glm::vec2> textureUVs;
    for (int face = 0; face < 6; face++)
    {
        textureUVs.push_back(glm::vec2(0.0f, 0.0f));
        textureUVs.push_back(glm::vec2(1.0f, 0.0f));
        textureUVs.push_back(glm::vec2(1.0f, 1.0f));
        textureUVs.push_back(glm::vec2(0.0f, 1.0f));
    }

    // Instances
    std::vector<glm::vec3> instances;
    instances.push_back(glm::vec3(-1.0f, 0.0f, 0.0f));
    instances.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
    instanceCount = static_cast<GLsizei>(instances.size());


    GLuint vertexBuffer, indexBuffer, textureBuffer, instanceBuffer;
    // Create vao
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // Vertices + Indices
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(glm::uvec3), indices.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);

    // Texture
    glGenBuffers(1, &textureBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, textureBuffer);
    glBufferData(GL_ARRAY_BUFFER, textureUVs.size() * sizeof(glm::vec2), textureUVs.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);

    // Instance
    glGenBuffers(1, &instanceBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, instanceBuffer);
    glBufferData(GL_ARRAY_BUFFER, instances.size() * sizeof(glm::vec3), instances.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    glVertexAttribDivisor(2, 1);
}
