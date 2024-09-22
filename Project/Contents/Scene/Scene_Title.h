#pragma once
#include <Engine/Game/Scene.h>

namespace ehw
{
	class Scene_Title : public Scene
	{
		CLASS_NAME(Scene_Title);
		REGISTER_INSTANCE_DEFAULT(Scene_Title);
		
	public:
		Scene_Title();
		virtual ~Scene_Title();

		void init() final;
		void OnEnter() final;

	private:
	};
}
