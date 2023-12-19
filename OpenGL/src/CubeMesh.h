#pragma once

#include <glm/gtc/type_ptr.hpp>

class CubeMesh
{
public:
	CubeMesh();

	GLuint getVao() { return vao; };
	GLsizei getIndiciesCount() { return indicesCount; };
	GLsizei getInstanceCount() { return instanceCount; };

private:
	GLuint vao;

	GLsizei indicesCount;
	GLsizei instanceCount;
};
