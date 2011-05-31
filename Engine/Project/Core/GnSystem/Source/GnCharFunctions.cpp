#include "GnSystemPCH.h"
#include "GnCharFunctions.h"

//GNFORCEINLINE size_t GnStrlen(const gchar* GNRESTRICT str)
//{
//    return strlen(str);
//}
//
//GNFORCEINLINE gchar* GnStrcpy(gchar* GNRESTRICT dest, const gchar* GNRESTRICT src, size_t destSize)
//{
//#ifdef __GNUC__
//	return strcpy(dest, src);
//#else // #ifdef __GNUC__
//	strcpy_s(dest, destSize, src);
//	return dest;
//#endif // #ifdef __GNUC__
//    
//}
//
//GNFORCEINLINE gchar* GnStrncpy(gchar* GNRESTRICT dest, const gchar*  src, size_t strLength, size_t destSize)
//{
//#ifdef __GNUC__
//	return strncpy(dest, src, strLength);
//#else // #ifdef __GNUC__
//	strncpy_s(dest, destSize, src, strLength);
//	return dest;
//#endif // #ifdef __GNUC__
//}
//
//GNFORCEINLINE gint GnSprintf(gchar* GNRESTRICT buffer, gsize bufferSize, const gchar* GNRESTRICT format, ...)
//{
//    va_list args;
//    va_start( args, format );
//#ifdef __GNUC__
//	gint ret = vsprintf(buffer, format, args);
//#else // #ifdef __GNUC__
//	gint ret = vsprintf_s(buffer, bufferSize, format, args);
//#endif // #ifdef __GNUC__
//    va_end(args);
//    return ret;
//}
//
//GNFORCEINLINE gchar* GnStrtok(gchar* GNRESTRICT pcString, const gchar* GNRESTRICT pcDelimit,
//    gchar** GNRESTRICT ppcContext)
//{
//#if _MSC_VER >= 1400
//	return strtok_s(pcString, pcDelimit, ppcContext);
//#else // #if _MSC_VER >= 1400
//	return strtok(pcString, pcDelimit);
//#endif // #if _MSC_VER >= 1400
//}
//
//GNFORCEINLINE gint GnStrcmp(const gchar* GNRESTRICT pStr1, const gchar* GNRESTRICT pStr2)
//{
//	return strcmp(pStr1, pStr2);
//}
//
//GNFORCEINLINE gint GnStricmp(const gchar* GNRESTRICT pStr1, const gchar* GNRESTRICT pStr2)
//{
//#ifdef WIN32
//	return _stricmp(pStr1, pStr2);
//#else
//	return stricmp(pStr1, pStr2);
//#endif // WIN32
//	
//}
//
//GNFORCEINLINE const gchar* GnStrstr(const gchar* GNRESTRICT pStr1, const gchar* GNRESTRICT pStr2)
//{
//	return strstr(pStr1, pStr2);
//}

gchar* GnAllocStrcpy(const gchar* GNRESTRICT src)
{
	gsize strSize = GnStrlen( src )+1;
	gchar* outStr = GnAlloc( gchar, strSize ); 
	GnStrcpy( outStr, src, strSize );
	outStr[strSize-1] = '\0';
	return outStr;
}