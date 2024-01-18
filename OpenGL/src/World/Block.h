#pragma once

#include <glm/gtc/type_ptr.hpp>
#include <array>

const struct Block
{
    static const float SIZE;

    struct Type
    {
        const enum ID
        {
            AIR = 0,
            SOLID = 1
        };
    };
    
    const struct Vertex
    {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec2 texture;
    };

    typedef const std::array<Vertex, 4> FACE;

    const struct Face
    {
        static const std::array<Vertex, 4> FRONT;
        static const std::array<Vertex, 4> BACK;
        static const std::array<Vertex, 4> LEFT;
        static const std::array<Vertex, 4> RIGHT;
        static const std::array<Vertex, 4> TOP;
        static const std::array<Vertex, 4> BOTTOM;
    };
};
