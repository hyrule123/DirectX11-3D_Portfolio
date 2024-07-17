#pragma once
#include <Engine/Scene/Component/Script/Script.h>

namespace ehw
{
    class Script_Player :
        public Script
    {
    public:
        Script_Player() {};
        virtual ~Script_Player() {};

        virtual void Init() override;
        virtual void Awake() override;
        virtual void Update() override;

    private:
        void TestCallback();
    };

}

