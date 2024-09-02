#include "Scene_Title.h"

#include <Engine/Manager/ResourceManager.h>
#include <Engine/Manager/RenderManager.h>
#include <Engine/Manager/InputManager.h>

#include <Engine/Game/GameObject.h>
#include <Engine/Game/Collision/CollisionSystem.h>
#include <Engine/Game/Collision/Collision3D.h>

#include <Engine/Game/Component/Com_Transform.h>
#include <Engine/Game/Component/Renderer/Com_Renderer_Mesh.h>
#include <Engine/Game/Component/Camera/Com_Camera.h>
#include <Engine/Game/Component/Renderer/Com_Renderer_Sprite.h>
#include <Engine/Game/Component/Script/GridScript.h>
#include <Engine/Game/Component/Collider/Collider2D.h>
#include <Engine/Game/Component/Animator/Com_Animator2D.h>
#include <Engine/Game/Component/Light/Com_Light3D.h>
#include <Engine/Game/Component/Animator/Com_Animator3D.h>
#include <Engine/Game/Component/Renderer/Com_Renderer_ParticleSystem.h>
#include <Engine/Game/Component/Renderer/Com_Renderer_UIBase.h>
#include <Engine/Game/Component/Collider/Com_Collider3D_Cube.h>
#include <Engine/Game/Component/Rigidbody/Com_Rigidbody_Dynamic.h>
#include <Engine/Game/Component/Rigidbody/Com_Rigidbody_Static.h>


#include <Engine/Resource/Prefab.h>
#include <Engine/Resource/Model3D/Model3D.h>
#include <Engine/Resource/Texture.h>

#include "Contents/Script/Script_Player.h"
#include "Contents/Script/Script_CameraMove.h"

#include <iostream>

namespace ehw
{
	Scene_Title::Scene_Title()
		: Scene(
			INSTANCE_ABLE(Scene_Title)
		)
	{
	}
	Scene_Title::~Scene_Title()
	{
	}
	void Scene_Title::Init()
	{
	}
	void Scene_Title::OnEnter()
	{
		{
			// Main Com_Camera Game Object
			std::unique_ptr<GameObject> cameraObj = std::make_unique<GameObject>();
			cameraObj->SetName("MainCamera");

			Com_Transform* tr = cameraObj->Transform();
			tr->SetLocalPosition(float3(0.0f, 0.0f, -500.0f));

			Com_Camera* cameraComp = cameraObj->AddComponent<Com_Camera>();
			cameraComp->SetProjectionType(eProjectionType::Perspective);

			cameraObj->AddComponent("Script_CameraMove");

			RenderManager::GetInst().sceneRenderAgent().SetMainCamera(cameraComp);


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
			GetCollisionSystem()->SetCollisionMask(0, 0, true);
			GetCollisionSystem()->SetCollisionMask(0, 1, true);
			std::unique_ptr<GameObject> colA = std::make_unique<GameObject>("Collider A");
			std::unique_ptr<GameObject> colB = std::make_unique<GameObject>("Collider B");

			colA->AddComponent(strKey::component::Com_Collider2D_AABB);
			colA->Transform()->SetLocalPosition(float3(-50.f, 0.f, 0.f));
			colB->AddComponent(strKey::component::Com_Collider2D_AABB);
			colB->Transform()->SetLocalPosition(float3(0.f, 50.f, 0.f));

			AddGameObject(colA, 0u);
			AddGameObject(colB, 1u);
		}

		{
			GetCollisionSystem()->GetCollision3D()->EnableGravity(true, float3(0.f, -9.8f, 0.f));
			physx::PxMaterial* material = GetCollisionSystem()->GetCollision3D()->GetDefaultPxMaterial();
			//material->setStaticFriction(0.f);
			//material->setDynamicFriction(0.5f);
			material->setRestitution(0.f);

			//material->setDamping(1.f);
			//material->setFlag(physx::PxMaterialFlag::eDISABLE_FRICTION, true);

			//material->setRestitution(0.f);
			GetCollisionSystem()->SetCollisionMask(0u, 0u, true);
			GetCollisionSystem()->SetCollisionMask(0u, 1u, true);

			std::unique_ptr<GameObject> col3dA = std::make_unique<GameObject>("Collider 3D-A");
			std::unique_ptr<GameObject> col3dB = std::make_unique<GameObject>("Collider 3D-B");

			col3dA->Transform()->SetLocalPosition(float3(0.f, -100.f, 0.f));
			col3dA->Transform()->SetLocalScale(float3(500.f, 100.f, 500.f));

			col3dB->Transform()->SetLocalPosition(float3(0.f, 100.f, 0.f));
			col3dB->Transform()->SetLocalScale(float3(100.f, 100.f, 100.f));

			Com_Collider3D_Cube* colA = col3dA->AddComponent<Com_Collider3D_Cube>();
			Com_Collider3D_Cube* colB = col3dB->AddComponent<Com_Collider3D_Cube>();

			Com_Rigidbody_Dynamic* rigidDynamic = col3dB->AddComponent<Com_Rigidbody_Dynamic>();

			//rigidDynamic->SetDensity(10.f);
			rigidDynamic->SetMass(50000.f);
			rigidDynamic->EnableGravity(true);
			//rigidDynamic->SetRigidDynamicLockFlag(physx::PxRigidDynamicLockFlag::eLOCK_ANGULAR_X, true);
			//rigidDynamic->SetRigidDynamicLockFlag(physx::PxRigidDynamicLockFlag::eLOCK_LINEAR_X, true);
			//rigidDynamic->SetRigidDynamicLockFlag(physx::PxRigidDynamicLockFlag::eLOCK_LINEAR_Z, true);
			//rigidDynamic->SetRigidDynamicLockFlag(physx::PxRigidDynamicLockFlag::eLOCK_ANGULAR_Z, true);


			AddGameObject(col3dA, 0u);
			AddGameObject(col3dB, 1u);
		}

		{
			auto model = ResourceManager<Model3D>::GetInst().Load("Player_Default");
			auto player = model->Instantiate();

			player[0]->AddScript<Script_Player>();

			for (size_t i = 0; i < 10; ++i)
			{
				player[i]->AddComponent("Script_Test");
			}
			player[11]->AddComponent("Script_Test2");

			int a = 3;

			AddGameObjects(player, 0);
		}


		{
			//std::unique_ptr<GameObject> player = NewGameObject(eLayer::Player);
			//player->AddComponent<Script_Player>();


			//std::unique_ptr<GameObject> modeling = meshdata->Instantiate(eLayer::Player);
		}
	}


}
