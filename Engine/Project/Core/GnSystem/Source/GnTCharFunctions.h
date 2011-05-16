#include <wchar.h>
#include <string.h>
#include <stdio.h>
#include "GnWCharFunctions.h"
#include "GnCharFunctions.h"

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

#define GnTvssprintf vsprintf_s


#endif // #ifdef GNUNICODE


//#ifdef GNUNICODE

//#define GnTstrlen wcslen
//#define GnTstrcpy wcscpy
//#define GnTvssprintf vswprintf
//#define GnTsprintf swprintf
//#define GnTaccess _waccess
//#define GnTfopen _wfopen
//#define GnTfgets fgetws
//#define GnTvfprintf vfwprintf
//#define GnTfsscanf fwscanf
//#define GnTsscanf swscanf

//#else // #ifdef GNUNICODE

//#define GnTstrlen strlen
//#define GnTstrcpy strcpy_s
//#define GnStrncpy strncpy_s
//#define GnTsprintf sprintf_s
//#define GnTvssprintf vsprintf_s
//#define GnTsprintf sprintf_s
//#define GnTaccess _access
//#define GnTfopen fopen_s
//#define GnTfgets fgets
//#define GnTvfprintf vfprintf_s
//#define GnTfsscanf fscanf_s
//#define GnTsscanf  sscanf_s

//#endif // #ifdef GNUNICODE