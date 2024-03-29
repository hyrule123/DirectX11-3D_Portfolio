#include "Contents/Script/Script_Test2.h"

#include <Engine/Manager/InputManager.h>
#include <Engine/Game/GameObject.h>

namespace ehw
{
	Script_Test2::Script_Test2()
	{
	}

	Script_Test2::~Script_Test2()
	{
	}
	void Script_Test2::Update()
	{
		if (InputManager::GetKeyDown(eKeyCode::I))
		{
			const auto& childs = GetOwner()->Transform()->GetChilds();

			DEBUG_BREAK;
		}
	}
}
