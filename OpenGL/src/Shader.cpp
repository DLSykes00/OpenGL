#include "Shader.h"
#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

Shader::Shader()
{
    loadShaders();
}

unsigned int Shader::compileShader(unsigned int type, const std::string& source)
{
    unsigned int id = glCreateShader(type);
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

unsigned int Shader::createShader(const std::string& vertexShaderSource, const std::string& fragmentShaderSource)
{
    unsigned int program = glCreateProgram();
    unsigned int vertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderSource);
    unsigned int fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return program;
}

void Shader::parseShader(const std::string& filepath)
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

    Shader::ShaderSourceStruct sss;
    vertShader = inputShaderSource[0].str();
    fragmentShader = inputShaderSource[1].str();
}

void Shader::loadShaders()
{
    parseShader("Shaders/basic");
    basicShaderID = createShader(vertShader, fragmentShader);

    parseShader("Shaders/cube");
    cubeShaderID = createShader(vertShader, fragmentShader);

    useBasicShader();
}

void Shader::useBasicShader()
{
    glUseProgram(basicShaderID);
    shaderID = basicShaderID;
}

void Shader::useCubeShader()
{
    glUseProgram(cubeShaderID);
    shaderID = cubeShaderID;
}

void Shader::setUniformColor(float r, float g, float b, float a)
{
    int uniformLocation = glGetUniformLocation(shaderID, "u_Color");
    glUniform4f(uniformLocation, r, g, b, a);
}

void Shader::setUniform1i(const std::string& name, int value)
{
    int uniformLocation = glGetUniformLocation(shaderID, name.c_str());
    glUniform1i(uniformLocation, value);
}

void Shader::setMvpMatrix(const glm::mat4& modelMatrix, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix, float angle)
{
    glm::mat4 mvpMatrix = projectionMatrix * viewMatrix  * modelMatrix;

    glUniformMatrix4fv(glGetUniformLocation(shaderID, "u_mvpMatrix"), 1, GL_FALSE, glm::value_ptr(mvpMatrix));

    glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));

    glUniformMatrix4fv(glGetUniformLocation(shaderID, "u_rotationMatrix"), 1, GL_FALSE, glm::value_ptr(rotationMatrix));
}
