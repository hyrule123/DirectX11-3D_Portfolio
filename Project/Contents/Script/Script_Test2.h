#pragma once
#include <Engine/Game/Component/Script/Script.h>

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


