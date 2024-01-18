#pragma once

#include <glm/gtc/type_ptr.hpp>
#include <FastNoise/FastNoiseLite.h>
#include <vector>
#include <memory>
#include <thread>
#include <mutex>

class Chunk;

class World
{
public:
    World(int seed = rand() * INT_MAX);

    const std::vector<std::vector<std::shared_ptr<Chunk>>> getChunks() { std::lock_guard<std::mutex> lk(m_mutex); return m_chunks; }

private:
    const int m_renderDistance = 16;

    FastNoiseLite              m_noise;
    FastNoiseLite::NoiseType   m_noiseType        = FastNoiseLite::NoiseType_OpenSimplex2;
    FastNoiseLite::FractalType m_noiseFractalType = FastNoiseLite::FractalType_FBm;
    int   m_noiseFractalOctaves = 3;
    int   m_noiseSeed           = 1234;
    float m_noiseFrequency      = 0.005f;

    std::vector<std::vector<std::shared_ptr<Chunk>>> m_chunks;

    std::mutex m_mutex;

    void loadChunks();
};
