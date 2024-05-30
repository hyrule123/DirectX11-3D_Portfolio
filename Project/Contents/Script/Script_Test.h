#pragma once
#include <Engine/Scene/Component/Script/iScript.h>

namespace ehw
{
    class Script_Test :
        public iScript
    {
    public:
        Script_Test();
        virtual ~Script_Test();

        virtual void Update() override;
    };
}


