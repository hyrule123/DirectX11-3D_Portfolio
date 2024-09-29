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
		void create_camera();
		void create_lights();
		void create_test_physics_colliders();
		void create_test_3D_modeling();
		void create_test_sphere_mesh();
	};
}
