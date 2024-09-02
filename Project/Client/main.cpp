#include "PCH_Client.h"

#include <Base/Engine/EngineMain.h>

#ifdef EDITOR_INCLUDED
#include <Editor/EditorManager.h>
#endif

ehw::tDesc_EngineMain Desc{};

inline void DebugCheck(long _block);
BOOL APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    DebugCheck(0);

    using namespace ehw;
    
    Desc.Inst = hInstance;
    Desc.TitleName = TEXT("Monster Hunter World");
    Desc.ClassName = TEXT("GameEngine Client");
    Desc.LeftPos = 100;
    Desc.TopPos = 100;
    Desc.Width = 1280;
    Desc.Height = 720;

    Desc.WindowIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));

    Desc.GPUDesc.ResolutionX = (UINT)Desc.Width;
    Desc.GPUDesc.ResolutionY = (UINT)Desc.Height;
    Desc.GPUDesc.RefreshRate = (UINT)60u;

#ifdef EDITOR_INCLUDED
    Desc.EditorRunFunction = ehw::editor::EditorManager::GetEditorRunFunction();
    ehw::editor::EditorManager::OpenEditorAsDefault(true);
#endif

    EngineMain mainWindow(Desc);
    return mainWindow.Run();
}

inline void DebugCheck(long _block)
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    if (_block)
    {
        _CrtSetBreakAlloc(_block);
    }
}
