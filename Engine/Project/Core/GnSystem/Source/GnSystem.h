#pragma once
#ifndef GNSYSTEM_H
#define GNSYSTEM_H

#include "GnPlatformConfig.h"

#include <wchar.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdint.h>

#if (GNUSE_PLATFORM == PLATFORM_IOS)
	
	#include <stddef.h>
    #include <string.h>
    #include <unistd.h>

#elif (GNUSE_PLATFORM == PLATFORM_WIN32) // (GNUSE_PLATFORM == PLATFORM_IOS)

    #include <io.h>
    #include <tchar.h>
    #include <cassert>
    #include <cfloat>
    #include <climits>
    #include <cmath>
    #include <cstdarg>
    #include <cstdio>
    #include <cstdlib>
    #include <cstring>
    #include <ctime>
    #include <string>
	#include <Windows.h>
	#include <SDKDDKVer.h>

#endif // (GNUSE_PLATFORM == PLATFORM_IOS)

#include "GnSystemLibType.h"
#include "GnSystemDefine.h"
#include "GnMemoryDefine.h"
#include "GnMemoryObject.h"
#include "GnBitwiseoperation.h"
#include "GnSimpleString.h"
#include "GnSimpleTString.h"
#include "GnSmartObject.h"
#include "GnTOther.h"
#include "GnTypeTraits.h"
#include "GnList.h"
#include "GnTArray.h"
#include "GnTMap.h"
#include "GnTStringMap.h"
#include "GnTSet.h"
#include "GnLog.h"
#include "GnPath.h"
#include "GnSingletonManager.h"
#include "GnTimer.h"
#include "GnStandardFunction.h"
namespace GnSystem
{
	GNSYSTEM_ENTRY void SetWorkDirectory(const gchar* pcVal);
	GNSYSTEM_ENTRY const gchar* GetWorkDirectory();
}


#endif // GNSYSTEM_H
