#version 410 core

in vec2 f_texCoords;

layout(location = 0) out vec4 color;

uniform sampler2D u_texture;
uniform bool      u_useTexture = true;
uniform vec4      u_color      = vec4(0.9f, 0.9f, 0.9f, 1.0f);

void main()
{
	if (u_useTexture)
		color = texture(u_texture, f_texCoords);
	else
		color = u_color;
};
