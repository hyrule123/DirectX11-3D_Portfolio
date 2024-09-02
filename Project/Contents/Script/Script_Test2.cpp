#include "Contents/Script/Script_Test2.h"

#include <Engine/Manager/InputManager.h>
#include <Engine/Game/GameObject.h>
#include <Engine/Game/Component/Com_Transform.h>

namespace ehw
{
	Script_Test2::Script_Test2()
		: Script(INSTANCE_ABLE(Script_Test2))
	{
	}

	Script_Test2::~Script_Test2()
	{
	}
	void Script_Test2::Update()
	{
		if (InputManager::GetKeyDown(eKeyCode::I))
		{
			const auto& childs = gameObject()->Transform()->GetChilds();

			DEBUG_BREAK;
		}
	}
}
