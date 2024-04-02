#include "Scene_Title.h"

#include <Engine/Manager/ResourceManager.h>
#include <Engine/Manager/RenderManager.h>
#include <Engine/Manager/InputManager.h>
#include <Engine/Manager/CollisionManager.h>

#include <Engine/Game/GameObject.h>
#include <Engine/Game/Component/Transform/Com_Transform.h>
#include <Engine/Game/Component/Renderer/Com_Renderer_Mesh.h>
#include <Engine/Game/Component/Camera/Com_Camera.h>
#include <Engine/Game/Component/Renderer/Com_Renderer_Sprite.h>
#include <Engine/Game/Component/Script/GridScript.h>
#include <Engine/Game/Component/Collider/ICollider2D.h>
#include <Engine/Game/Component/Animator/Com_Animator2D.h>
#include <Engine/Game/Component/Light/Com_Light3D.h>
#include <Engine/Game/Component/Animator/Com_Animator3D.h>
#include <Engine/Game/Component/Renderer/Com_Renderer_ParticleSystem.h>
#include <Engine/Game/Component/Renderer/Com_Renderer_UIBase.h>



#include <Engine/Resource/Prefab.h>
#include <Engine/Resource/Model3D/Model3D.h>
#include <Engine/Resource/Texture.h>



#include "Contents/strKey_Script.h"
#include "Contents/Script/Script_Player.h"

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
			std::unique_ptr<GameObject> cameraObj = std::make_unique<GameObject>();
			cameraObj->SetName("MainCamera");

			Com_Transform* tr = cameraObj->Transform();
			tr->SetLocalPosition(float3(0.0f, 0.0f, -20.0f));

			Com_Camera* cameraComp = cameraObj->AddComponent<Com_Camera>();
			cameraComp->SetProjectionType(eProjectionType::Perspective);

			cameraObj->AddComponent(strKey::script::Script_CameraMove);

			RenderManager::SetMainCamera(cameraComp);


			AddGameObject(cameraObj, 0u);
		}

		{
			std::unique_ptr<GameObject> dirLight = std::make_unique<GameObject>();
			//dirLight->AddComponent<Com_Transform>();

			Com_Light3D* light3d = dirLight->AddComponent<Com_Light3D>();
			light3d->SetLightType(eLightType::Directional);
			light3d->SetDiffuse(float4(0.3f, 0.3f, 0.3f, 1.f));
			light3d->SetAmbient(float4(0.3f, 0.3f, 0.3f, 1.f));

			AddGameObject(dirLight, 0u);
		}

		{
			std::unique_ptr<GameObject> dirLight = std::make_unique<GameObject>();
			//dirLight->AddComponent<Com_Transform>();
			dirLight->SetName("Point1000");

			Com_Light3D* light3d = dirLight->AddComponent<Com_Light3D>();
			light3d->SetLightType(eLightType::Point);
			light3d->SetRadius(1000.f);
			light3d->SetDiffuse(float4(0.3f, 0.3f, 0.3f, 1.f));
			light3d->SetAmbient(float4(0.3f, 0.3f, 0.3f, 1.f));
		}

		{
			std::unique_ptr<GameObject> dirLight = std::make_unique<GameObject>();
			//dirLight->AddComponent<Com_Transform>();
			dirLight->SetName("Point500");

			Com_Light3D* light3d = dirLight->AddComponent<Com_Light3D>();
			light3d->SetLightType(eLightType::Point);
			light3d->SetRadius(500.f);

			light3d->SetDiffuse(float4(0.7f, 0.7f, 0.7f, 1.f));

			light3d->SetAmbient(float4(0.3f, 0.3f, 0.3f, 1.f));

			AddGameObject(dirLight, 0u);
		}

		{
			CollisionManager::SetCollisionMask(0, 0, true);
			std::unique_ptr<GameObject> colA = std::make_unique<GameObject>("Collider A");
			std::unique_ptr<GameObject> colB = std::make_unique<GameObject>("Collider B");

			colA->AddComponent(strKey::component::Com_Collider2D_AABB);
			colA->Transform()->SetLocalPosition(float3(-50.f, 0.f, 0.f));
			colB->AddComponent(strKey::component::Com_Collider2D_AABB);
			colB->Transform()->SetLocalPosition(float3(0.f, 50.f, 0.f));

			AddGameObject(colA, 0u);
			AddGameObject(colB, 0u);
		}

		{
			
			auto houseModel = ResourceManager<Model3D>::Load("Player_Default");
			auto house = houseModel->Instantiate();

			

			//const auto& childs = house->Transform()->GetChilds();

			for (size_t i = 0; i < 10; ++i)
			{
				house[i]->AddComponent(strKey::script::Script_Test);
			}
			house[11]->AddComponent(strKey::script::Script_Test2);

			int a = 3;

			AddGameObjects(house, 0);
		}


		{
			//std::unique_ptr<GameObject> player = NewGameObject(eLayer::Player);
			//player->AddComponent<Script_Player>();


			//std::unique_ptr<GameObject> modeling = meshdata->Instantiate(eLayer::Player);
		}
	}


}
