#include "TestTriangle.h"

#include "../vendor/imgui/imgui.h"

#include "../Renderer.h"

namespace tests {

    TestTriangle::TestTriangle()
        :m_Color {1.0f, 1.0f, 1.0f, 1.0f}
    {
        float positions[] = {
            -0.5f, -0.5f,
             0.0f,  0.5f,
             0.5f, -0.5f
        };
        unsigned int indices[] = {
            0, 1, 2
        };

        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
        
        m_Shader = std::make_unique<Shader>("shaders/BasicColor.shader");
        m_VAO = std::make_unique<VertexArray>();
        m_VB = std::make_unique<VertexBuffer>(positions, 3 * 2 * sizeof(float));

        VertexBufferLayout layout;
        layout.Push(GL_FLOAT, 2);

        m_VAO->AddBuffer(*m_VB, layout);
        m_IndexBuffer = std::make_unique<IndexBuffer>(indices, 3);
        
        m_Shader->Bind();
        m_Shader->SetUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);
    }

    TestTriangle::~TestTriangle()
    {
    }

    void TestTriangle::OnUpdate(float deltaTime)
    {    
    }

    void TestTriangle::OnRender()
    {   
        Renderer renderer;
        renderer.Clear();

        m_Shader->Bind();
        m_Shader->SetUniform4f("u_Color", m_Color[0], m_Color[1], m_Color[2], m_Color[3]);

        renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
    }

    void TestTriangle::OnImGuiRender()
    {
        ImGui::ColorEdit4("Color", m_Color);
    }
}