#include "TerrainShader.h"

TerrainShader::TerrainShader()
{
    Shader::loadShader(m_shaderPath);

    m_mvpMatrixUniform     = glGetUniformLocation(m_shaderProgramID, "u_mvpMatrix");
    m_lightPosWorldUniform = glGetUniformLocation(m_shaderProgramID, "u_lightPosWorld");
    m_chunkPosWorldUniform = glGetUniformLocation(m_shaderProgramID, "u_chunkPosWorld");
}

void TerrainShader::setMvp(const glm::mat4& modelMatrix, const glm::mat4& projectionViewMatrix)
{
    glUniformMatrix4fv(m_mvpMatrixUniform, 1, GL_FALSE, glm::value_ptr(projectionViewMatrix * modelMatrix));
}

void TerrainShader::setLightPosition(const glm::vec3& position)
{
    glUniform3f(m_lightPosWorldUniform, position.x, position.y, position.z);
}

void TerrainShader::setChunkPosition(const glm::vec3& position)
{
    glUniform3f(m_chunkPosWorldUniform, position.x, position.y, position.z);
}
