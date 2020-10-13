#include "TestModel.h"

#include "../vendor/imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>

namespace tests {

    TestModel::TestModel()
        :m_InitPose{0.0f, 0.0f, 0.0f}, m_InitRot{0.0f, 0.0f, 0.0f}
    {
        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
        
        m_Shader = std::make_unique<Shader>("shaders/Model.shader");
        m_VAO = std::make_unique<VertexArray>();
        m_VB = std::make_unique<VertexBuffer>(nullptr, sizeof(MyModel::Vertex) * 300, GL_DYNAMIC_DRAW); // allocate memory for 300 vertex

        VertexBufferLayout layout;
        layout.Push(GL_FLOAT, 3);
        layout.Push(GL_FLOAT, 3);
        layout.Push(GL_FLOAT, 2);
        layout.Push(GL_FLOAT, 1);

        m_VAO->AddBuffer(*m_VB, layout);

        m_IndexBuffer = std::make_unique<IndexBuffer>(nullptr, 100 * 3, GL_DYNAMIC_DRAW); // allocate memory for 100 triangles
        
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

        m_Texture1 = std::make_unique<Texture>("textures/zelda.png");
        m_Texture2 = std::make_unique<Texture>("textures/white.png");


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
        m_Model.SetTranslation(m_InitPose[0], m_InitPose[1], m_InitPose[2]);
        m_Model.SetRotationEuler(m_InitRot[0], m_InitRot[1], m_InitRot[2]);
        
        MyModel::Vertex* vertices = m_Model.GetVertexData();

        m_VB->Bind();
        m_VB->WriteData(0, m_Model.GetVertexCount() * sizeof(MyModel::Vertex) * sizeof(float), vertices); // write vertices in VertexBuffer
        
        unsigned int * indices = m_Model.GetIndicesData();

        m_IndexBuffer->Bind();
        m_IndexBuffer->WriteData(0, m_Model.GetTriangleCount() * 3, indices); // write indices in IndexBuffer
    }

    void TestModel::OnRender()
    {   
        Renderer renderer;
        renderer.Clear();

        m_Texture1->Bind(0);
        m_Texture2->Bind(1);
        m_Shader->Bind();
        renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
    }

    void TestModel::OnImGuiRender()
    {
        ImGui::DragFloat3("Init Position", m_InitPose, 0.1f);
        ImGui::DragFloat3("Init Rotation", m_InitRot, 0.1f);
    }
}