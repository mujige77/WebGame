#ifndef GTCONVERTSTRING_H
#define GTCONVERTSTRING_H
#include <xstring>

class GtConvertString : public gtstring
{
protected:
#ifdef GNUNICODE
	std::string mConvertString;
#else // GNUNICODE
	std::wstring mConvertString;
#endif // GNUNICODE

public:
	GtConvertString();
	GtConvertString(gtstring str) : gtstring( str ) {}
	GtConvertString& operator=(gtstring str) {
		gtstring::operator=(str);
		return *this;
	}

	virtual ~GtConvertString();

	void Format( gtchar* pcFormat, ... );
#ifdef GNUNICODE	
	GtConvertString(const gchar* str)
	{
		operator=(str);
	};
	GtConvertString& operator=(const gchar* str);
	gsize GetAciiString(gchar*& outString, bool isNew = true, int outStringLength = 0);
	const gchar* GetAciiString();
#else // GNUNICODE
	bool GetConvertString();
#endif // GNUNICODE
};

template<class KeyType>
class GtTStringMapHash
{
public:
	inline static gtuint HashIndex( KeyType key )
	{
		return key.length();
	}
};

template<class T>
class GtTStringMap : public GnTMap<gtstring, T, GnDefaultDeallocate, GtTStringMapHash>
{
public:
	GtTStringMap(gtuint size = 15) : GnTMap(size)
	{}
};

#endif // GTCONVERTSTRING_H
