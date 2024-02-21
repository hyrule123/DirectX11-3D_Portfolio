#pragma once
#include <Engine/Game/Component/Script/iScript.h>

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

		virtual void Init();
		virtual void Update();

	private:
		void Camera2DMove();
		void Camera3DMove();

	private:
		std::shared_ptr<Com_Camera> m_camera;
		
		float mCamSpeed;

	};
}


