#version 410 core

layout(location = 0) out vec4 color;

//uniform vec4 u_Color;
//in vec3 theColor;

uniform sampler2D u_Texture;
in vec2 texCoords;


void main()
{
    color = texture(u_Texture, texCoords);
};
