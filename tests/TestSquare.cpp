#include "TestSquare.h"

#include "../vendor/imgui/imgui.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace tests {

    TestSquare::TestSquare()
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

        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
        
        m_Shader = std::make_unique<Shader>("shaders/MVPColor.shader");
        m_VAO = std::make_unique<VertexArray>();
        m_VB = std::make_unique<VertexBuffer>(positions, 4 * 4 * sizeof(float));

        VertexBufferLayout layout;
        layout.Push(GL_FLOAT, 2);
        layout.Push(GL_FLOAT, 2);

        m_VAO->AddBuffer(*m_VB, layout);
        m_IndexBuffer = std::make_unique<IndexBuffer>(indices, 6);
        
        m_Shader->Bind();

        m_Shader->SetUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);
    
        int height = 540;
        int width = 960;
        float miniSize = std::min(width, height);
        float borderLimit = 0.66f;
        float verticalLimit = (height / miniSize) * borderLimit;
        float horizontalLimit = (width / miniSize) * borderLimit;
        glm::mat4 proj = glm::ortho(-horizontalLimit, horizontalLimit, -verticalLimit, verticalLimit, -1.0f, 1.0f);
        m_Shader->SetUniformMat4f("u_MVP", proj); 
    }

    TestSquare::~TestSquare()
    {
        
    }

    void TestSquare::OnUpdate(float deltaTime)
    {    
    }

    void TestSquare::OnRender(){
        Renderer renderer;
        renderer.Clear();

        m_Shader->Bind();

        renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
    }

    void TestSquare::OnImGuiRender()
    {
    }
}