#pragma once

#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>

class CubeMesh
{
public:
    CubeMesh();

    GLuint  getVao()           { return m_vao; }
    GLsizei getIndiciesCount() { return m_indicesCount; }
    GLsizei getInstanceCount() { return m_instanceCount; }

private:
    GLuint  m_vao;
    GLsizei m_indicesCount;
    GLsizei m_instanceCount;
};
