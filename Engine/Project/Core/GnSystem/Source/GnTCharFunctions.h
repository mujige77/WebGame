#include <wchar.h>
#include <string>
#include <stdio.h>
#include "GnWCharFunctions.h"
#include "GnCharFunctions.h"

#ifndef GNTCHARFUNCTIONS_H
#define GNTCHARFUNCTIONS_H

#ifdef _UNICODE
#define  GNUNICODE
#endif // _UNICODE

#ifdef WIN32
#define GnText _T
#else
#define GnText
#endif


#ifdef GNUNICODE

typedef wchar_t gtchar;
typedef std::wstring gtstring;

#define GnTStrlen GnWStrlen
#define GnTStrcpy GnWStrcpy
#define GnTStrncpy GnWStrncpy
#define GnTSprintf GnWSprintf
#define GnTStrtok GnWStrtok
#define GnTStrcmp GnWStrcmp
#define GnTStricmp GnWStricmp
#define GnTStrstr GnWStrstr

#define GnTvssprintf vswprintf_s
#define GnTPrintf wprintf

#else // #ifdef GNUNICODE

typedef char gtchar;
typedef std::string gtstring;

#define GnTStrlen GnStrlen
#define GnTStrcpy GnStrcpy
#define GnTStrncpy GnStrncpy
#define GnTSprintf GnSprintf
#define GnTStrtok GnStrtok
#define GnTStrcmp GnStrcmp
#define GnTStricmp GnStricmp
#define GnTStrstr GnStrstr

#ifdef WIN32
#define GnTvssprintf vsprintf_s
#else
#define GnTvssprintf vsprintf
#endif // WINRE

#define GnTPrintf printf

#endif // #ifdef GNUNICODE

#endif // GNTCHARFUNCTIONS_H