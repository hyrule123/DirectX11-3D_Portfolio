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
		void update() final;

	private:
		void create_camera();
		void create_lights();
		void create_test_physics_colliders();
		GameObject* create_test_3D_modeling(const std::string_view _name, const float3& _where);
		void create_test_sphere_mesh();
		void create_delayed_3D_modeling();

	private:
		float m_wait = 1.f;
	};
}
