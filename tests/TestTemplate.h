#pragma once

#include "Test.h"

namespace tests
{
    class TestTemplate : public Test
    {
        private:

        public:
            TestTemplate();
            ~TestTemplate();

            void OnUpdate(float deltaTime) override;
            void OnRender() override;
            void OnImGuiRender() override;
    };
    
} // namespace tests