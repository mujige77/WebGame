#include "GnToolLibPCH.h"
#include "GtConvertString.h"


GtConvertString::GtConvertString(void)
{
}


GtConvertString::~GtConvertString(void)
{
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