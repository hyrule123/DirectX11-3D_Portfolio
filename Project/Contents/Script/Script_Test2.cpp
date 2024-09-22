#include "Contents/Script/Script_Test2.h"

#include <Engine/Manager/InputManager.h>
#include <Engine/Game/GameObject.h>
#include <Engine/Game/Component/Transform.h>

namespace ehw
{
	Script_Test2::Script_Test2()
		: Script(Script_Test2::concrete_class_name)
	{
	}

	Script_Test2::~Script_Test2()
	{
	}
	void Script_Test2::update()
	{
		if (InputManager::GetKeyDown(eKeyCode::I))
		{
			const auto& childs = gameObject()->transform()->get_childs();

			DEBUG_BREAK;
		}
	}
}
