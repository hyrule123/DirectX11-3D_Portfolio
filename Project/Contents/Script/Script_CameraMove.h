#pragma once
#include <Engine/Scene/Component/Script/iScript.h>

namespace ehw
{
	class Com_Camera;
	class Script_CameraMove :
		public iScript
	{
	public:
		Script_CameraMove();

		Script_CameraMove(const Script_CameraMove& _other);
		CLONE_ABLE(Script_CameraMove);


		virtual ~Script_CameraMove();

		virtual void Awake();
		virtual void Update();

	private:
		void Camera2DMove();
		void Camera3DMove();

	private:
		Com_Camera* m_camera;
		
		float mCamSpeed;
	};
}


