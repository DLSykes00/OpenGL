#version 410 core

layout(location = 0) in vec4 v_pos;
layout(location = 1) in vec2 v_texCoords;

out vec2 f_texCoords;

uniform mat4 u_mvpMatrix;

void main()
{
    gl_Position = u_mvpMatrix * v_pos;

    f_texCoords = v_texCoords;
};
