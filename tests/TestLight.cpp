#include "TestLight.h"

#include "../vendor/imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>

namespace tests {

    TestLight::TestLight()
        :m_Trans{0.0f, 0.0f, 0.0f},
         m_Rot{0.0f, 0.0f, 0.0f},
         m_Scale{1.0f, 1.0f, 1.0f}
    {
        easyGL::Renderer::Blend();
        
        m_Shader = std::make_unique<easyGL::Shader>("shaders/Light.shader");
        m_VAO = std::make_unique<easyGL::VertexArray>();
        m_VB = std::make_unique<easyGL::VertexBuffer>(nullptr, sizeof(easyGL::MyModel::Vertex) * 300, GL_DYNAMIC_DRAW); // allocate memory for 300 vertex

        easyGL::VertexBufferLayout layout;
        layout.Push(GL_FLOAT, 3);
        layout.Push(GL_FLOAT, 3);
        layout.Push(GL_FLOAT, 2);
        layout.Push(GL_FLOAT, 1);

        m_VAO->AddBuffer(*m_VB, layout);

        m_IndexBuffer = std::make_unique<easyGL::IndexBuffer>(nullptr, 100 * 3, GL_DYNAMIC_DRAW); // allocate memory for 100 triangles
        
        m_Shader->Bind();
        m_Shader->SetUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);
        
        // MVP matrix        
        int height = 540;
        int width = 960;
        glm::mat4 proj = glm::perspective(
                glm::radians(60.0f),
                (float)width / height,
                0.1f,
                100.0f
            );
        
        glm::mat4 view = glm::lookAt(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        m_Shader->SetUniformMat4f("u_MVP", proj * view);
        
        m_Model.AddVertex(glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec3(-1.0f, -1.0f,  1.0f), glm::vec2(0.0f, 0.0f), 1.0f);
        m_Model.AddVertex(glm::vec3( 0.5f, -0.5f,  0.5f), glm::vec3( 1.0f, -1.0f,  1.0f), glm::vec2(1.0f, 0.0f), 1.0f);
        m_Model.AddVertex(glm::vec3( 0.5f,  0.5f,  0.5f), glm::vec3( 1.0f,  1.0f,  1.0f), glm::vec2(1.0f, 1.0f), 1.0f);
        m_Model.AddVertex(glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec3(-1.0f,  1.0f,  1.0f), glm::vec2(0.0f, 1.0f), 1.0f);

        m_Model.AddVertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec2(0.0f, 0.0f), 1.0f);
        m_Model.AddVertex(glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3(-1.0f,  1.0f, -1.0f), glm::vec2(1.0f, 0.0f), 1.0f);
        m_Model.AddVertex(glm::vec3( 0.5f,  0.5f, -0.5f), glm::vec3( 1.0f,  1.0f, -1.0f), glm::vec2(1.0f, 1.0f), 1.0f);
        m_Model.AddVertex(glm::vec3( 0.5f, -0.5f, -0.5f), glm::vec3( 1.0f, -1.0f, -1.0f), glm::vec2(0.0f, 1.0f), 1.0f);

        // down
        m_Model.AddTriangle(0, 4, 7);
        m_Model.AddTriangle(7, 1, 0);

        // right
        m_Model.AddTriangle(1, 7, 6);
        m_Model.AddTriangle(6, 2, 1);

        // back
        m_Model.AddTriangle(4, 5, 6);
        m_Model.AddTriangle(6, 7, 4);

        // left
        m_Model.AddTriangle(0, 3, 5);
        m_Model.AddTriangle(5, 4, 0);

        // front
        m_Model.AddTriangle(0, 1, 2);
        m_Model.AddTriangle(2, 3, 0);

        // up
        m_Model.AddTriangle(3, 2, 6);
        m_Model.AddTriangle(6, 5, 3);


        // lights
        m_Shader->SetUniform2f("_ScreenParams", width, height);
        m_Shader->SetUniform3f("_WorldSpaceCameraPos",  1.0f, 1.0f, 1.0f);
        m_Shader->SetUniform4f("_AmbientLight",         0.2f, 0.2f, 0.2f, 1.0f);
        m_Shader->SetUniform4f("_LightColor0",          1.0f, 0.0f, 0.0f, 1.0f);
        m_Shader->SetUniform4f("_WorldSpaceLightPos0", -1.0f, 1.0f, 1.0f, 1.0f);        
    }

    TestLight::~TestLight()
    {
    }

    void TestLight::OnUpdate(float deltaTime)
    {
        m_Model.SetTranslation(m_Trans[0], m_Trans[1], m_Trans[2]);
        m_Model.SetRotationEuler(m_Rot[0], m_Rot[1], m_Rot[2]);
        m_Model.SetScale(m_Scale[0], m_Scale[1], m_Scale[2]);
        
        easyGL::MyModel::Vertex* vertices = m_Model.GetVertexData();

        m_VB->Bind();
        m_VB->WriteData(0, m_Model.GetVertexCount() * sizeof(easyGL::MyModel::Vertex) * sizeof(float), vertices); // write vertices in VertexBuffer
        
        unsigned int * indices = m_Model.GetIndicesData();

        m_IndexBuffer->Bind();
        m_IndexBuffer->WriteData(0, m_Model.GetTriangleCount() * 3, indices); // write indices in IndexBuffer
    }

    void TestLight::OnRender()
    {
        easyGL::Renderer::Clear();

        m_Shader->Bind();
        m_Shader->SetUniform1f("_Time", difftime( time(0), m_TimeStart));
        easyGL::Renderer::Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
    }

    void TestLight::OnImGuiRender()
    {
        ImGui::DragFloat3("Translation", m_Trans, 0.1f);
        ImGui::DragFloat3("Rotation", m_Rot, 0.1f);
        ImGui::DragFloat3("Scale", m_Scale, 0.1f);
    }
}