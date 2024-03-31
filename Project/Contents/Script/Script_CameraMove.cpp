
#include "Script_CameraMove.h"

#include <Engine/Game/GameObject.h>
#include <Engine/Game/Component/Camera/Com_Camera.h>
#include <Engine/Game/Component/Transform/Com_Transform.h>
#include <Engine/Manager/InputManager.h>
#include <Engine/Manager/TimeManager.h>


namespace ehw
{
	Script_CameraMove::Script_CameraMove()
		: m_camera()
		, mCamSpeed(100.f)
	{
	}


	Script_CameraMove::Script_CameraMove(const Script_CameraMove& _other)
	{
	}


	Script_CameraMove::~Script_CameraMove()
	{
	}

	void Script_CameraMove::Awake()
	{

		m_camera = GetOwner()->GetComponent<Com_Camera>();
	}

	void Script_CameraMove::Update()
	{
		eProjectionType projType = m_camera->GetProjectionType();

		switch (projType)
		{
		case ehw::eProjectionType::None:
			ASSERT(false, "미구현");
			break;
		case ehw::eProjectionType::Perspective:
			Camera3DMove();
			break;
		case ehw::eProjectionType::Orthographic:
			Camera2DMove();
			break;
		default:
			ASSERT(false, "미구현");
			break;
		}
	}


	void Script_CameraMove::Camera2DMove()
	{
		Com_Transform* tf = GetOwner()->GetComponent<Com_Transform>();

		// 키 입력에 따른 카메라 이동
		float3 vPos = tf->GetLocalPosition();

		float fSpeed = mCamSpeed;
		if (InputManager::GetKeyPress(eKeyCode::LSHIFT))
		{
			fSpeed *= 5.f;
		}

		if (InputManager::GetKeyPress(eKeyCode::W))
		{
			vPos.y += TimeManager::DeltaTime() * fSpeed;
		}

		if (InputManager::GetKeyPress(eKeyCode::S))
		{
			vPos.y -= TimeManager::DeltaTime() * fSpeed;
		}

		if (InputManager::GetKeyPress(eKeyCode::A))
		{
			vPos.x -= TimeManager::DeltaTime() * fSpeed;
		}

		if (InputManager::GetKeyPress(eKeyCode::D))
		{
			vPos.x += TimeManager::DeltaTime() * fSpeed;
		}


		if (InputManager::GetKeyPress(eKeyCode::N_1))
		{
			float fScale = m_camera->GetScale();
			fScale += TimeManager::DeltaTime() * 1.f;
			m_camera->SetScale(fScale);
		}

		if (InputManager::GetKeyPress(eKeyCode::N_2))
		{
			float fScale = m_camera->GetScale();
			fScale -= TimeManager::DeltaTime() * 1.f;
			m_camera->SetScale(fScale);
		}

		tf->SetLocalPosition(vPos);
	}

	void Script_CameraMove::Camera3DMove()
	{
		Com_Transform* tf = GetOwner()->GetComponent<Com_Transform>();

		float3 vPos = tf->GetLocalPosition();
		float3 vRot = tf->GetLocalRotation().ToEuler();

		float3 vFront = tf->GetLocalDirection(eDirection::Forward);
		float3 vUp = tf->GetLocalDirection(eDirection::Up);
		float3 vRight = tf->GetLocalDirection(eDirection::Right);

		float fSpeed = mCamSpeed;

		if (InputManager::GetKeyPress(eKeyCode::LSHIFT))
			fSpeed *= 5.f;

		if (InputManager::GetKeyPress(eKeyCode::W))
		{
			vPos += TimeManager::DeltaTime() * vFront * fSpeed;
		}

		if (InputManager::GetKeyPress(eKeyCode::S))
		{
			vPos -= TimeManager::DeltaTime() * vFront * fSpeed;
		}

		if (InputManager::GetKeyPress(eKeyCode::A))
		{
			vPos -= TimeManager::DeltaTime() * vRight * fSpeed;
		}

		if (InputManager::GetKeyPress(eKeyCode::D))
		{
			vPos += TimeManager::DeltaTime() * vRight * fSpeed;
		}



		if (InputManager::GetKeyPress(eKeyCode::RBTN))
		{
			float2 vMouseDir = InputManager::GetMouseDir();
			vRot.y += TimeManager::DeltaTime() * vMouseDir.x;
			vRot.x -= TimeManager::DeltaTime() * vMouseDir.y;
		}

		tf->SetLocalPosition(vPos);
		tf->SetLocalRotation(vRot);
	}
}

