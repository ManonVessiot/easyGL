#pragma once

#include "Test.h"

#include "../Renderer.h"
#include "../VertexArray.h"
#include "../VertexBufferLayout.h"
#include "../Texture.h"
#include "../MyModel.h"

#include <memory>

namespace tests
{
    class TestModel : public Test
    {
        private:
            MyModel m_Model;
            float m_Trans[3];
            float m_Rot[3];
            float m_Scale[3];

            std::unique_ptr<easyGL::VertexArray> m_VAO; 
            std::unique_ptr<easyGL::IndexBuffer> m_IndexBuffer;
            std::unique_ptr<easyGL::Shader> m_Shader;
            std::unique_ptr<easyGL::Texture> m_Texture1;
            std::unique_ptr<easyGL::Texture> m_Texture2;
            std::unique_ptr<easyGL::VertexBuffer> m_VB;

        public:
            TestModel();
            ~TestModel();

            void OnUpdate(float deltaTime) override;
            void OnRender() override;
            void OnImGuiRender() override;
    };
    
} // namespace tests