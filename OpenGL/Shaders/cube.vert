#version 410 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec2 vertexUV;
layout(location = 2) in vec3 offsetPos;

uniform mat4 u_mvpMatrix;
uniform mat4 u_rotationMatrix;

//out vec3 theColor;
out vec2 texCoords;

void main()
{
    vec4 transformedPos = u_rotationMatrix * vec4(pos, 1.0f) + vec4(offsetPos, 0.0f);

    gl_Position = u_mvpMatrix * transformedPos;
    texCoords = vertexUV;
};
