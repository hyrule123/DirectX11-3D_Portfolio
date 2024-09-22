
#include "Script_CameraMove.h"

#include <Engine/Game/GameObject.h>
#include <Engine/Game/Component/Camera/Com_Camera.h>
#include <Engine/Game/Component/Transform.h>
#include <Engine/Manager/InputManager.h>
#include <Engine/Manager/TimeManager.h>


namespace ehw
{
	Script_CameraMove::Script_CameraMove()
		: Script(Script_CameraMove::concrete_class_name)
		, m_camera()
		, mCamSpeed(100.f)
	{
	}

	Script_CameraMove::Script_CameraMove(const Script_CameraMove& _other)
		: Script(_other)
	{
	}

	Script_CameraMove::~Script_CameraMove()
	{
	}

	void Script_CameraMove::Awake()
	{

		m_camera = gameObject()->GetComponent<Com_Camera>();
	}

	void Script_CameraMove::update()
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
		Transform* tf = gameObject()->GetComponent<Transform>();

		// 키 입력에 따른 카메라 이동
		float3 vPos = tf->get_local_position();

		float fSpeed = mCamSpeed;
		if (InputManager::GetKeyPress(eKeyCode::LSHIFT))
		{
			fSpeed *= 5.f;
		}

		if (InputManager::GetKeyPress(eKeyCode::W))
		{
			vPos.y += TimeManager::get_inst().DeltaTime() * fSpeed;
		}

		if (InputManager::GetKeyPress(eKeyCode::S))
		{
			vPos.y -= TimeManager::get_inst().DeltaTime() * fSpeed;
		}

		if (InputManager::GetKeyPress(eKeyCode::A))
		{
			vPos.x -= TimeManager::get_inst().DeltaTime() * fSpeed;
		}

		if (InputManager::GetKeyPress(eKeyCode::D))
		{
			vPos.x += TimeManager::get_inst().DeltaTime() * fSpeed;
		}


		if (InputManager::GetKeyPress(eKeyCode::N_1))
		{
			float fScale = m_camera->GetScale();
			fScale += TimeManager::get_inst().DeltaTime() * 1.f;
			m_camera->SetScale(fScale);
		}

		if (InputManager::GetKeyPress(eKeyCode::N_2))
		{
			float fScale = m_camera->GetScale();
			fScale -= TimeManager::get_inst().DeltaTime() * 1.f;
			m_camera->SetScale(fScale);
		}

		tf->set_local_position(vPos);
	}

	void Script_CameraMove::Camera3DMove()
	{
		Transform* tf = gameObject()->GetComponent<Transform>();

		float3 vPos = tf->get_local_position();
		float3 vRot = tf->get_local_rotation().ToEuler();

		float3 vFront = tf->get_local_direction(eDirection::Forward);
		float3 vUp = tf->get_local_direction(eDirection::Up);
		float3 vRight = tf->get_local_direction(eDirection::Right);

		float fSpeed = mCamSpeed;

		if (InputManager::GetKeyPress(eKeyCode::LSHIFT))
			fSpeed *= 5.f;

		if (InputManager::GetKeyPress(eKeyCode::W))
		{
			vPos += TimeManager::get_inst().DeltaTime() * vFront * fSpeed;
		}

		if (InputManager::GetKeyPress(eKeyCode::S))
		{
			vPos -= TimeManager::get_inst().DeltaTime() * vFront * fSpeed;
		}

		if (InputManager::GetKeyPress(eKeyCode::A))
		{
			vPos -= TimeManager::get_inst().DeltaTime() * vRight * fSpeed;
		}

		if (InputManager::GetKeyPress(eKeyCode::D))
		{
			vPos += TimeManager::get_inst().DeltaTime() * vRight * fSpeed;
		}



		if (InputManager::GetKeyPress(eKeyCode::RBTN))
		{
			float2 vMouseDir = InputManager::GetMouseDir();
			vRot.y += TimeManager::get_inst().DeltaTime() * vMouseDir.x;
			vRot.x -= TimeManager::get_inst().DeltaTime() * vMouseDir.y;
		}

		tf->set_local_position(vPos);
		tf->set_local_rotation(vRot);
	}
}

