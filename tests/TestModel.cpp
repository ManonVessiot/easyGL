#include "TestModel.h"

#include "../vendor/imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>

namespace tests {

    TestModel::TestModel()
        :m_Trans{0.0f, 0.0f, 0.0f},
         m_Rot{0.0f, 0.0f, 0.0f},
         m_Scale{1.0f, 1.0f, 1.0f}
    {
        easyGL::Renderer::Blend();
        
        m_Shader = std::make_unique<easyGL::Shader>("shaders/Model.shader");
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
        int samplers[2] = {0, 1};
        m_Shader->SetUniform1iv("u_Textures", 2, samplers);
        
        // MVP matrix        
        int height = 540;
        int width = 960;
        float miniSize = std::min(width, height);
        float borderLimit = 1.0f;
        float verticalLimit = (height / miniSize) * borderLimit;
        float horizontalLimit = (width / miniSize) * borderLimit;
        glm::mat4 proj = glm::ortho(-horizontalLimit, horizontalLimit, -verticalLimit, verticalLimit, -1.0f, 1.0f);
        m_Shader->SetUniformMat4f("u_MVP", proj);

        m_Texture1 = std::make_unique<easyGL::Texture>("textures/zelda.png");
        m_Texture2 = std::make_unique<easyGL::Texture>("textures/white.png");


        m_Model.AddVertex(glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f), 0.0f);
        m_Model.AddVertex(glm::vec3( 0.5f, -0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f), 0.0f);
        m_Model.AddVertex(glm::vec3( 0.5f,  0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f), 0.0f);
        m_Model.AddVertex(glm::vec3(-0.5f,  0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 1.0f), 0.0f);

        m_Model.AddTriangle(0, 1, 2);
        m_Model.AddTriangle(2, 3, 0);
    }

    TestModel::~TestModel()
    {
    }

    void TestModel::OnUpdate(float deltaTime)
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

    void TestModel::OnRender()
    {
        easyGL::Renderer::Clear();

        m_Texture1->Bind(0);
        m_Texture2->Bind(1);
        m_Shader->Bind();
        easyGL::Renderer::Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
    }

    void TestModel::OnImGuiRender()
    {
        ImGui::DragFloat3("Global translation", m_Trans, 0.1f);
        ImGui::DragFloat3("Global rotation", m_Rot, 0.1f);
        ImGui::DragFloat3("Global scale", m_Scale, 0.1f);
    }
}