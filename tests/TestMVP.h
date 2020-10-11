#pragma once

#include "Test.h"

#include "../Renderer.h"
#include "../VertexArray.h"
#include "../VertexBufferLayout.h"
#include "../Texture.h"

#include <glm/glm.hpp>

#include <memory>

namespace tests
{
    class TestMVP : public Test
    {
        private:
            glm::vec3 m_CameraTranslation;
            glm::vec3 m_model1Translation;
            glm::vec3 m_model2Translation;
            
            glm::vec3 m_CameraRotation;
            glm::vec3 m_model1Rotation;
            glm::vec3 m_model2Rotation;




            glm::mat4 m_Proj;

            float m_R;
            float m_G;
            float m_B;
            float m_IncrementR;
            float m_IncrementG;
            float m_IncrementB;

            std::unique_ptr<VertexArray> m_VAO; 
            std::unique_ptr<IndexBuffer> m_IndexBuffer;
            std::unique_ptr<Shader> m_Shader;
            std::unique_ptr<Texture> m_Texture;
            std::unique_ptr<VertexBuffer> m_VB;
            
        public:
            TestMVP();
            ~TestMVP();

            void OnUpdate(float deltaTime) override;
            void OnRender() override;
            void OnImGuiRender() override;

            void updateColor();
    };
    
} // namespace tests