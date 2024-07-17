#pragma once
#include <Engine/Scene/Scene.h>

namespace ehw
{
	class Scene_Title : public Scene
	{
	public:
		Scene_Title();
		virtual ~Scene_Title();

		void Init() final;
		void OnEnter() final;

	private:
	};
}
