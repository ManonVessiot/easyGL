#include "TestSquareAnimatedColor.h"

#include "../vendor/imgui/imgui.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace tests {

    TestSquareAnimatedColor::TestSquareAnimatedColor()
        :m_R(0.0f), m_G(0.0f), m_B(0.0f), m_IncrementR(0.02f), m_IncrementG(0.01f), m_IncrementB(0.03f)
    {
        float positions[] = {
            -0.5f, -0.5f, 0.0f, 0.0f,
             0.5f, -0.5f, 1.0f, 0.0f,
             0.5f,  0.5f, 1.0f, 1.0f,
            -0.5f,  0.5f, 0.0f, 1.0f
        };
        unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0
        };

        m_Renderer.Blend();
        
        m_Shader = std::make_unique<easyGL::Shader>("shaders/MVPColor.shader");
        m_VAO = std::make_unique<easyGL::VertexArray>();
        m_VB = std::make_unique<easyGL::VertexBuffer>(positions, 4 * 4 * sizeof(float));

        easyGL::VertexBufferLayout layout;
        layout.Push(GL_FLOAT, 2);
        layout.Push(GL_FLOAT, 2);

        m_VAO->AddBuffer(*m_VB, layout);
        m_IndexBuffer = std::make_unique<easyGL::IndexBuffer>(indices, 6);
        
        m_Shader->Bind();

        m_Shader->SetUniform4f("u_Color", 0.2f, 0.3f, 0.8f, 1.0f);
    
        int height = 540;
        int width = 960;
        float miniSize = std::min(width, height);
        float borderLimit = 0.66f;
        float verticalLimit = (height / miniSize) * borderLimit;
        float horizontalLimit = (width / miniSize) * borderLimit;
        glm::mat4 proj = glm::ortho(-horizontalLimit, horizontalLimit, -verticalLimit, verticalLimit, -1.0f, 1.0f);
        m_Shader->SetUniformMat4f("u_MVP", proj); 
    }

    TestSquareAnimatedColor::~TestSquareAnimatedColor()
    {
        
    }

    void TestSquareAnimatedColor::OnUpdate(float deltaTime)
    {    
    }

    void TestSquareAnimatedColor::OnRender(){
        m_Renderer.Clear();

        m_Shader->Bind();        

        updateColor();

        m_Shader->SetUniform4f("u_Color", m_R, m_G, m_B, 1.0f);
        m_Renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
    }

    void TestSquareAnimatedColor::OnImGuiRender()
    {
    }

    void TestSquareAnimatedColor::updateColor(){    
        if (m_R > 1.0f){
            m_IncrementR *= -1;
        }
        else if (m_R < 0.0f){
            m_IncrementR *= -1;
        }

        if (m_G > 1.0f){
            m_IncrementG *= -1;
        }
        else if (m_G < 0.0f){
            m_IncrementG *= -1;
        }

        if (m_B > 1.0f){
            m_IncrementB *= -1;
        }
        else if (m_B < 0.0f){
            m_IncrementB *= -1;
        }
        m_R += m_IncrementR;
        m_G += m_IncrementG;
        m_B += m_IncrementB;
    }
}