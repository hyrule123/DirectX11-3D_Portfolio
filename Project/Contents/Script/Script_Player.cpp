#include "Script_Player.h"


#include <Engine/Resource/Model3D/Animation3D.h>
#include <Engine/Game/Component/Animator/Com_Animator3D.h>
#include <Engine/Game/GameObject.h>
#include <Engine/Manager/InputManager.h>
#include <Engine/Resource/Model3D/Model3D.h>
#include <Engine/Manager/ResourceManager.h>

#include <Engine/Game/Component/Transform.h>

#include "Contents/define_Contents.h"

namespace ehw
{
	Script_Player::Script_Player()
		: Script(Script_Player::concrete_name)
	{
	}
	Script_Player::~Script_Player()
	{
	}
	void Script_Player::Init()
	{
		gameObject()->SetName("Player");
		//GetOwner()->GetComponent<Transform>()->set_local_rotation(Vector3(0.f, -100.f, 750.f));
		Com_Animator3D* animator = gameObject()->GetComponent<Com_Animator3D>();
		animator->Play("Take 001");
		
		//animator->AddEvent("Evade", 0, std::bind(&Script_Player::TestCallback, this));
	}

	void Script_Player::Awake()
	{
		Com_Animator3D* animator = gameObject()->GetComponent<Com_Animator3D>();
		if (animator)
		{
			//5animator->AddEvent()
		}
	}

	void Script_Player::Update()
	{
		if (InputManager::GetKeyDown(eKeyCode::P))
		{
			Com_Animator3D* animator = gameObject()->GetComponent<Com_Animator3D>();
			if (animator)
			{
				animator->PlayNext();
			}
		}

		if (InputManager::GetKeyDown(eKeyCode::E))
		{
		}
	}
	void Script_Player::TestCallback()
	{
		OutputDebugStringA("!!!!Called!!!\n");
	}
}

