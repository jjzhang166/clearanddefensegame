// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 从 Windows 头中排除极少使用的资料
// Windows 头文件: 
#include <windows.h>

// C 运行时头文件
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#define TimerDrawAll 0
#define SelectStatus 1000
#define PlayStatus 1001
#define GameOverStatus 1002
#define GameNextStatus 1003
#define NullBtn 1999
#define StartBtn 2000
#define QuitBtn 2001
#define ReturnBtn 2003
#define Moveing 2004
#define NotMoving 2005
#define Time 2006
#define BOOM1 8
#define BOOM2 9
#define BOOM3 10
#define BOOM4 11
#define PLAY 3001
#define PAUSE 3002
#define Dragon 4001
#define Tiger 4002

#define DRAGON_BOOM 5001
#define TIGER_BOOM 5002
#define DEFENSE_BOOM 5003