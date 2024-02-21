#include "Script_Player.h"


#include <Engine/Resource/Model3D/Animation3D.h>
#include <Engine/Game/Component/Animator/Com_Animator3D.h>
#include <Engine/Game/GameObject.h>
#include <Engine/Manager/InputManager.h>
#include <Engine/Resource/Model3D/Model3D.h>
#include <Engine/Manager/ResourceManager.h>


#include <Engine/Game/Component/Transform/Com_Transform.h>

namespace ehw
{
	void Script_Player::Init()
	{
		std::shared_ptr<Model3D> meshdata = ResourceManager<Model3D>::Load("RealAniman");
		if (nullptr == meshdata || eResultFail(meshdata->Instantiate(GetOwner())))
		{
			ERROR_MESSAGE_W(L"메쉬 데이터 로드 실패");
		}

		GetOwner()->SetName("Player");
		GetOwner()->GetComponent<Com_Transform>()->SetRelativePosY(-100.f);
		GetOwner()->GetComponent<Com_Transform>()->SetRelativePosZ(750.f);
		const std::shared_ptr<Com_Animator3D>& animator = GetOwner()->GetComponent<Com_Animator3D>();
		animator->Play("Noesis Frames");
		
		//animator->AddEvent("Evade", 0, std::bind(&Script_Player::TestCallback, this));
	}

	void Script_Player::Awake()
	{
		const std::shared_ptr<Com_Animator3D> animator = GetOwner()->GetComponent<Com_Animator3D>();
		if (animator)
		{
			//5animator->AddEvent()
		}
	}

	void Script_Player::Update()
	{
		if (InputManager::GetKeyDown(eKeyCode::P))
		{
			const std::shared_ptr<Com_Animator3D>& animator = GetOwner()->GetComponent<Com_Animator3D>();
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

