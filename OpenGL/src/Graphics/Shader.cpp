#include "Shader.h"
#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

Shader::Shader()
{
    loadShaders();
}

void Shader::loadShaders()
{
    ShaderSource s = parseShader("Shaders/basic");
    m_basicShaderID = createShader(s.vertexSource, s.fragmentSource);

    s = parseShader("Shaders/cube");
    m_cubeShaderID = createShader(s.vertexSource, s.fragmentSource);
}

Shader::ShaderSource Shader::parseShader(const std::string& filepath)
{
    std::stringstream inputShaderSource[2];
    std::string line;

    // Read vertex shader
    std::ifstream vertex(filepath + ".vert");
    while (getline(vertex, line))
        inputShaderSource[0] << line << '\n';

    // Read fragment shader
    std::ifstream fragment(filepath + ".frag");
    while (getline(fragment, line))
        inputShaderSource[1] << line << '\n';

    ShaderSource s;
    s.vertexSource = inputShaderSource[0].str();
    s.fragmentSource = inputShaderSource[1].str();

    return s;
}

uint32_t Shader::createShader(const std::string& vertexShaderSource, const std::string& fragmentShaderSource)
{
    uint32_t program = glCreateProgram();
    uint32_t vertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderSource);
    uint32_t fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return program;
}

uint32_t Shader::compileShader(uint32_t type, const std::string& source)
{
    uint32_t id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);

    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)malloc(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);

        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT") << " shader!" << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);
        free(message);
        return 0;
    }

    return id;
}

void Shader::useCubeShader()
{
    glUseProgram(m_cubeShaderID);
    m_shaderID = m_cubeShaderID;
}

void Shader::useBasicShader()
{
    glUseProgram(m_basicShaderID);
    m_shaderID = m_basicShaderID;
}

void Shader::setUniform4fv(const char* uniform, const glm::mat4& matrix)
{
    glUniformMatrix4fv(glGetUniformLocation(m_shaderID, uniform), 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::setUniformColor(float r, float g, float b, float a)
{
    int uniformLocation = glGetUniformLocation(m_shaderID, "u_Color");
    glUniform4f(uniformLocation, r, g, b, a);
}

void Shader::setMvpMatrix(const glm::mat4& modelMatrix, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix)
{
    glm::mat4 mvpMatrix = projectionMatrix * viewMatrix * modelMatrix;

    glUniformMatrix4fv(glGetUniformLocation(m_shaderID, "u_mvpMatrix"), 1, GL_FALSE, glm::value_ptr(mvpMatrix));
}
