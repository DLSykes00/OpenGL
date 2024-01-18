#version 410 core

layout(location = 0) out vec4 color;

in vec3 f_pos;
in vec3 f_normal;
in vec2 f_texCoords;

uniform sampler2D u_texture;

uniform vec3 u_lightPosWorld;
uniform vec3 u_chunkPosWorld;
float ambientLightStrength = 0.5f;
float diffuseLightStrength = 1.0f;

void main()
{
	vec3 normal = normalize(f_normal);
	vec3 vertPosWorld = u_chunkPosWorld + f_pos;
	vec3 lightVector = normalize(u_lightPosWorld - vertPosWorld);

	vec3 ambientLight = vec3(ambientLightStrength);
	vec3 diffuseLight = diffuseLightStrength * vec3(max(dot(normal, lightVector), 0.0f));
	vec4 lighting = vec4(ambientLight + diffuseLight, 1.0f);

    color = texture(u_texture, f_texCoords) * lighting;
};
