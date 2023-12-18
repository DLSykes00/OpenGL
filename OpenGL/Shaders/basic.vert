#version 410 core

layout(location = 0) in vec3 pos;

uniform mat4 u_mvpMatrix;

void main()
{
    gl_Position = u_mvpMatrix * vec4(pos, 1.0f);
};
