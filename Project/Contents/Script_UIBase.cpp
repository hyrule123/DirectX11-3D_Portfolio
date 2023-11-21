#include "Script_UIBase.h"
#include "Script_UIBase.h"
#include "PCH_Contents.h"
#include "Script_UIBase.h"

#include <EngineBase/Engine/GameObject.h>
#include <EngineBase/Engine/Com_Renderer_UIBase.h>
#include <EngineBase/Engine/ResourceMgr.h>
#include <EngineBase/Engine/define_Component.h>

namespace ehw
{
	Script_UIBase::Script_UIBase(eUIType _type)
		: mUIMode(_type)
		, mUIComponent()
	{
		CreateUI();
	}

	Script_UIBase::Script_UIBase()
		: mUIMode(eUIType::Basic)
		, mUIComponent()
	{
		CreateUI();
	}

	Script_UIBase::~Script_UIBase()
	{
	}

	void Script_UIBase::Init()
	{
		GetOwner()->AddComponent(mUIComponent);
	}

	void Script_UIBase::CreateUI()
	{



		switch (mUIMode)
		{
		case eUIType::Basic:
			mUIComponent = 
				static_cast<Com_Renderer_UIBase*>(ComMgr::GetNewCom(strKey::com::Com_Renderer_UIBase));
			break;

		case eUIType::Gauge:
		{
			mUIComponent =
				static_cast<Com_Renderer_UIBase*>(ComMgr::GetNewCom(strKey::com::Com_Renderer_UIBase));

			//에디터를 통해 만든 Gauge 머티리얼로 설정
			SetCustomMaterial(ResourceMgr::Load<Material>("UI/UIGauge.json"));
			break;
		}

		case eUIType::Button:
			mUIComponent =
				static_cast<Com_Renderer_UIBase*>(ComMgr::GetNewCom(strKey::com::Com_Renderer_UIBase));

			break;

		default:
			break;
		}
	}
	void Script_UIBase::SetCustomMaterial(std::shared_ptr<Material> _material)
	{
		MH_ASSERT(mUIComponent);
		mUIComponent->SetMaterial(_material, 0u);
		mUIComponent->SetMaterialMode(0u, eMaterialMode::Dynamic);
	}

	void Script_UIBase::SetTexture(define::eTextureSlot _slot, std::shared_ptr<Texture> _tex)
	{
		MH_ASSERT(mUIComponent);
		mUIComponent->GetCurrentMaterial(0u)->SetTexture(_slot, _tex);
	}
}

