#pragma once

#include <glm/gtc/type_ptr.hpp>

class GridMesh
{
public:
	GridMesh();

	GLuint getVao() { return vao; };
	GLsizei getIndicesCount() { return indicesCount; };

private:
	GLuint vao;

	GLsizei indicesCount;

	int gridSlices = 11;
};
