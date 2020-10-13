#pragma once

#include "Test.h"

#include "../Renderer.h"
#include "../VertexArray.h"
#include "../VertexBufferLayout.h"
#include "../Texture.h"

#include <memory>

namespace tests
{
    struct TVertex
    {
        glm::vec3 Position;
        glm::vec4 Color;
        glm::vec2 TexCoords;
        float TexID;
    };

    class TestBatchingDynamic : public Test
    {
        private:
            float m_PosQuad1[3];

            std::unique_ptr<VertexArray> m_VAO; 
            std::unique_ptr<IndexBuffer> m_IndexBuffer;
            std::unique_ptr<Shader> m_Shader;
            std::unique_ptr<Texture> m_Texture1;
            std::unique_ptr<Texture> m_Texture2;
            std::unique_ptr<VertexBuffer> m_VB;

        public:
            TestBatchingDynamic();
            ~TestBatchingDynamic();

            void OnUpdate(float deltaTime) override;
            void OnRender() override;
            void OnImGuiRender() override;

            static std::array<unsigned int, 6> CreateQuadIndices(unsigned int offsetCount);
            static std::array<TVertex, 4> CreateQuad(glm::vec3 cornerPos, float size, glm::vec4 color, float texID);
    };
    
} // namespace tests