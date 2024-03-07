#include "Scene_Title.h"

#include <Base/Engine/Manager/ResourceManager.h>
#include <Base/Engine/Manager/RenderManager.h>
#include <Base/Engine/Game/Component/Transform/Com_Transform.h>
#include <Base/Engine/Game/Component/Renderer/Com_Renderer_Mesh.h>
#include <Base/Engine/Resource/Texture.h>
#include <Base/Engine/Game/Component/Camera/Com_Camera.h>
#include <Base/Engine/Game/Component/Renderer/Com_Renderer_Sprite.h>
#include <Base/Engine/Game/Component/Script/GridScript.h>
#include <Base/Engine/Manager/InputManager.h>
#include <Base/Engine/Game/Component/Collider/ICollider2D.h>
#include <Base/Engine/Manager/CollisionManager.h>
#include <Base/Engine/Game/Component/Animator/Com_Animator2D.h>
#include <Base/Engine/Game/Component/Light/Com_Light3D.h>
#include <Base/Engine/Game/Component/Animator/Com_Animator3D.h>
#include <Base/Engine/Game/Component/Renderer/Com_Renderer_ParticleSystem.h>
#include <Base/Engine/Resource/Prefab.h>
#include <Base/Engine/Resource/Model3D/Model3D.h>
#include <Base/Engine/Game/Component/Renderer/Com_Renderer_UIBase.h>


#include "../strKey_Script.h"
#include "../Script/Script_Player.h"

#include <iostream>

namespace ehw
{
	Scene_Title::Scene_Title()
	{
	}
	Scene_Title::~Scene_Title()
	{
	}
	void Scene_Title::OnEnter()
	{
		{
			// Main Com_Camera Game Object
			const std::shared_ptr<GameObject>& cameraObj = NewGameObject(eLayer::Com_Camera);
			cameraObj->SetName("MainCamera");

			const std::shared_ptr<Com_Transform>& tr = cameraObj->AddComponent<Com_Transform>();
			tr->SetLocalPosition(float3(0.0f, 0.0f, -20.0f));

			const std::shared_ptr<Com_Camera>& cameraComp = cameraObj->AddComponent<Com_Camera>();
			cameraComp->SetProjectionType(eProjectionType::Perspective);

			cameraObj->AddComponent(strKey::script::Script_CameraMove);


			RenderManager::SetMainCamera(cameraComp);
		}

		{
			const std::shared_ptr<GameObject>& dirLight = NewGameObject(eLayer::Player);
			dirLight->AddComponent<Com_Transform>();

			const std::shared_ptr<Com_Light3D>& light3d = dirLight->AddComponent<Com_Light3D>();
			light3d->SetLightType(eLightType::Directional);
			light3d->SetDiffuse(float4(0.3f, 0.3f, 0.3f, 1.f));
			light3d->SetAmbient(float4(0.3f, 0.3f, 0.3f, 1.f));
		}

		{
			const std::shared_ptr<GameObject>& dirLight = NewGameObject(eLayer::Player);
			dirLight->AddComponent<Com_Transform>();
			dirLight->SetName("Point1000");

			const std::shared_ptr<Com_Light3D>& light3d = dirLight->AddComponent<Com_Light3D>();
			light3d->SetLightType(eLightType::Point);
			light3d->SetRadius(1000.f);
			light3d->SetDiffuse(float4(0.3f, 0.3f, 0.3f, 1.f));
			light3d->SetAmbient(float4(0.3f, 0.3f, 0.3f, 1.f));
		}

		{
			const std::shared_ptr<GameObject>& dirLight = NewGameObject(eLayer::Player);
			dirLight->AddComponent<Com_Transform>();
			dirLight->SetName("Point500");

			const std::shared_ptr<Com_Light3D>& light3d = dirLight->AddComponent<Com_Light3D>();
			light3d->SetLightType(eLightType::Point);
			light3d->SetRadius(500.f);

			light3d->SetDiffuse(float4(0.7f, 0.7f, 0.7f, 1.f));

			light3d->SetAmbient(float4(0.3f, 0.3f, 0.3f, 1.f));
		}

		{
			const auto& house = NewGameObject(eLayer::Player);
			ASSERT(house, "house 인스턴스 생성 실패");
			house->SetName("HOUSE");
			
			const auto& houseModel = ResourceManager<Model3D>::Load("House");
			eResult result = houseModel->Instantiate(house);
			ASSERT(eResultSuccess(result), "생성 실패");
		}


		{
			//const std::shared_ptr<GameObject>& player = NewGameObject(eLayer::Player);
			//player->AddComponent<Script_Player>();


			//const std::shared_ptr<GameObject>& modeling = meshdata->Instantiate(eLayer::Player);
		}
	}


}
