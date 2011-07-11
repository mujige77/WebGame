#include "stdafx.h"

std::string GetOnlyFileNameAttachNumber(gtint iID, const gchar* filePath)
{
	GtNumberString number;
	number.SetNumber( 3, iID );
	GtConvertString convert = number.GetString().c_str();
	convert += _T("_");

	// get only filename
	gchar name[GN_MAX_PATH] = { 0, };
	GnVerify( GnPath::GetFileNameA( filePath, name, GN_MAX_PATH, true ) );
	std::string fileName = name;
	// if not exist number add number
	if( fileName.find( convert.GetAciiString() ) == std::string::npos )
	{
		fileName = convert.GetAciiString();
		fileName += name;
	}

	return fileName;
}