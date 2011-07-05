#ifndef GNCHARFUNCTIONS_H
#define GNCHARFUNCTIONS_H



#include <wchar.h>
#include <string.h>
#include <stdio.h>
#include "GnSystemDefine.h"


//GNFORCEINLINE gsize GnStrlen(const gchar* GNRESTRICT str);
//
//GNFORCEINLINE gchar* GnStrcpy(gchar* GNRESTRICT dest, const gchar* GNRESTRICT src, size_t destSize);
//
//GNFORCEINLINE gchar* GnStrncpy(gchar* GNRESTRICT dest, const gchar* GNRESTRICT src, size_t strLength,
//	size_t destSize);
//
//GNFORCEINLINE gint GnSprintf(gchar* GNRESTRICT buffer, gsize bufferSize, const gchar* GNRESTRICT format, ...);
//
//GNFORCEINLINE gchar* GnStrtok(gchar* GNRESTRICT pcString, const gchar* GNRESTRICTpcDelimit
//	, gchar** ppcContext);
//
//GNFORCEINLINE gint GnStrcmp(const gchar* GNRESTRICT pStr1, const gchar* GNRESTRICT pStr2);
//
//GNFORCEINLINE gint GnStricmp(const gchar* GNRESTRICT pStr1, const gchar* GNRESTRICT pStr2);
//
//GNFORCEINLINE const gchar* GnStrstr(const gchar* GNRESTRICT pStr1, const gchar* GNRESTRICT pStr2);

#ifdef WIN32
#define GnVssprintf vsprintf_s
#else // WIN32
#define GnVssprintf vsprintf
#endif // WIN32

typedef std::string gstring;

gchar* GnAllocStrcpy(const gchar* GNRESTRICT src);

static GNFORCEINLINE size_t GnStrlen(const gchar* GNRESTRICT str)
{
	return strlen(str);
}

static GNFORCEINLINE gchar* GnStrcpy(gchar* GNRESTRICT dest, const gchar* GNRESTRICT src, size_t destSize)
{
#ifdef __GNUC__
	return strcpy(dest, src);
#else // #ifdef __GNUC__
	strcpy_s(dest, destSize, src);
	return dest;
#endif // #ifdef __GNUC__

}

static GNFORCEINLINE gchar* GnStrncpy(gchar* GNRESTRICT dest, const gchar*  src, size_t strLength, size_t destSize)
{
#ifdef __GNUC__
	return strncpy(dest, src, strLength);
#else // #ifdef __GNUC__
	strncpy_s(dest, destSize, src, strLength);
	return dest;
#endif // #ifdef __GNUC__
}

static GNFORCEINLINE const gchar* GnStrcat(gchar* GNRESTRICT pStr1, const gchar* GNRESTRICT pStr2, gsize destSize)
{
#ifdef __GNUC__
	return strcat(pStr1, pStr2);
#else // #ifdef __GNUC__
	errno_t error = strcat_s(pStr1, destSize, pStr2);
	return pStr1;
#endif // #ifdef __GNUC__
}

static GNFORCEINLINE gint GnSprintf(gchar* GNRESTRICT buffer, gsize bufferSize, const gchar* GNRESTRICT format, ...)
{
	va_list args;
	va_start( args, format );
#ifdef __GNUC__
	gint ret = vsprintf(buffer, format, args);
#else // #ifdef __GNUC__
	gint ret = vsprintf_s(buffer, bufferSize, format, args);
#endif // #ifdef __GNUC__
	va_end(args);
	return ret;
}

static GNFORCEINLINE gchar* GnStrtok(gchar* GNRESTRICT pcString, const gchar* GNRESTRICT pcDelimit,
	gchar** GNRESTRICT ppcContext)
{
#if _MSC_VER >= 1400
	return strtok_s(pcString, pcDelimit, ppcContext);
#else // #if _MSC_VER >= 1400
	return strtok(pcString, pcDelimit);
#endif // #if _MSC_VER >= 1400
}

static GNFORCEINLINE gint GnStrcmp(const gchar* GNRESTRICT pStr1, const gchar* GNRESTRICT pStr2)
{
	return strcmp(pStr1, pStr2);
}

static GNFORCEINLINE gint GnStricmp(const gchar* GNRESTRICT pStr1, const gchar* GNRESTRICT pStr2)
{
#ifdef WIN32
	return _stricmp(pStr1, pStr2);
#else
	return strcasecmp(pStr1, pStr2);
#endif // WIN32

}

static GNFORCEINLINE const gchar* GnStrstr(const gchar* GNRESTRICT pStr1, const gchar* GNRESTRICT pStr2)
{
	return strstr(pStr1, pStr2);
}

#endif // GNCHARFUNCTIONS_H