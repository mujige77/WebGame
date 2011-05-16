#include "StdAfx.h"
#include "GtCString.h"


GtCString::GtCString(CString& cstr)
{
	SetString( cstr.GetBuffer() );
}
GtCString::GtCString(LPCTSTR pStr)
{
	SetString( pStr );
}

GtCString::GtCString(const gchar* pStr)
{
	*this = pStr;
}
GtCString::~GtCString(void)
{
}

const gchar* GtCString::GetAciiString()
{
#ifdef UNICODE
	gchar str[256] = {0,};
	int length = WideCharToMultiByte( CP_ACP, 0, GetBuffer(), -1, str, sizeof( str ), NULL, NULL );
	mAString = str;
	return mAString.c_str();
#else
	mAString.resize( GetLength() );
	gchar str[256];
	WideCharToMultiByte( CP_ACP, 0, GetBuffer(), -1, str, GetLength(), NULL, NULL );
	return mAString.c_str();
#endif // UNICODE
}

const gwchar* GtCString::GetWideString()
{
#ifdef UNICODE
	return GetString();
#else
	mAString.resize( GetLength() );
	gchar str[256];
	WideCharToMultiByte( CP_ACP, 0, GetBuffer(), -1, str, GetLength(), NULL, NULL );
	return mAString.c_str();
#endif // UNICODE
	return NULL;
}