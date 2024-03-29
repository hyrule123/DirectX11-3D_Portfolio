#ifndef PCH_CLIENT
#define PCH_CLIENT

#include <Contents/PCH_Contents.h>


#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>
// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include "Resource.h"

#ifdef _WIN64

#ifdef _DEBUG
#pragma comment(lib, "Contents/x64/Debug/Contents.lib")
#else _DEBUG
#pragma comment(lib, "Contents/x64/Release/Contents.lib")
#endif _DEBUG

#else _WIN64
#error "x64만 지원합니다"
#endif _WIN64

#endif PCH_CLIENT
