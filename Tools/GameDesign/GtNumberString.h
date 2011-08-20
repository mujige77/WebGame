#pragma once
#

template<typename T>
class GtNumberString : public gtstring
{
public:
	void SetNumber(T uiNumber, gtuint uiNumberLength = 1, const gtchar* pcFrontString = NULL
		, const gtchar* pcBackString = NULL)
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

		assign( str );
		if( pcBackString )
			append( pcBackString );
	}

	T GetNumber(T iNullValue = 0)
	{
		if( length() <= 0)
			return iNullValue;

		return Ato( c_str() );
	}
	
	void SetNumber(gtchar* tNumbuer) {
		assign( tNumbuer );
	}
protected:
	virtual T Ato(const gtchar* val) = 0;
};

class GtLongNumberString : public GtNumberString<glong>
{
protected:
	virtual glong Ato(const gtchar* val)
	{
		glong ounNum;
		_stscanf_s( val, GnText( "%d" ), &ounNum );
		return ounNum;
	};
};

class GtULongNumberStrinig : public GtNumberString<gulong>
{
protected:
	virtual gulong Ato(const gtchar* val)
	{
		glong ounNum;
		_stscanf_s( val, GnText( "%u" ), &ounNum );
		return ounNum;
	};
};