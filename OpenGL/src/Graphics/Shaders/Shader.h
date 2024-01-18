#pragma once

#include <GL/glew.h>
#include <string>

class Shader
{
public:
    ~Shader();

    void use() { glUseProgram(m_shaderProgramID); }

protected:
    void loadShader(const std::string& filepath);

    GLuint m_shaderProgramID;

private:
    struct ShaderSource
    {
        std::string vertex;
        std::string fragment;
    };

    ShaderSource parseShader(const std::string& filepath);
    GLuint       createShader(const ShaderSource& source);
    GLuint       compileShader(GLenum type, const std::string& source);
};
