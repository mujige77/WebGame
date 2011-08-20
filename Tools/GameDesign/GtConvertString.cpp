#include "StdAfx.h"
#include "GtConvertString.h"


GtConvertString::GtConvertString(void)
{
}


GtConvertString::~GtConvertString(void)
{
}

void GtConvertString::Format(gtchar* pcFormat, ...)
{
	gtchar buffer[1024] = {0,};
	va_list args;
	va_start( args, pcFormat );
#ifdef __GNUC__
	gint ret = vsprintf(buffer, pcFormat, args);
#else // #ifdef __GNUC__
	gint ret = GnTvssprintf(buffer, 1024, pcFormat, args);
#endif // #ifdef __GNUC__
	va_end(args);
	operator=(buffer);
}

gsize GtConvertString::GetAciiString(gchar*& outString, bool isNew /*= true*/, int outStringLength)
{
	int multiByteLength = WideCharToMultiByte( CP_ACP, 0, c_str(), length(), NULL, NULL, NULL, NULL );

	if( isNew )
		outString = new gchar[multiByteLength+1];
	else if( multiByteLength > outStringLength )
		return -1;


	multiByteLength = WideCharToMultiByte( CP_ACP, 0, c_str(), length(), outString, outStringLength, NULL, NULL );
	//int nLen = MultiByteToWideChar(CP_ACP, 0, c_str(), length(), NULL, NULL);
	//if( isNew )
	//	outString = new gchar[nLen+1];
	//else if( nLen > outStringLength )
	//	return -1;

	//nLen = MultiByteToWideChar( CP_ACP, 0, c_str(), length(), outString, nLen );
	return multiByteLength;
}

const gchar* GtConvertString::GetAciiString()
{
	gchar str[512] = {0,};
	int multiByteLength = WideCharToMultiByte( CP_ACP, 0, c_str(), length(), str, 512, NULL, NULL );
	mConvertString = str;
	return mConvertString.c_str();
}

GtConvertString& GtConvertString::operator=(const gchar* str)
{
	if( str == NULL ) 
		return *this;

	mConvertString = str;
	wchar_t wstr[1024] = {0,};
	int nLen = MultiByteToWideChar(CP_ACP, 0, mConvertString.c_str(), mConvertString.length()
		, NULL, NULL);
	nLen = MultiByteToWideChar( CP_ACP, 0, mConvertString.c_str(), mConvertString.length(), wstr, nLen );
	operator=(wstr);
	return *this;
}