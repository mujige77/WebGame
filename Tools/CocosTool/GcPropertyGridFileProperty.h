#pragma once
#include "GcPropertyGridProperty.h"

class GcPropertyGridFileProperty : public GcPropertyGridProperty
{
protected:
	BOOL    m_bIsFolder;
	BOOL m_bOpenFileDialog; // TRUE - use "File Open/Save" diaog; otherwise - folder selection dialog
	DWORD m_dwFileOpenFlags;
	CString m_strDefExt;
	CString m_strFilter;	
	CString mFullFilePath;
	CString mUserDescr;
	bool mDrawFileName;

public:
	GcPropertyGridFileProperty(const CString& strName, const CString& strFolderName, bool bDrawFileName
		, DWORD_PTR dwData = 0, LPCTSTR lpszDescr = NULL);
	GcPropertyGridFileProperty(const CString& strName, BOOL bOpenFileDialog, const CString& strFileName, bool bDrawFileName
		, LPCTSTR lpszDefExt = NULL, DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR,
		LPCTSTR lpszFilter = NULL, LPCTSTR lpszDescr = NULL, DWORD_PTR dwData = 0);
	virtual ~GcPropertyGridFileProperty(void);
	void SetFilePathName( const CString &strFileName );
	

	inline CString GetFullFilePath() {
		return mFullFilePath;
	}

public:
	virtual void OnClickButton(CPoint point);
	
};

