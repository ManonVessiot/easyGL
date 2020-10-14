#pragma once

#include "Test.h"

#include "../Renderer.h"
#include "../VertexArray.h"
#include "../VertexBufferLayout.h"
#include "../Texture.h"
#include "../MyModel.h"

#include <memory>
#include <ctime>

namespace tests
{
    class TestLight : public Test
    {
        private:
            std::time_t m_TimeStart = std::time(0);

            easyGL::MyModel m_Model;
            float m_Trans[3];
            float m_Rot[3];
            float m_Scale[3];

            std::unique_ptr<easyGL::VertexArray> m_VAO; 
            std::unique_ptr<easyGL::IndexBuffer> m_IndexBuffer;
            std::unique_ptr<easyGL::Shader> m_Shader;
            std::unique_ptr<easyGL::VertexBuffer> m_VB;

        public:
            TestLight();
            ~TestLight();

            void OnUpdate(float deltaTime) override;
            void OnRender() override;
            void OnImGuiRender() override;
    };
    
} // namespace tests