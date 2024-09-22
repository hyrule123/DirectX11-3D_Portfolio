#include "ContentsInitializer.h"

#include <Engine/Manager/SceneManager.h>
#include <Engine/Entity.h>

#include "Contents/Scene/Scene_Title.h"


namespace ehw {
	


	void ContentsInitializer::init()
	{
		SceneManager::get_inst().LoadScene("Scene_Title");
	}
}

