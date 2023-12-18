#pragma once

#include <glm/gtc/type_ptr.hpp>
#include <string>

class Shader
{
public:
    Shader();
    void useCubeShader();
    void useBasicShader();

    void setUniformColor(float r, float g, float b, float a);
    void setMvpMatrix(const glm::mat4& modelMatrix, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix, float angle);
    void setUniform1i(const std::string& name, int value);

private:
    struct ShaderSourceStruct
    {
        std::string vertexSource;
        std::string fragmentSource;
    };

    std::string vertShader;
    std::string fragmentShader;

    uint32_t shaderID;
    uint32_t cubeShaderID;
    uint32_t basicShaderID;

    void loadShaders();
    void parseShader(const std::string& filepath);
    uint32_t compileShader(unsigned int type, const std::string& source);
    uint32_t createShader(const std::string& vertexShaderSource, const std::string& fragmentShaderSource);
};
