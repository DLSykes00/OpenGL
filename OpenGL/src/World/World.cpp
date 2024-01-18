#include "World.h"
#include "Chunk.h"
#include <chrono>
#include <string>
#include <iostream>

World::World(int seed)
{
    m_noiseSeed = seed;

    m_noise.SetNoiseType(m_noiseType);
    m_noise.SetFrequency(m_noiseFrequency);
    m_noise.SetFractalType(m_noiseFractalType);
    m_noise.SetFractalOctaves(m_noiseFractalOctaves);
    m_noise.SetSeed(m_noiseSeed);

    std::thread(&World::loadChunks, this).detach();
}

void World::loadChunks()
{
    std::vector<std::vector<std::shared_ptr<Chunk>>> chunks;

    // Create chunk blocks with 1 chunk buffer in +/- x/z direction
    for (int x = -m_renderDistance - 1; x <= m_renderDistance + 1; x++)
    {
        std::vector<std::shared_ptr<Chunk>> chunkRow;
        for (int z = -m_renderDistance - 1; z <= m_renderDistance + 1; z++)
        {
            chunkRow.push_back(std::make_shared<Chunk>(glm::vec3(x, 0.0f, z), m_noise));
        }
        chunks.push_back(chunkRow);
    }    

    auto start = std::chrono::high_resolution_clock::now();

    // Generate meshes for chunks inside buffer
    for (int x = 1; x < chunks.size() - 1; x++)
    {
        std::vector<std::shared_ptr<Chunk>> chunkRow;
        for (int z = 1; z < chunks[x].size() - 1; z++)
        {
            chunks[x][z]->setNeighbours(chunks[x + 1][z], chunks[x - 1][z],
                                      //chunks[x][z], chunks[x][z],
                                        chunks[x][z + 1], chunks[x][z - 1]);
            chunks[x][z]->generateMesh();
            chunkRow.push_back(chunks[x][z]);
        }
        m_mutex.lock();
        m_chunks.push_back(chunkRow);
        m_mutex.unlock();
    }
    std::chrono::microseconds chunksUs = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start);
    std::string outputString = "\n\nGenerated " + std::to_string(m_chunks.size() * m_chunks[0].size())
                             + " chunk meshes in " + std::to_string(chunksUs.count() / 1000.0f) + " mS\n\n";
    std::cout << outputString;
}
