#include "Contents/Script/Script_Test.h"

#include <Engine/Manager/InputManager.h>

#include <Engine/Game/GameObject.h>


namespace ehw
{
	Script_Test::Script_Test()
		: Script(Script_Test::concrete_name)
	{
	}

	Script_Test::~Script_Test()
	{
	}
	void Script_Test::Update()
	{
		if (InputManager::GetKeyDown(eKeyCode::X))
		{
			gameObject()->Destroy();
		}
	}
}

