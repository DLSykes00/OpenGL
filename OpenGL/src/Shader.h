#pragma once

#include <string>

class Shader
{
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
    
public:
    void useShader();
    void setUniformColor(float r, float g, float b, float a);
    void setProjectionMatrix(float angle, float x, float y, float z, float xRot, float yRot );

    void setUniform1i(const std::string& name, int value);
};
