#include "TestClearColor.h"

#include "../vendor/imgui/imgui.h"

#include "../Renderer.h"

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
        easyGL::Renderer::Clear(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], m_ClearColor[3]);
    }

    void TestClearColor::OnImGuiRender(){
        ImGui::ColorEdit4("Clear color", m_ClearColor);
    }
}