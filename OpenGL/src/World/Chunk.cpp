#include "Chunk.h"
#include <FastNoise/FastNoiseLite.h>
#include <thread>
#include <random>
#include <chrono>

Chunk::Chunk(const glm::vec3& chunkIndex, const FastNoiseLite& noise)
{
    m_position = chunkIndex;
    m_position *= m_CHUNK_SIZE;

    m_blocks.resize(m_LENGTH_BLOCKS, std::vector<std::vector<uint8_t>>(m_LENGTH_BLOCKS, std::vector<uint8_t>(m_LENGTH_BLOCKS)));

    generateBlocks(noise);
}

Chunk::~Chunk()
{
    glDeleteVertexArrays(1, &m_vao);
    glDeleteBuffers(1, &m_vbo);
    glDeleteBuffers(1, &m_ebo);
}

void Chunk::generateBlocks(const FastNoiseLite& noise)
{
    int noiseFloor = m_CHUNK_SIZE / 4;
    int noiseCeil = m_CHUNK_SIZE;
    int maxNoiseHeight = noiseCeil - noiseFloor;

    for (int x = 0; x < m_LENGTH_BLOCKS; x++)
    for (int z = 0; z < m_LENGTH_BLOCKS; z++)
    {
        float noiseHeight = std::round((maxNoiseHeight / Block::SIZE) *
            noise.GetNoise(m_position.x / Block::SIZE + x, m_position.z / Block::SIZE + z));
        noiseHeight += (maxNoiseHeight / Block::SIZE);
        noiseHeight *= 0.5f;

        for (int y = 0; y < noiseFloor + noiseHeight; y++)
            m_blocks[x][y][z] = Block::Type::SOLID;
    }
}

void Chunk::setNeighbours(const std::weak_ptr<Chunk> xPos, const std::weak_ptr<Chunk> xNeg,
    //const std::weak_ptr<Chunk>& yPos, const std::weak_ptr<Chunk>& yNeg,
    const std::weak_ptr<Chunk> zPos, const std::weak_ptr<Chunk> zNeg)
{
    m_neighbours.xPos = xPos; m_neighbours.xNeg = xNeg;
    //m_neighbours.yPos = yPos; m_neighbours.yNeg = yNeg;
    m_neighbours.zPos = zPos; m_neighbours.zNeg = zNeg;
}


void Chunk::generateMesh()
{
    glm::vec3 localPosition = glm::vec3(0.0f);

    for (int x = 0; x < m_LENGTH_BLOCKS; x++)
    {
        localPosition.x = x * Block::SIZE - 0.5f * m_CHUNK_SIZE;
        for (int y = 0; y < m_LENGTH_BLOCKS; y++)
        {
            localPosition.y = y * Block::SIZE - 0.5f * m_CHUNK_SIZE;
            for (int z = 0; z < m_LENGTH_BLOCKS; z++)
            {
                if (m_blocks[x][y][z] == Block::Type::AIR) continue;

                localPosition.z = z * Block::SIZE - 0.5f * m_CHUNK_SIZE;

                if (x > 0 && m_blocks[x - 1][y][z] == Block::Type::AIR)
                    addMeshFace(Block::Face::LEFT, localPosition);
                else if (x == 0 && m_neighbours.xNeg.lock()->getBlock(m_LENGTH_BLOCKS - 1, y, z) == Block::Type::AIR)
                    addMeshFace(Block::Face::LEFT, localPosition);

                if (x < m_LENGTH_BLOCKS - 1 && m_blocks[x + 1][y][z] == Block::Type::AIR)
                    addMeshFace(Block::Face::RIGHT, localPosition);
                else if (x == m_LENGTH_BLOCKS - 1 && m_neighbours.xPos.lock()->getBlock(0, y, z) == Block::Type::AIR)
                    addMeshFace(Block::Face::RIGHT, localPosition);

                if (y > 0 && m_blocks[x][y - 1][z] == Block::Type::AIR)
                    addMeshFace(Block::Face::BOTTOM, localPosition);
                
                if (y < m_LENGTH_BLOCKS - 1 && m_blocks[x][y + 1][z] == Block::Type::AIR)
                    addMeshFace(Block::Face::TOP, localPosition);
                else if (y == m_LENGTH_BLOCKS - 1)
                    addMeshFace(Block::Face::TOP, localPosition);

                if (z > 0 && m_blocks[x][y][z - 1] == Block::Type::AIR)
                    addMeshFace(Block::Face::BACK, localPosition);
                else if (z == 0 && m_neighbours.zNeg.lock()->getBlock(x, y, m_LENGTH_BLOCKS - 1) == Block::Type::AIR)
                    addMeshFace(Block::Face::BACK, localPosition);

                if (z < m_LENGTH_BLOCKS - 1 && m_blocks[x][y][z + 1] == Block::Type::AIR)
                    addMeshFace(Block::Face::FRONT, localPosition);
                else if (z == m_LENGTH_BLOCKS - 1 && m_neighbours.zPos.lock()->getBlock(x, y, 0) == Block::Type::AIR)
                    addMeshFace(Block::Face::FRONT, localPosition);
            }
        }
    }
    m_meshIndicesCount = static_cast<GLsizei>(m_meshIndices.size() * 3);
}

void Chunk::addMeshFace(const Block::FACE& face, const glm::vec3& localPosition)
{
    size_t index = m_meshVertices.size();

    for (Block::Vertex vert : face)
    {
        vert.position += localPosition;
        m_meshVertices.push_back(vert);
    }

    m_meshIndices.push_back(glm::uvec3(0 + index, 1 + index, 2 + index));
    m_meshIndices.push_back(glm::uvec3(2 + index, 3 + index, 0 + index));
}

void Chunk::generateVao()
{
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, m_meshVertices.size() * sizeof(Block::Vertex), m_meshVertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Block::Vertex), (GLvoid*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Block::Vertex), (GLvoid*)(sizeof(Block::Vertex::position)));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Block::Vertex), (GLvoid*)(sizeof(Block::Vertex::position) + sizeof(Block::Vertex::normal)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glGenBuffers(1, &m_ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_meshIndices.size() * sizeof(glm::uvec3), m_meshIndices.data(), GL_STATIC_DRAW);

    m_meshVertices.clear();
    m_meshIndices.clear();
    m_meshVertices.shrink_to_fit();
    m_meshIndices.shrink_to_fit();
}
