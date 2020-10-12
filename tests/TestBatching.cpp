#include "TestBatching.h"
#include "../Renderer.h"

#include "../vendor/imgui/imgui.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace tests {
    TestBatching::TestBatching()
    {
        float positions[] = {
             0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f,
             1.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
             1.5f,  0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
             0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,

            -1.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
            -0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
            -1.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f
        };
        unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0,

            4, 5, 6,
            6, 7, 4
        };

        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
        
        m_Shader = std::make_unique<Shader>("shaders/MVPTextureBatching.shader");
        m_VAO = std::make_unique<VertexArray>();
        m_VB = std::make_unique<VertexBuffer>(positions, 8 * 10 * sizeof(float));

        VertexBufferLayout layout;
        layout.Push(GL_FLOAT, 3);
        layout.Push(GL_FLOAT, 4);
        layout.Push(GL_FLOAT, 2);
        layout.Push(GL_FLOAT, 1);

        m_VAO->AddBuffer(*m_VB, layout);
        m_IndexBuffer = std::make_unique<IndexBuffer>(indices, 2 * 6);
        
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
    }

    TestBatching::~TestBatching()
    {
    }

    void TestBatching::OnUpdate(float deltaTime)
    {    
    }

    void TestBatching::OnRender()
    {   
        Renderer renderer;
        renderer.Clear();

        m_Texture1->Bind(0);
        m_Texture2->Bind(1);
        m_Shader->Bind();
        renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
    }

    void TestBatching::OnImGuiRender()
    {        
    }
}