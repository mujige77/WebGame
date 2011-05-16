#pragma once
#include <string>

class GtCString : public CString
{
public:
	GtCString(){};
	GtCString(CString& cstr);
	GtCString(LPCTSTR pStr);
	GtCString(const gchar* pStr);
	~GtCString(void);

	GtCString& operator=(GtCString& str) {
		SetString( str.GetBuffer() );
		return *this;
	}

	GtCString& operator=(CString& str) {
		SetString( str.GetBuffer() );
		return *this;
	}

	GtCString& operator=(LPCTSTR pStr) {
		SetString( pStr );
		return *this;
	}

	GtCString& operator=(const gchar* str) {
		if( str == NULL ) 
			return *this;
		
		mAString = str;
		wchar_t wstr[256] = {0,};
		int nLen = MultiByteToWideChar(CP_ACP, 0, mAString.c_str(), mAString.length(), NULL, NULL);
		nLen = MultiByteToWideChar( CP_ACP, 0, mAString.c_str(), mAString.length(), wstr, nLen );
		SetString( wstr );
		return *this;
	}

	const gchar* GetAciiString();
	const gwchar* GetWideString();

protected:
	std::string mAString;
};

