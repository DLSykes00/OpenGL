#pragma once

#include <glm/gtc/type_ptr.hpp>
#include <string>

class Shader
{
public:
    Shader();

    void useCubeShader();
    void useBasicShader();
    
    void setUniform4fv(const char*, const glm::mat4& matrix);
    void setUniformColor(float r, float g, float b, float a);
    void setMvpMatrix(const glm::mat4& modelMatrix, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix);

private:
    struct ShaderSource
    {
        std::string vertexSource;
        std::string fragmentSource;
    };

    uint32_t m_shaderID;
    uint32_t m_cubeShaderID;
    uint32_t m_basicShaderID;

    void         loadShaders();
    ShaderSource parseShader(const std::string& filepath);
    uint32_t     createShader(const std::string& vertexShaderSource, const std::string& fragmentShaderSource);
    uint32_t     compileShader(uint32_t type, const std::string& source);
};
