#pragma once
#include <Engine/Scene/Component/Script/Script.h>

namespace ehw
{
    class Script_Test2 :
        public Script
    {
    public:
        Script_Test2();
        virtual ~Script_Test2();

        virtual void Update() override;
    };
}


