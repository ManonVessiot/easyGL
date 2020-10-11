#pragma once

#include "Test.h"

#include "../Renderer.h"
#include "../VertexArray.h"
#include "../VertexBufferLayout.h"
#include "../Texture.h"

#include <memory>

namespace tests
{
    class TestBatching : public Test
    {
        private:
            std::unique_ptr<VertexArray> m_VAO; 
            std::unique_ptr<IndexBuffer> m_IndexBuffer;
            std::unique_ptr<Shader> m_Shader;
            std::unique_ptr<Texture> m_Texture1;
            std::unique_ptr<Texture> m_Texture2;
            std::unique_ptr<VertexBuffer> m_VB;

        public:
            TestBatching();
            ~TestBatching();

            void OnUpdate(float deltaTime) override;
            void OnRender() override;
            void OnImGuiRender() override;
    };
    
} // namespace tests