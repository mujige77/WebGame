#include "StdAfx.h"
#include "GtPropertyGridFileProperty.h"
#define AFX_PROP_HAS_BUTTON 0x0002

GtPropertyGridFileProperty::GtPropertyGridFileProperty(const CString& strName, const CString& strFolderName
	, bool bDrawFileName , DWORD_PTR dwData, LPCTSTR lpszDescr) : GtPropertyGridProperty( strName
	, COleVariant((LPCTSTR)strFolderName), lpszDescr, dwData ), m_bIsFolder(TRUE), mDrawFileName(bDrawFileName)
	, mUserDescr(lpszDescr)
{
	m_dwFlags = AFX_PROP_HAS_BUTTON;
	AllowEdit( FALSE );
}

GtPropertyGridFileProperty::GtPropertyGridFileProperty(const CString& strName, BOOL bOpenFileDialog, const CString& strFileName
	, bool bDrawFileName, LPCTSTR lpszDefExt, DWORD dwFlags, LPCTSTR lpszFilter, LPCTSTR lpszDescr, DWORD_PTR dwData)
	: GtPropertyGridProperty(strName, COleVariant((LPCTSTR)strFileName), lpszDescr, dwData)
	, m_bOpenFileDialog(bOpenFileDialog), mDrawFileName(bDrawFileName), m_dwFileOpenFlags(dwFlags)
	, mUserDescr(lpszDescr)
{
	m_dwFlags = AFX_PROP_HAS_BUTTON;
	m_strDefExt = lpszDefExt == NULL ? _T("") : lpszDefExt;
	m_strFilter = lpszFilter == NULL ? _T("") : lpszFilter;
	m_bIsFolder  = FALSE;
	if( bDrawFileName && strFileName.GetLength() != 0 )
	{
		SetFilePathName(strFileName);
	}
	AllowEdit( FALSE );
}

GtPropertyGridFileProperty::~GtPropertyGridFileProperty(void)
{
}

void GtPropertyGridFileProperty::OnClickButton(CPoint /*point*/)
{
	ASSERT_VALID(this);
	ASSERT_VALID(m_pWndList);
	ASSERT_VALID(m_pWndInPlace);
	ASSERT(::IsWindow(m_pWndInPlace->GetSafeHwnd()));

	m_bButtonIsDown = TRUE;
	//Redraw();	
	CString strPath = m_varValue.bstrVal;
	BOOL bUpdate = FALSE;
	
	if (m_bIsFolder)
	{
	}
	else
	{
		GtOpenDialog dlg(m_bOpenFileDialog, m_strDefExt, strPath, m_dwFileOpenFlags, m_strFilter, m_pWndList);
		if (dlg.DoModal() == IDOK)
		{
			bUpdate = TRUE;
			SetFilePathName( dlg.GetPathName() );
		}
	}

	if (bUpdate)
	{
		if (m_pWndInPlace != NULL)
		{
			m_pWndInPlace->SetWindowText(strPath);
		}
	}

	m_bButtonIsDown = FALSE;
	Redraw();

	if (m_pWndInPlace != NULL)
	{
		m_pWndInPlace->SetFocus();
	}
	else
	{
		m_pWndList->SetFocus();
	}
}

void GtPropertyGridFileProperty::SetFilePathName(const CString &strFileName)
{
	if( mDrawFileName == false )
	{
		SetValue( strFileName.GetString() );
		mFullFilePath = strFileName;
		return;
	}
	GtCString fullFilePath = GnSystem::GetWorkDirectory();
	fullFilePath += strFileName;
	mFullFilePath = fullFilePath;
	m_strDescr = mUserDescr + _T( "\n" ) + mFullFilePath;		

	gtchar filePath[GN_MAX_PATH] = { 0, };
	GnVerify( GnPath::GetFileName( mFullFilePath.GetString(), filePath, GN_MAX_PATH, true ) );
	m_varValue = filePath;

	Redraw();
}