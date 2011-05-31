#include "StdAfx.h"
#include "GtNumberString.h"


GtNumberString::GtNumberString(void)
{
}


GtNumberString::~GtNumberString(void)
{
}

void GtNumberString::SetNumber(gtuint uiNumberLength, gint uiNumber, const gtchar* pcFrontString
	, const gtchar* pcBackString)
{
	gtstring format;
	if( pcFrontString )
		format = pcFrontString;

	gtuint number = abs(uiNumber);
	gtuint checkNumber = 10;

	--uiNumberLength;
	while( uiNumberLength )
	{
		if( checkNumber > number )
		{			
			format += _T("0");
		}
		checkNumber *= 10;
		--uiNumberLength;
	}
	format += _T("%d");

	gtchar str[512] = {0,};
	_stprintf_s( str, format.c_str(), uiNumber );
	
	mString = str;
	if( pcBackString )
		mString += pcBackString;
}