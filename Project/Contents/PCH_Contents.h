#ifndef PCH_CONTENTS
#define PCH_CONTENTS

#include <Engine/PCH_Engine.h>

#if defined (_WIN64) && (_DEBUG)
#pragma comment(lib, "Engine/x64/Debug/Engine.lib")

#include <Editor/PCH_Editor.h>
#pragma comment(lib, "Editor/x64/Debug/Editor.lib")
#endif //(_WIN64) && (_DEBUG)

#if defined (_WIN64) && !(_DEBUG)
#pragma comment(lib, "Engine/x64/Release/Engine.lib")
#endif

#endif
