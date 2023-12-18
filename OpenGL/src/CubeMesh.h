#pragma once

#include <vector>
#include <glm/gtc/type_ptr.hpp>

class CubeMesh
{
public:
	CubeMesh();

	uint32_t getVertexBuffer() { return vertexBuffer; };
	uint32_t getIndexBuffer() { return indexBuffer; };
	uint32_t getTextureBuffer() { return textureBuffer; };
	uint32_t getInstanceBuffer() { return instanceBuffer; };

	const std::vector<glm::vec3>& getVertices() const { return vertices; };
	const std::vector<glm::uvec3>& getIndices() const { return indices; };
	const std::vector<glm::vec2>& getTextureUVs() const { return textureUVs; };
	const std::vector<glm::vec3>& getInstances() const { return instances; };

private:
	uint32_t vertexBuffer;
	uint32_t indexBuffer;
	uint32_t textureBuffer;
	uint32_t instanceBuffer;

	std::vector<glm::vec3> vertices;
	std::vector<glm::uvec3> indices;
	std::vector<glm::vec2> textureUVs;
	std::vector<glm::vec3> instances;
};
