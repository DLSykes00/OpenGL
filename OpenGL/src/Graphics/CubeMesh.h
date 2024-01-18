#pragma once

#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>

class CubeMesh
{
public:
    CubeMesh();
    ~CubeMesh();

    GLuint  getVao()           { return m_vao; }
    GLsizei getIndicesCount()  { return m_indicesCount; }

private:
    GLuint  m_vao;
    GLsizei m_indicesCount;

    GLuint m_vbo;
    GLuint m_ebo;
};
