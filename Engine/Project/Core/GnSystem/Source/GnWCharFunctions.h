#ifndef GNWCHARFUNCTIONS_H
#define GNWCHARFUNCTIONS_H

#include <wchar.h>
#include <string.h>
#include <stdio.h>
#include "GnSystemDefine.h"

//GNFORCEINLINE gsize GnWStrlen(const gwchar* GNRESTRICT src);
//
//GNFORCEINLINE gwchar* GnWStrcpy(gwchar* GNRESTRICT dest, const gwchar* GNRESTRICT src, size_t destSize);
//
//GNFORCEINLINE gwchar* GnWStrncpy(gwchar* GNRESTRICT dest, const gwchar* GNRESTRICT src, size_t strLength,
//	size_t destSize);
//
//GNFORCEINLINE gint GnWSprintf(gwchar* GNRESTRICT buffer, gsize bufferSize, const gwchar* GNRESTRICT format
//    , ...);
//
//GNFORCEINLINE gwchar* GnWStrtok(gwchar* GNRESTRICT pcString, const gwchar* GNRESTRICT pcDelimit
//    , gwchar** GNRESTRICT ppcContext);
//
//GNFORCEINLINE gint GnWStrcmp(const gwchar* GNRESTRICT pStr1, const gwchar* GNRESTRICT pStr2);
//
//GNFORCEINLINE gint GnWStricmp(const gwchar* GNRESTRICT pStr1, const gwchar* GNRESTRICT pStr2);
//
//GNFORCEINLINE const gwchar* GnWStrstr(const gwchar* GNRESTRICT pStr1, const gwchar* GNRESTRICT pStr2);

#define GnWVssprintf vswprintf_s

GNSYSTEM_ENTRY GNFORCEINLINE gsize GnWStrlen(const gwchar* GNRESTRICT str)
{
	return wcslen(str);
}

GNSYSTEM_ENTRY GNFORCEINLINE gwchar* GnWStrcpy(gwchar* GNRESTRICT dest, const gwchar* GNRESTRICT src, size_t destSize)
{
#ifdef __GNUC__
	return wcscpy(dest, src);
#else
	wcscpy_s(dest, destSize, src);
	return dest;
#endif
}

GNSYSTEM_ENTRY GNFORCEINLINE gwchar* GnWStrncpy(gwchar* GNRESTRICT dest, const gwchar* GNRESTRICT src, size_t strLength
	, size_t destSize)
{
#ifdef __GNUC__
	return wcsncpy(dest, src, strLength);
#else
	wcsncpy_s(dest, destSize, src, strLength);
	return dest;
#endif

}
GNFORCEINLINE const gwchar* GnWStrcat(gwchar* GNRESTRICT pStr1, const gwchar* GNRESTRICT pStr2, gsize destSize)
{
#ifdef __GNUC__
	return wcscat(pStr1, pStr2);
#else // #ifdef __GNUC__
	errno_t error = wcscat_s(pStr1, destSize, pStr2);
	return pStr1;
#endif // #ifdef __GNUC__
}


GNSYSTEM_ENTRY GNFORCEINLINE gint GnWSprintf(gwchar* GNRESTRICT buffer, gsize bufferSize, const gwchar* GNRESTRICT format
	, ...)
{
#ifdef __GNUC__
	__darwin_va_list args;
#else
	va_list args;
#endif

	va_start( args, format );
	gint ret = vswprintf(buffer, bufferSize, format, args);
	va_end(args);
	return ret; 
}

GNSYSTEM_ENTRY GNFORCEINLINE gwchar* GnWStrtok(gwchar* GNRESTRICT pcString, const gwchar* GNRESTRICT pcDelimit
	, gwchar** GNRESTRICT ppcContext)
{
#ifdef __GNUC__
	return wcstok(pcString, pcDelimit, ppcContext);
#else
	return wcstok_s(pcString, pcDelimit, ppcContext);
#endif
}

GNSYSTEM_ENTRY GNFORCEINLINE gint GnWStrcmp(const gwchar* GNRESTRICT pStr1, const gwchar* GNRESTRICT pStr2)
{
	return wcscmp(pStr1, pStr2);
}

GNSYSTEM_ENTRY GNFORCEINLINE gint GnWStricmp(const gwchar* GNRESTRICT pStr1, const gwchar* GNRESTRICT pStr2)
{
#ifdef WIN32
	return _wcsicmp(pStr1, pStr2);
#else
	return wcsicmp(pStr1, pStr2);
#endif
}

GNSYSTEM_ENTRY GNFORCEINLINE const gwchar* GnWStrstr(const gwchar* GNRESTRICT pStr1, const gwchar* GNRESTRICT pStr2)
{
	return wcsstr(pStr1, pStr2);
}
#endif // GNWCHARFUNCTIONS_H