#include "Block.h"

const float Block::SIZE = 1.0f; // [0.0 - 1.0]

const Block::FACE Block::Face::FRONT =
{
    Vertex{ glm::vec3(0.0f, 0.0f, 1.0f) * SIZE, glm::vec3(0.0f, 0.0f, 1.0f),  glm::vec2(0.0f, 0.0f) },
    Vertex{ glm::vec3(1.0f, 0.0f, 1.0f) * SIZE, glm::vec3(0.0f, 0.0f, 1.0f),  glm::vec2(1.0f, 0.0f) },
    Vertex{ glm::vec3(1.0f, 1.0f, 1.0f) * SIZE, glm::vec3(0.0f, 0.0f, 1.0f),  glm::vec2(1.0f, 1.0f) },
    Vertex{ glm::vec3(0.0f, 1.0f, 1.0f) * SIZE, glm::vec3(0.0f, 0.0f, 1.0f),  glm::vec2(0.0f, 1.0f) },
};

const Block::FACE Block::Face::BACK =
{
    Vertex{ glm::vec3(1.0f, 0.0f, 0.0f) * SIZE, glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(0.0f, 0.0f) },
    Vertex{ glm::vec3(0.0f, 0.0f, 0.0f) * SIZE, glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(1.0f, 0.0f) },
    Vertex{ glm::vec3(0.0f, 1.0f, 0.0f) * SIZE, glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(1.0f, 1.0f) },
    Vertex{ glm::vec3(1.0f, 1.0f, 0.0f) * SIZE, glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(0.0f, 1.0f) },
};

const Block::FACE Block::Face::LEFT =
{
    Vertex{ glm::vec3(0.0f, 0.0f, 0.0f) * SIZE, glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f) },
    Vertex{ glm::vec3(0.0f, 0.0f, 1.0f) * SIZE, glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f) },
    Vertex{ glm::vec3(0.0f, 1.0f, 1.0f) * SIZE, glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f) },
    Vertex{ glm::vec3(0.0f, 1.0f, 0.0f) * SIZE, glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 1.0f) },
};

const Block::FACE Block::Face::RIGHT =
{
    Vertex{ glm::vec3(1.0f, 0.0f, 1.0f) * SIZE, glm::vec3(1.0f, 0.0f, 0.0f),  glm::vec2(0.0f, 0.0f) },
    Vertex{ glm::vec3(1.0f, 0.0f, 0.0f) * SIZE, glm::vec3(1.0f, 0.0f, 0.0f),  glm::vec2(1.0f, 0.0f) },
    Vertex{ glm::vec3(1.0f, 1.0f, 0.0f) * SIZE, glm::vec3(1.0f, 0.0f, 0.0f),  glm::vec2(1.0f, 1.0f) },
    Vertex{ glm::vec3(1.0f, 1.0f, 1.0f) * SIZE, glm::vec3(1.0f, 0.0f, 0.0f),  glm::vec2(0.0f, 1.0f) },
};

const Block::FACE Block::Face::TOP =
{
    Vertex{ glm::vec3(0.0f, 1.0f, 1.0f) * SIZE, glm::vec3(0.0f, 1.0f, 0.0f),  glm::vec2(0.0f, 0.0f) },
    Vertex{ glm::vec3(1.0f, 1.0f, 1.0f) * SIZE, glm::vec3(0.0f, 1.0f, 0.0f),  glm::vec2(1.0f, 0.0f) },
    Vertex{ glm::vec3(1.0f, 1.0f, 0.0f) * SIZE, glm::vec3(0.0f, 1.0f, 0.0f),  glm::vec2(1.0f, 1.0f) },
    Vertex{ glm::vec3(0.0f, 1.0f, 0.0f) * SIZE, glm::vec3(0.0f, 1.0f, 0.0f),  glm::vec2(0.0f, 1.0f) },
};

const Block::FACE Block::Face::BOTTOM =
{
    Vertex{ glm::vec3(0.0f, 0.0f, 0.0f) * SIZE, glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(0.0f, 0.0f) },
    Vertex{ glm::vec3(1.0f, 0.0f, 0.0f) * SIZE, glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(1.0f, 0.0f) },
    Vertex{ glm::vec3(1.0f, 0.0f, 1.0f) * SIZE, glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(1.0f, 1.0f) },
    Vertex{ glm::vec3(0.0f, 0.0f, 1.0f) * SIZE, glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(0.0f, 1.0f) },
};
