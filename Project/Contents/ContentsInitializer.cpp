#include "ContentsInitializer.h"

#include <Engine/Manager/SceneManager.h>
#include <Engine/Instance.h>

#include "Contents/Scene/Scene_Title.h"


namespace ehw {
	


	void ContentsInitializer::init()
	{

		auto name = ClassInfo2<Scene_Title>::name;

		SceneManager::GetInst().LoadScene("Scene_Title");
	}
}

