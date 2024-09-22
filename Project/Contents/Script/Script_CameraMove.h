#pragma once
#include <Engine/Game/Component/Script/Script.h>

namespace ehw
{
	class Com_Camera;
	class Script_CameraMove :
		public Script
	{
		CLASS_NAME(Script_CameraMove);
		REGISTER_INSTANCE_DEFAULT(Script_CameraMove);
		
	public:
		Script_CameraMove();
		Script_CameraMove(const Script_CameraMove& _other);
		CLONE_ABLE(Script_CameraMove);

		virtual ~Script_CameraMove();

		virtual void Awake();
		virtual void update();

	private:
		void Camera2DMove();
		void Camera3DMove();

	private:
		Com_Camera* m_camera;
		
		float mCamSpeed;
	};
}


