#include "Script_Player.h"


#include <Base/Engine/Resource/Model3D/Animation3D.h>
#include <Base/Engine/Game/Component/Animator/Com_Animator3D.h>
#include <Base/Engine/Game/GameObject.h>
#include <Base/Engine/Manager/InputManager.h>
#include <Base/Engine/Resource/Model3D/Model3D.h>
#include <Base/Engine/Manager/ResourceManager.h>


#include <Base/Engine/Game/Component/Transform/Com_Transform.h>

namespace ehw
{
	void Script_Player::Init()
	{
		std::shared_ptr<Model3D> meshdata = ResourceManager<Model3D>::Load("RealAniman");
		if (nullptr == meshdata || eResultFail(meshdata->Instantiate(GetOwner()->shared_from_this_T<GameObject>())))
		{
			ERROR_MESSAGE_W(L"메쉬 데이터 로드 실패");
		}

		GetOwner()->SetName("Player");
		GetOwner()->GetComponent<Com_Transform>()->SetLocalRotation(Vector3(0.f, -100.f, 750.f));
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

