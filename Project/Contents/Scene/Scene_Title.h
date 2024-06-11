#pragma once
#include <Engine/Scene/iScene.h>

namespace ehw
{
	class Scene_Title : public iScene
	{
	public:
		Scene_Title();
		virtual ~Scene_Title();

		void Init() final;
		void OnEnter() final;

	private:
	};
}
