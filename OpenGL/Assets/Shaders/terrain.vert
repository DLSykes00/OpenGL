#version 410 core

layout(location = 0) in vec3 v_pos;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec2 v_texCoords;

out vec3 f_pos;
out vec3 f_normal;
out vec2 f_texCoords;

uniform mat4 u_mvpMatrix;

void main()
{
    gl_Position = u_mvpMatrix * vec4(v_pos, 1.0f);

    f_pos = v_pos;
    f_normal = v_normal;
    f_texCoords = v_texCoords;
};
