#include "Shader.h"

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>



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

Shader::ShaderSourceStruct Shader::parseShader(const std::string& filepath)
{
    //C FILE API FASTER, CHANGE EVENTUALLY

    std::ifstream stream(filepath);
    std::string line;
    std::stringstream inputShaderSource[2];
    int type;

    while (getline(stream, line))
    {
        if (line.find("#shader vertex") != std::string::npos)
        {
            type = 0;
        }
        else if (line.find("#shader fragment") != std::string::npos)
        {
            type = 1;
        }
        else
        {
            inputShaderSource[type] << line << '\n';
        }
    }

    Shader::ShaderSourceStruct sss;
    sss.vertexSource = inputShaderSource[0].str();
    sss.fragmentSource = inputShaderSource[1].str();

    return sss;
}

void Shader::useShader()
{
    Shader::ShaderSourceStruct sss = parseShader("Shaders/Shader.shader");
    shaderID = createShader(sss.vertexSource, sss.fragmentSource);
    glUseProgram(shaderID);
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

void Shader::setProjectionMatrix(float angle, float x = 0.0f, float y = 0.0f, float z = -0.0f, float xRot = 0.0f, float yRot = 0.0f)
{
    glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -5.0));

    //glm::mat4 viewMatrix = glm::lookAt(glm::vec3(x, y, z), glm::vec3(xRot, yRot, -5.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 viewMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(xRot), glm::vec3(1.0f, 0.0f, 0.0f)); //apply x rotation from camera
    viewMatrix = glm::rotate(viewMatrix, glm::radians(yRot), glm::vec3(0.0f, 1.0f, 0.0f)); //apply y rotation from camera
    viewMatrix = glm::translate(viewMatrix, glm::vec3(x, y, z)); //apply translation from camera
    
    glm::mat4 projectionMatrix = glm::perspective(glm::radians(75.0f), 1.0f, 0.1f, 300.0f);

    glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));

    glm::mat4 finalMatrix = projectionMatrix * viewMatrix  * modelMatrix;

    glUniformMatrix4fv(glGetUniformLocation(shaderID, "u_transformMatrix"), 1, GL_FALSE, glm::value_ptr(finalMatrix));

    glUniformMatrix4fv(glGetUniformLocation(shaderID, "u_rotationMatrix"), 1, GL_FALSE, glm::value_ptr(rotationMatrix));
}

