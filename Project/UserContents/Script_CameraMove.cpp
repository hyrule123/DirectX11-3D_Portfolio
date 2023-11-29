#include "PCH_UserContents.h"
#include "Script_CameraMove.h"

#include <EngineBase/Engine/GameObject.h>
#include <EngineBase/Engine/Com_Camera.h>
#include <EngineBase/Engine/Com_Transform.h>
#include <EngineBase/Engine/InputMgr.h>
#include <EngineBase/Engine/TimeMgr.h>


namespace ehw
{
	Script_CameraMove::Script_CameraMove()
		: mCamera()
		, mCamSpeed(100.f)
	{
	}


	Script_CameraMove::Script_CameraMove(const Script_CameraMove& _other)
	{
	}


	Script_CameraMove::~Script_CameraMove()
	{
	}

	void Script_CameraMove::Init()
	{
		mCamera = GetOwner()->GetComponent<Com_Camera>();
	}

	void Script_CameraMove::Update()
	{
		define::eProjectionType projType = mCamera->GetProjectionType();

		switch (projType)
		{
		case ehw::define::eProjectionType::None:
			ASSERT(false, "미구현");
			break;
		case ehw::define::eProjectionType::Perspective:
			Camera3DMove();
			break;
		case ehw::define::eProjectionType::Orthographic:
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
		float3 vPos = tf->GetRelativePos();

		float fSpeed = mCamSpeed;
		if (InputMgr::GetKey(eKeyCode::LSHIFT))
		{
			fSpeed *= 5.f;
		}

		if (InputMgr::GetKey(eKeyCode::W))
		{
			vPos.y += TimeMgr::DeltaTime() * fSpeed;
		}

		if (InputMgr::GetKey(eKeyCode::S))
		{
			vPos.y -= TimeMgr::DeltaTime() * fSpeed;
		}

		if (InputMgr::GetKey(eKeyCode::A))
		{
			vPos.x -= TimeMgr::DeltaTime() * fSpeed;
		}

		if (InputMgr::GetKey(eKeyCode::D))
		{
			vPos.x += TimeMgr::DeltaTime() * fSpeed;
		}


		if (InputMgr::GetKey(eKeyCode::N_1))
		{
			float fScale = mCamera->GetScale();
			fScale += TimeMgr::DeltaTime() * 1.f;
			mCamera->SetScale(fScale);
		}

		if (InputMgr::GetKey(eKeyCode::N_2))
		{
			float fScale = mCamera->GetScale();
			fScale -= TimeMgr::DeltaTime() * 1.f;
			mCamera->SetScale(fScale);
		}

		tf->SetRelativePos(vPos);
	}

	void Script_CameraMove::Camera3DMove()
	{
		Com_Transform* tf = GetOwner()->GetComponent<Com_Transform>();

		float3 vPos = tf->GetRelativePos();
		float3 vRot = tf->GetRelativeRotXYZ();

		float3 vFront = tf->Forward();
		float3 vUp = tf->Up();
		float3 vRight = tf->Right();

		float fSpeed = mCamSpeed;

		if (InputMgr::GetKey(eKeyCode::LSHIFT))
			fSpeed *= 5.f;

		if (InputMgr::GetKey(eKeyCode::W))
		{
			vPos += TimeMgr::DeltaTime() * vFront * fSpeed;
		}

		if (InputMgr::GetKey(eKeyCode::S))
		{
			vPos -= TimeMgr::DeltaTime() * vFront * fSpeed;
		}

		if (InputMgr::GetKey(eKeyCode::A))
		{
			vPos -= TimeMgr::DeltaTime() * vRight * fSpeed;
		}

		if (InputMgr::GetKey(eKeyCode::D))
		{
			vPos += TimeMgr::DeltaTime() * vRight * fSpeed;
		}



		if (InputMgr::GetKey(eKeyCode::RBTN))
		{
			float2 vMouseDir = InputMgr::GetMouseDir();
			vRot.y += TimeMgr::DeltaTime() * vMouseDir.x;
			vRot.x -= TimeMgr::DeltaTime() * vMouseDir.y;
		}

		tf->SetRelativePos(vPos);
		tf->SetRelativeRotXYZ(vRot);
	}
}

