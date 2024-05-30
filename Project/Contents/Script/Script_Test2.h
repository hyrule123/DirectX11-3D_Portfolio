#pragma once
#include <Engine/Scene/Component/Script/iScript.h>

namespace ehw
{
    class Script_Test2 :
        public iScript
    {
    public:
        Script_Test2();
        virtual ~Script_Test2();

        virtual void Update() override;
    };
}


