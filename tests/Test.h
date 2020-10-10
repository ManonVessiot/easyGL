#pragma once

namespace tests
{
    class Test
    {
        public:
            Test(){}
            virtual ~Test(){}

            virtual void OnUpdate(float deltaTime){ }
            virtual void OnRender(){ }
    };
} // namespace tests
