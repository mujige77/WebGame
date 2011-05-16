#ifndef GNSIMPLESTRING_H
#define GNSIMPLESTRING_H
#include "GnTCharFunctions.h"

class GNSYSTEM_ENTRY GnSimpleString : public GnMemoryObject
{
public:
	GnSimpleString();
	GnSimpleString(gchar* pStr);
	GnSimpleString(GnSimpleString& str);
	~GnSimpleString()
	{
		if( mpHandle )
			GnFree(mpHandle);
	}
	operator const gchar*() const;
	inline const gchar* GetHandle() const;
	inline void SetHandle(gchar* pcHandel);

	GnSimpleString& operator=(const GnSimpleString& str);
	GnSimpleString& operator=(const gchar* pStr);

	bool Equals(const gchar* pcStr) const;
	bool EqualsNoCase(const gchar* pcStr) const;
	bool Exists() const;

	bool Contains(const gchar* pcStr) const;
	inline gsize GetLength() const;

	friend bool operator==(const GnSimpleString& str1, const GnSimpleString& str2);
	friend bool operator!=(const GnSimpleString& str1, const GnSimpleString& str2);

	friend bool operator==(const GnSimpleString& str1, const gchar* str2);
	friend bool operator!=(const GnSimpleString& str1, const gchar* str2);

	friend bool operator==(const gchar* str1, const GnSimpleString& str2);
	friend bool operator!=(const gchar* str1, const GnSimpleString& str2);

private:
	gchar* mpHandle;
};

inline GnSimpleString::GnSimpleString() : mpHandle(NULL)
{
}

inline GnSimpleString::GnSimpleString(gchar* pStr) : mpHandle(NULL)
{
	*this = pStr;
}

inline GnSimpleString::GnSimpleString(GnSimpleString& str) : mpHandle(NULL)
{
	*this = str;
}

inline const gchar* GnSimpleString::GetHandle() const
{
	return mpHandle;
}

inline void GnSimpleString::SetHandle(gchar* pcHandel)
{
	GnAssert( mpHandle == NULL );
	mpHandle = pcHandel;
}

inline GnSimpleString::operator const char*() const
{
	return mpHandle;
}

inline GnSimpleString& GnSimpleString::operator=(const GnSimpleString& str)
{
	if (mpHandle != str.mpHandle)
	{
		guint len = GnStrlen( str.mpHandle ) + 1;
		GnAssert( len );

		if( mpHandle )
			GnFree( mpHandle );
		mpHandle = GnAlloc( gchar, len );
		GnStrcpy( mpHandle, str.mpHandle, len );
		mpHandle[len-1] = '\0';
	}
	return *this;
}
//---------------------------------------------------------------------------
inline GnSimpleString& GnSimpleString::operator=(const gchar* pStr)
{
	if ( pStr && mpHandle != pStr )
	{
		guint len = GnStrlen(pStr) + 1;
		GnAssert(len);

		if( mpHandle )
			GnFree( mpHandle );
		mpHandle = GnAlloc( gchar, len );
		GnStrcpy( mpHandle, pStr, len );
		mpHandle[len-1] = '\0';
	}
	return *this;
}

inline bool GnSimpleString::Exists() const
{
	return mpHandle != NULL;
}

//---------------------------------------------------------------------------
inline bool GnSimpleString::Equals(const gchar* pcStr) const
{
	if (mpHandle == pcStr)
		return true;

	if (pcStr == NULL  || mpHandle == NULL)
		return false;

	return GnStrcmp(mpHandle, pcStr) == 0;
}
//---------------------------------------------------------------------------
inline bool GnSimpleString::EqualsNoCase(const gchar* pcStr) const
{
	if (mpHandle == pcStr)
		return true;

	if (pcStr == NULL  || mpHandle == NULL)
		return false;

	return GnStricmp(mpHandle, pcStr) == 0;
}

//---------------------------------------------------------------------------
inline bool GnSimpleString::Contains(const gchar* pcStr) const
{
	if (mpHandle == pcStr && pcStr != NULL)
		return true;

	if (pcStr == NULL  || mpHandle == NULL || pcStr[0] == '\0' ||
		(const gchar*) mpHandle == '\0')
	{
		return false;
	}

	return GnStrstr(mpHandle, pcStr) != NULL;
}

inline gsize GnSimpleString::GetLength() const
{
	if( mpHandle == NULL )
		return 0;

	return GnStrlen(mpHandle);
}

//---------------------------------------------------------------------------
inline bool operator==(const GnSimpleString& str1, const GnSimpleString& str2)
{
	return str1.Equals( str2.mpHandle );
}
//---------------------------------------------------------------------------
inline bool operator!=(const GnSimpleString& str1, const GnSimpleString& str2)
{
	return !str1.Equals( str2.mpHandle );
}
//---------------------------------------------------------------------------
inline bool operator==(const GnSimpleString& str1, const gchar* str2)
{
	return str1.Equals(str2);
}
//---------------------------------------------------------------------------
inline bool operator!=(const GnSimpleString& str1, const gchar* str2)
{
	return !(str1.Equals(str2));
}
//---------------------------------------------------------------------------
inline bool operator==(const gchar* str1, const GnSimpleString& str2)
{
	return str2.Equals(str1);
}
//---------------------------------------------------------------------------
inline bool operator!=(const gchar* str1, const GnSimpleString& str2)
{
	return !(str2.Equals(str1));
}

#endif // GNSIMPLESTRING_H