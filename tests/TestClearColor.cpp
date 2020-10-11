#include "TestClearColor.h"
#include "../Renderer.h"
#include "../vendor/imgui/imgui.h"

namespace tests {
    TestClearColor::TestClearColor(float color[])
        :TestClearColor(color[0], color[1], color[2], color[3])
    {
    }

    TestClearColor::TestClearColor(float v0, float v1, float v2, float v3)
        :m_ClearColor {v0, v1, v2, v3}
    {
    }

    TestClearColor::~TestClearColor()
    {
    }

    void TestClearColor::OnUpdate(float deltaTime)
    {    
    }

    void TestClearColor::OnRender(){
        GLCall(glClearColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], m_ClearColor[3]));
        GLCall(glClear(GL_COLOR_BUFFER_BIT));
    }

    void TestClearColor::OnImGuiRender(){
        ImGui::ColorEdit4("Clear color", m_ClearColor);
    }
}