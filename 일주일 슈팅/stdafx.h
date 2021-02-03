// header.h: 표준 시스템 포함 파일
// 또는 프로젝트 특정 포함 파일이 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>
// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <cstdio>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <queue>
#include <list>


#include <iostream>
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
using namespace std;


//내가 추가한 헤더
#include "macroFuction.h"
#include "imageManager.h"
#include "inputManager.h"
#include "timeManager.h"
#include "cameraManager.h"
#include "itemManager.h"

//디파인

#define PI 3.1415926f
#define PI2 PI*2
#define DEGREE(p) (PI / 180.0f)*(p)
#define SAFEDELETE(p) if(p){delete(p); (p)= nullptr;}
#define IMAGEMANAGER imageManager::getSingleton()
#define TIMEMANAGER timeManager::getSingleton()
#define INPUT inputManager::getSingleton()
#define CAMERAMANAGER cameraManager::getSingleton()

#define SAFE_DELETE(p) if(p){delete (p); (p)= nullptr;}


#define WINSIZEX 800
#define WINSIZEY 600
#define WINSTARTX 400
#define WINSTARTY 100
#define WINNAME (LPSTR)(TEXT("2D"))
#define WINSTYLE WS_CAPTION | WS_SYSMENU



extern HINSTANCE _hInstance;
extern HWND _hWnd;
extern POINT _ptMouse;