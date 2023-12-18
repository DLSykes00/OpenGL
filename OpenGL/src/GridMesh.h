#pragma once

#include <vector>
#include <glm/gtc/type_ptr.hpp>

class GridMesh
{
public:
	GridMesh();

	uint32_t getVertexBuffer() { return vbo; };
	uint32_t getIndexBuffer() { return indexBuffer; };
	const std::vector<glm::vec3>& getVertices() const { return vertices; };
	const std::vector<glm::uvec2>& getIndices() const { return indices; };

private:
	int gridSlices = 11;

	uint32_t vbo;
	uint32_t indexBuffer;

	std::vector<glm::vec3> vertices;
	std::vector<glm::uvec2> indices;
};
