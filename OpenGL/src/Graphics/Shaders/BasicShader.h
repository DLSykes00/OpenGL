#pragma once

#include "Shader.h"
#include <glm/gtc/type_ptr.hpp>

class BasicShader : public Shader
{
public:
    BasicShader();

    void setMvp(const glm::mat4& modelMatrix, const glm::mat4& projectionViewMatrix);
    void setColor(const glm::vec4& color);
    void useTexture() { setUseTexture(true); }
    void useColor()   { setUseTexture(false); }
    
private:
    void setUseTexture(const bool b);

    std::string m_shaderPath = "Assets/Shaders/basic";

    GLint m_mvpMatrixUniform;
    GLint m_useTextureUniform;
    GLint m_colorUniform;
};
