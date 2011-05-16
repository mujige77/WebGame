#ifndef GNSIMPLEWSTRING_H
#define GNSIMPLEWSTRING_H

#include "GnTCharFunctions.h"

class GNSYSTEM_ENTRY GnSimpleTString : public GnMemoryObject
{
public:
	GnSimpleTString();
	GnSimpleTString(gtchar* pStr);
	GnSimpleTString(GnSimpleTString& str);
	~GnSimpleTString()
	{
		if( mpHandle )
			GnFree(mpHandle);
	};

	GnSimpleTString& operator=(const GnSimpleTString& str);
	GnSimpleTString& operator=(const gtchar* tcStr);

	bool Equals(const gtchar* tcStr) const;
	bool EqualsNoCase(const gtchar* tcStr) const;
	bool Exists() const;

	bool Contains(const gtchar* tcStr) const;

	friend bool operator==(const GnSimpleTString& str1, const GnSimpleTString& str2);
	friend bool operator!=(const GnSimpleTString& str1, const GnSimpleTString& str2);

	friend bool operator==(const GnSimpleTString& str1, const gtchar* str2);
	friend bool operator!=(const GnSimpleTString& str1, const gtchar* str2);

	friend bool operator==(const gtchar* str1, const GnSimpleTString& str2);
	friend bool operator!=(const gtchar* str1, const GnSimpleTString& str2);

private:
	gtchar* mpHandle;
};

inline GnSimpleTString::GnSimpleTString() : mpHandle(NULL)
{
}

inline GnSimpleTString::GnSimpleTString(gtchar* pStr)
{
	*this = pStr;
}

inline GnSimpleTString::GnSimpleTString(GnSimpleTString& str)
{
	*this = str;
}

inline GnSimpleTString& GnSimpleTString::operator=(const GnSimpleTString& str)
{
	if (mpHandle != str.mpHandle)
	{
		guint len = GnTStrlen(str.mpHandle);
		GnAssert( len > 0 );

		if( mpHandle )
			GnFree( mpHandle );
		mpHandle = GnAlloc( gtchar, len + 1 );
		GnTStrcpy( mpHandle, str.mpHandle, len );
		mpHandle[len] = '\0';
	}
	return *this;
}
//---------------------------------------------------------------------------
inline GnSimpleTString& GnSimpleTString::operator=(const gtchar* tcStr)
{
	if (mpHandle != tcStr)
	{
		guint len = GnTStrlen(tcStr);
		GnAssert(len > 0);

		if( mpHandle )
			GnFree( mpHandle );
		mpHandle = GnAlloc( gtchar, len + 1 );
		GnTStrcpy( mpHandle, tcStr, len );
		mpHandle[len] = '\0';
	}
	return *this;
}

inline bool GnSimpleTString::Exists() const
{
	return mpHandle != NULL;
}

//---------------------------------------------------------------------------
inline bool GnSimpleTString::Equals(const gtchar* tcStr) const
{
	if (mpHandle == tcStr)
		return true;

	if (tcStr == NULL  || mpHandle == NULL)
		return false;

	return GnTStrcmp(mpHandle, tcStr) == 0;
}
//---------------------------------------------------------------------------
inline bool GnSimpleTString::EqualsNoCase(const gtchar* tcStr) const
{
	if (mpHandle == tcStr)
		return true;

	if (tcStr == NULL  || mpHandle == NULL)
		return false;

	return GnTStricmp(mpHandle, tcStr) == 0;
}

//---------------------------------------------------------------------------
inline bool GnSimpleTString::Contains(const gtchar* tcStr) const
{
	if (mpHandle == tcStr && tcStr != NULL)
		return true;

	if (tcStr == NULL  || mpHandle == NULL || tcStr[0] == '\0' ||
		(const gtchar*) mpHandle == '\0')
	{
		return false;
	}

	return GnTStrstr(mpHandle, tcStr) != NULL;
}

//---------------------------------------------------------------------------
inline bool operator==(const GnSimpleTString& str1, const GnSimpleTString& str2)
{
	return str1.Equals( str2.mpHandle );
}
//---------------------------------------------------------------------------
inline bool operator!=(const GnSimpleTString& str1, const GnSimpleTString& str2)
{
	return !str1.Equals( str2.mpHandle );
}
//---------------------------------------------------------------------------
inline bool operator==(const GnSimpleTString& str1, const gtchar* str2)
{
	return str1.Equals(str2);
}
//---------------------------------------------------------------------------
inline bool operator!=(const GnSimpleTString& str1, const gtchar* str2)
{
	return !(str1.Equals(str2));
}
//---------------------------------------------------------------------------
inline bool operator==(const gtchar* str1, const GnSimpleTString& str2)
{
	return str2.Equals(str1);
}
//---------------------------------------------------------------------------
inline bool operator!=(const gtchar* str1, const GnSimpleTString& str2)
{
	return !(str2.Equals(str1));
}

#endif // GNSIMPLEWSTRING_H