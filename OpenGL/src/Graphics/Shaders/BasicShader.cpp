#include "BasicShader.h"

BasicShader::BasicShader()
{
    loadShader(m_shaderPath);

    m_mvpMatrixUniform  = glGetUniformLocation(m_shaderProgramID, "u_mvpMatrix");
    m_useTextureUniform = glGetUniformLocation(m_shaderProgramID, "u_useTexture");
    m_colorUniform      = glGetUniformLocation(m_shaderProgramID, "u_color");
}

void BasicShader::setMvp(const glm::mat4& modelMatrix, const glm::mat4& projectionViewMatrix)
{
    glUniformMatrix4fv(m_mvpMatrixUniform, 1, GL_FALSE, glm::value_ptr(projectionViewMatrix * modelMatrix));
}

void BasicShader::setUseTexture(const bool b)
{
    glUniform1i(m_useTextureUniform, b);
}

void BasicShader::setColor(const glm::vec4& color)
{
    glUniform4f(m_colorUniform, color.r, color.g, color.b, color.a);
}
