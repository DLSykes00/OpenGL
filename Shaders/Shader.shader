#shader vertex
#version 410 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec2 vertexUV;
layout(location = 2) in vec3 offsetPos;

uniform mat4 u_transformMatrix;
uniform mat4 u_rotationMatrix;

out vec2 texCoords;
out vec3 theColor;


void main()
{
    vec4 rotatedPos = u_rotationMatrix * vec4(pos, 1.0f);

    vec4 translatedPos = rotatedPos + vec4(offsetPos, 0.0f);

    vec4 transformedPos = u_transformMatrix * translatedPos;

    gl_Position = transformedPos;

    texCoords = vertexUV;
};


#shader fragment
#version 410 core

layout(location = 0) out vec4 color;

uniform vec4 u_Color;
uniform sampler2D u_Texture;

in vec2 texCoords;
in vec3 theColor;


void main()
{
    color = texture(u_Texture, texCoords);
};