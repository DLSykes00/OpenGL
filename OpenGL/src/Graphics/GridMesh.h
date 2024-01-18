#pragma once

#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>

class GridMesh
{
public:
    GridMesh();
    ~GridMesh();

    GLuint  getVao()          { return m_vao; }
    GLsizei getIndicesCount() { return m_indicesCount; }

private:
    int m_gridSlices = 1056;

    GLuint  m_vao;
    GLsizei m_indicesCount;

    GLuint m_vbo;
    GLuint m_ebo;
};
