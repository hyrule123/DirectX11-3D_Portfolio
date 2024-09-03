#pragma once
#include <Engine/Game/Component/Script/Script.h>

namespace ehw
{
    class Script_Test :
        public Script
    {
        REGISTER_CLASS_INFO(Script_Test);
        SET_INSTANCE_ABLE(Script_Test);
    public:
        Script_Test();
        virtual ~Script_Test();

        virtual void Update() override;
    };
    
}


