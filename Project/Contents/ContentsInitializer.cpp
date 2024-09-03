#include "ContentsInitializer.h"

#include <Engine/Manager/SceneManager.h>
#include <Engine/ClassInfo.h>

#include "Contents/Scene/Scene_Title.h"


namespace ehw {
	


	void ContentsInitializer::init()
	{
		SceneManager::GetInst().LoadScene("Scene_Title");
	}
}

