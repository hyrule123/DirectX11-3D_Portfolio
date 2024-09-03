#pragma once
#include <Engine/Game/Component/Script/Script.h>

namespace ehw
{
	class Com_Camera;
	class Script_CameraMove :
		public Script
	{
		REGISTER_CLASS_INFO(Script_CameraMove);
		SET_INSTANCE_ABLE(Script_CameraMove);
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


