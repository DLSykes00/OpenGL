#pragma once

#include "Block.h"
#include <GL/glew.h>
#include <vector>
#include <memory>

class FastNoiseLite;

class Chunk
{
public:
    Chunk(const glm::vec3& chunkIndex, const FastNoiseLite& noise);
    ~Chunk();

    void setNeighbours(const std::weak_ptr<Chunk> xPos, const std::weak_ptr<Chunk> xNeg,
                       //const std::shared_ptr<Chunk>& yPos, const std::shared_ptr<Chunk>& yNeg,
                       const std::weak_ptr<Chunk> zPos, const std::weak_ptr<Chunk> zNeg);
    void generateMesh();
    void generateVao(); // Should be called from thread responible for issuing OpenGL commands

    GLuint getVao()          { return m_vao; }
    GLuint getIndicesCount() { return m_meshIndicesCount; }

    const glm::vec3& getPosition() const    { return m_position; }
    int   getChunkSize()                    { return m_CHUNK_SIZE; }
    char  getBlock(char x, char y, char z)  { return m_blocks[x][y][z]; }

private:
    const int m_CHUNK_SIZE = 32;

    const int m_LENGTH_BLOCKS = static_cast<int>(m_CHUNK_SIZE / Block::SIZE);
    std::vector<std::vector<std::vector<uint8_t>>> m_blocks;
    glm::vec3 m_position = { 0.0f, 0.0f, 0.0f };

    GLuint m_vao = NULL;
    GLuint m_meshIndicesCount = 0;

    GLuint m_vbo, m_ebo;
    std::vector<Block::Vertex> m_meshVertices;
    std::vector<glm::uvec3>    m_meshIndices;

    void generateBlocks(const FastNoiseLite& noise);
    
    void addMeshFace(const Block::FACE& face, const glm::vec3& localPosition);

    const struct Neighbours
    { 
        std::weak_ptr<Chunk> xPos; std::weak_ptr<Chunk> xNeg;
        //std::shared_ptr<Chunk> yPos; std::shared_ptr<Chunk> yNeg;
        std::weak_ptr<Chunk> zPos; std::weak_ptr<Chunk> zNeg;
    };
    Neighbours m_neighbours;
};
