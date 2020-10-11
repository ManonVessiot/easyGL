#pragma once

#include "Test.h"

#include "../Renderer.h"
#include "../VertexArray.h"
#include "../VertexBufferLayout.h"
#include "../Texture.h"

#include <memory>

namespace tests
{
    class TestCube : public Test
    {
        private:
            glm::vec3 m_modelTranslation;
            
            glm::vec3 m_modelRotation;

            glm::mat4 m_Proj;

            std::unique_ptr<VertexArray> m_VAO; 
            std::unique_ptr<IndexBuffer> m_IndexBuffer;
            std::unique_ptr<Shader> m_Shader;
            std::unique_ptr<VertexBuffer> m_VB;
            
        public:
            TestCube();
            ~TestCube();

            void OnUpdate(float deltaTime) override;
            void OnRender() override;
            void OnImGuiRender() override;
    };
    
} // namespace tests