#pragma once

#include "Test.h"

namespace tests
{
    class TestClearColor : public Test
    {
        private:
            float m_ClearColor[4];

        public:
            TestClearColor(float color[]);
            TestClearColor(float v0 = 0.2f, float v1 = 0.3f, float v2 = 0.8f, float v3 = 1.0f);
            ~TestClearColor();

            void OnUpdate(float deltaTime) override;
            void OnRender() override;
            void OnImGuiRender() override;
    };
    
} // namespace tests