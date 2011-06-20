#pragma once
#ifndef GNSYSTEM_H
#define GNSYSTEM_H


#include <wchar.h>
#include <stddef.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdint.h>

#if defined(__IPHONE_NA) || defined (__MAC_NA)

    #include <TargetConditionals.h>
    #include <string.h>
    #include <unistd.h>

#elif defined(WIN32) // #if defined(__IPHONE_NA) || defined (__MAC_

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

#endif // #if defined(__IPHONE_NA) || defined (__MAC_NA)

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

namespace GnSystem
{
	GNSYSTEM_ENTRY void SetWorkDirectory(const gchar* pcVal);
	GNSYSTEM_ENTRY const gchar* GetWorkDirectory();
}


#endif // GNSYSTEM_H
