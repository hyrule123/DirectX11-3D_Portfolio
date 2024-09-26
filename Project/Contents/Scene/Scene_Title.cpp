#include "Scene_Title.h"

#include <Engine/Manager/ResourceManager.h>
#include <Engine/Manager/RenderManager.h>
#include <Engine/Manager/InputManager.h>

#include <Engine/Game/GameObject.h>
#include <Engine/Game/Collision/CollisionSystem.h>
#include <Engine/Game/Collision/Collision3D.h>

#include <Engine/Game/Component/iComponent.h>
#include <Engine/Game/Component/Transform.h>
#include <Engine/Game/Component/Renderer/Com_Renderer_Mesh.h>
#include <Engine/Game/Component/Camera/Com_Camera.h>
#include <Engine/Game/Component/Renderer/Com_Renderer_Sprite.h>
#include <Engine/Game/Component/Script/GridScript.h>
#include <Engine/Game/Component/Collider/Collider2D.h>
#include <Engine/Game/Component/Animator/Com_Animator2D.h>
#include <Engine/Game/Component/Light/Light_3D.h>
#include <Engine/Game/Component/Animator/Com_Animator3D.h>
#include <Engine/Game/Component/Renderer/Com_Renderer_ParticleSystem.h>
#include <Engine/Game/Component/Renderer/Com_Renderer_UIBase.h>
#include <Engine/Game/Component/Collider/Com_Collider3D_Cube.h>
#include <Engine/Game/Component/Collider/Com_Collider3D_Sphere.h>
#include <Engine/Game/Component/Rigidbody/Com_Rigidbody_Dynamic.h>
#include <Engine/Game/Component/Rigidbody/Com_Rigidbody_Static.h>


#include <Engine/Resource/Prefab.h>
#include <Engine/Resource/Model3D/Model3D.h>
#include <Engine/Resource/Texture.h>
#include <Engine/Resource/Mesh/Mesh.h>
#include <Engine/Resource/Material/Material.h>
#include <Engine/Resource/Material/Default3DMtrl.h>

#include <Engine/Resource/define_Resource.h>

#include "Contents/Script/Script_Player.h"
#include "Contents/Script/Script_CameraMove.h"

#include <iostream>

namespace ehw
{
	Scene_Title::Scene_Title()
		: Scene(Scene_Title::concrete_class_name)
	{
	}
	Scene_Title::~Scene_Title()
	{
	}
	void Scene_Title::init()
	{
	}
	void Scene_Title::OnEnter()
	{
		{
			// Main Com_Camera Game Object
			std::unique_ptr<GameObject> cameraObj = std::make_unique<GameObject>();
			cameraObj->SetName("MainCamera");

			Transform* tr = cameraObj->transform();
			tr->set_local_position(float3(0.0f, 0.0f, -500.0f));

			Com_Camera* cameraComp = cameraObj->AddComponent<Com_Camera>();
			cameraComp->SetProjectionType(eProjectionType::Perspective);

			cameraObj->AddComponent("Script_CameraMove");

			RenderManager::get_inst().sceneRenderAgent().SetMainCamera(cameraComp);


			AddGameObject(cameraObj, 0u);
		}

		{
			std::unique_ptr<GameObject> dirLight = std::make_unique<GameObject>();
			//dirLight->AddComponent<Transform>();

			Light_3D* light3d = dirLight->AddComponent<Light_3D>();
			light3d->SetLightType(eLightType::Directional);
			light3d->SetDiffuse(float4(0.3f, 0.3f, 0.3f, 1.f));
			light3d->SetAmbient(float4(0.3f, 0.3f, 0.3f, 1.f));

			AddGameObject(dirLight, 0u);
		}

		{
			std::unique_ptr<GameObject> pointLight = std::make_unique<GameObject>();
			
			pointLight->SetName("Point1000");

			pointLight->GetComponent<Transform>()->set_world_position(float3(0.f, 200.f, 0.f));

			Light_3D* light3d = pointLight->AddComponent<Light_3D>();
			light3d->SetLightType(eLightType::Point);
			light3d->SetRadius(500.f);
			light3d->SetDiffuse(float4(0.3f, 0.f, 0.f, 1.f));
			light3d->SetAmbient(float4(0.3f, 0.f, 0.f, 1.f));

			AddGameObject(pointLight, 0);
		}

		{
			std::unique_ptr<GameObject> dirLight = std::make_unique<GameObject>();
			//dirLight->AddComponent<Transform>();
			dirLight->SetName("Point500");
			dirLight->GetComponent<Transform>()->set_world_position(float3(100.f, 100.f, 100.f));

			Light_3D* light3d = dirLight->AddComponent<Light_3D>();
			light3d->SetLightType(eLightType::Point);
			light3d->SetRadius(500.f);

			light3d->SetDiffuse(float4(0.f, 0.f, 0.3f, 1.f));

			light3d->SetAmbient(float4(0.f, 0.f, 0.3f, 1.f));

			AddGameObject(dirLight, 0u);
		}

		//{
		//	GetCollisionSystem()->SetCollisionMask(0, 0, true);
		//	GetCollisionSystem()->SetCollisionMask(0, 1, true);
		//	std::unique_ptr<GameObject> colA = std::make_unique<GameObject>("Collider A");
		//	std::unique_ptr<GameObject> colB = std::make_unique<GameObject>("Collider B");

		//	colA->AddComponent("Com_Collider2D_AABB");
		//	colA->transform()->set_local_position(float3(-50.f, 0.f, 0.f));
		//	colB->AddComponent("Com_Collider2D_AABB");
		//	colB->transform()->set_local_position(float3(0.f, 50.f, 0.f));

		//	AddGameObject(colA, 0u);
		//	AddGameObject(colB, 1u);
		//}

		{
			GetCollisionSystem()->GetCollision3D()->EnableGravity(true, float3(0.f, -9.8f, 0.f));
			physx::PxMaterial* material = GetCollisionSystem()->GetCollision3D()->GetDefaultPxMaterial();
			//material->setStaticFriction(0.f);
			//material->setDynamicFriction(0.5f);
			//material->setRestitution(0.f);

			//material->setDamping(1.f);
			//material->setFlag(physx::PxMaterialFlag::eDISABLE_FRICTION, true);

			//material->setRestitution(0.f);
			GetCollisionSystem()->SetCollisionMask(0u, 0u, true);
			GetCollisionSystem()->SetCollisionMask(0u, 1u, true);

			std::unique_ptr<GameObject> col3dA = std::make_unique<GameObject>("Collider 3D-A");
			std::unique_ptr<GameObject> col3dB = std::make_unique<GameObject>("Collider 3D-B");

			col3dA->transform()->set_local_position(float3(0.f, -100.f, 0.f));
			col3dA->transform()->set_local_scale(float3(500.f, 100.f, 500.f));

			col3dB->transform()->set_local_position(float3(0.f, 100.f, 0.f));
			col3dB->transform()->set_local_scale(float3(100.f, 100.f, 100.f));

			Com_Collider3D_Cube* colA = col3dA->AddComponent<Com_Collider3D_Cube>();
			Com_Collider3D_Cube* colB = col3dB->AddComponent<Com_Collider3D_Cube>();

			Com_Rigidbody_Dynamic* rigidDynamic = col3dB->AddComponent<Com_Rigidbody_Dynamic>();

			//rigidDynamic->SetDensity(10.f);
			rigidDynamic->SetMass(1000.f);
			rigidDynamic->EnableGravity(true);
			//rigidDynamic->SetRigidDynamicLockFlag(physx::PxRigidDynamicLockFlag::eLOCK_ANGULAR_X, true);
			//rigidDynamic->SetRigidDynamicLockFlag(physx::PxRigidDynamicLockFlag::eLOCK_LINEAR_X, true);
			//rigidDynamic->SetRigidDynamicLockFlag(physx::PxRigidDynamicLockFlag::eLOCK_LINEAR_Z, true);
			//rigidDynamic->SetRigidDynamicLockFlag(physx::PxRigidDynamicLockFlag::eLOCK_ANGULAR_Z, true);


			AddGameObject(col3dA, 0u);
			AddGameObject(col3dB, 1u);
		}

		{
			
			//auto model = ResourceManager<Model3D>::get_inst().load("Player_Default");
			//auto player = model->instantiate();

			//player[0]->AddScript<Script_Player>();

			//for (size_t i = 0; i < 10; ++i)
			//{
			//	player[i]->AddComponent("Script_Test");
			//}
			//player[11]->AddComponent("Script_Test2");

			//AddGameObjects(player, 0);
		}

		{
			std::unique_ptr<GameObject> sphere = std::make_unique<GameObject>();
			auto mesh_renderer = sphere->AddComponent<Com_Renderer_Mesh>();
			auto mesh = ResourceManager<Mesh>::get_inst().load(name::defaultRes::mesh::SphereMesh);
			
			auto mtrl = std::make_shared<Default3DMtrl>();
			mtrl->set_deffered3D_shader();

			auto albedo_tex = ResourceManager<Texture>::get_inst().load("Cube/Brick.jpg");
			auto normal_tex = ResourceManager<Texture>::get_inst().load("Cube/Brick_N.jpg");

			mtrl->set_texture(eTextureSlot::Albedo, albedo_tex);
			mtrl->set_texture(eTextureSlot::Normal, normal_tex);

			mesh_renderer->set_mesh(mesh);
			mesh_renderer->set_material(mtrl);

			sphere->GetComponent<Transform>()->set_local_scale(float3(500.f, 500.f, 500.f));
			
			AddGameObject(sphere, 0);
		}


		{
			//std::unique_ptr<GameObject> player = NewGameObject(eLayer::Player);
			//player->AddComponent<Script_Player>();


			//std::unique_ptr<GameObject> modeling = meshdata->instantiate(eLayer::Player);
		}
	}


}
