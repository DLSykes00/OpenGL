#pragma once

#include <glm/glm.hpp>
#include <string>

class Shader
{
public:
    void useShader();
    void setUniformColor(float r, float g, float b, float a);
    void setMvpMatrix(float angle, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix);

    void setUniform1i(const std::string& name, int value);

private:
    struct ShaderSourceStruct
    {
        std::string vertexSource;
        std::string fragmentSource;
    };

    unsigned int shaderID;

    Shader::ShaderSourceStruct parseShader(const std::string& filepath);
    unsigned int compileShader(unsigned int type, const std::string& source);
    unsigned int createShader(const std::string& vertexShaderSource, const std::string& fragmentShaderSource);
};
