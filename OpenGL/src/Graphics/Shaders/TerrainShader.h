#pragma once

#include "Shader.h"
#include <glm/gtc/type_ptr.hpp>

class TerrainShader : public Shader
{
public:
    TerrainShader();

    void setMvp(const glm::mat4& modelMatrix, const glm::mat4& projectionViewMatrix);
    void setLightPosition(const glm::vec3& vector);
    void setChunkPosition(const glm::vec3& position);

private:
    std::string m_shaderPath = "Assets/Shaders/terrain";

    GLint m_mvpMatrixUniform;
    GLint m_lightPosWorldUniform;
    GLint m_chunkPosWorldUniform;
};
