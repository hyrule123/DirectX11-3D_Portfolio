#pragma once
#include <Engine/Game/Component/Script/Script.h>

namespace ehw
{
    class Script_Test :
        public Script
    {
        CLASS_NAME(Script_Test);
        
    public:
        Script_Test();
        virtual ~Script_Test();

        virtual void Update() override;
    };
    
}


