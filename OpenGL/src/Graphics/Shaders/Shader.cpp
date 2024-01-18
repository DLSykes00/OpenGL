#include "Shader.h"
#include <fstream>
#include <sstream>
#include <iostream>

Shader::~Shader()
{
    glDeleteProgram(m_shaderProgramID);
}

void Shader::loadShader(const std::string& filepath)
{
    ShaderSource source = parseShader(filepath);
    m_shaderProgramID = createShader(source);
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

    ShaderSource source;
    source.vertex = inputShaderSource[0].str();
    source.fragment = inputShaderSource[1].str();

    return source;
}

GLuint Shader::createShader(const ShaderSource& source)
{
    GLuint program = glCreateProgram();

    GLuint vertexShader = compileShader(GL_VERTEX_SHADER, source.vertex);
    GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, source.fragment);

    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return program;
}

GLuint Shader::compileShader(GLenum type, const std::string& source)
{
    GLenum id = glCreateShader(type);

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
    }

    return id;
}
