// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once
#if defined(_WIN32)
	#define OS_WINDOWS
	#include "targetver.h"
	#include "windows.h"
	#include <tchar.h>
#elif defined(unix) || defined(__unix) || defined(__unix__)
	#define OS_UNIX
	// Unix Memes
#elif defined(__APPLE__) || defined(__MACH__)
	#define OS_APPLE
	// Mac Memes
#elif defined(__linux__) || defined(linux) || defined(__linux)
	#define OS_LINUX
	// Linux Memes
#endif

#include <stdio.h>
#include <iostream>
#include <direct.h>
#include <vector>
#include <iterator>
#include <algorithm>




// TODO: reference additional headers your program requires here
