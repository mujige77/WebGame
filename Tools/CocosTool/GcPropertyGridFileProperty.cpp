#include "StdAfx.h"
#include "GcPropertyGridFileProperty.h"
#define AFX_PROP_HAS_BUTTON 0x0002

GcPropertyGridFileProperty::GcPropertyGridFileProperty(const CString& strName, const CString& strFolderName
	, bool bDrawFileName , DWORD_PTR dwData, LPCTSTR lpszDescr) : GcPropertyGridProperty( strName
	, COleVariant((LPCTSTR)strFolderName), lpszDescr, dwData ), m_bIsFolder(TRUE), mDrawFileName(bDrawFileName)
	, mUserDescr(lpszDescr)
{
	m_dwFlags = AFX_PROP_HAS_BUTTON;
	AllowEdit( FALSE );
}

GcPropertyGridFileProperty::GcPropertyGridFileProperty(const CString& strName, BOOL bOpenFileDialog, const CString& strFileName
	, bool bDrawFileName, LPCTSTR lpszDefExt, DWORD dwFlags, LPCTSTR lpszFilter, LPCTSTR lpszDescr, DWORD_PTR dwData)
	: GcPropertyGridProperty(strName, COleVariant((LPCTSTR)strFileName), lpszDescr, dwData)
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

GcPropertyGridFileProperty::~GcPropertyGridFileProperty(void)
{
}

void GcPropertyGridFileProperty::OnClickButton(CPoint /*point*/)
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
		CFileDialog dlg(m_bOpenFileDialog, m_strDefExt, strPath, m_dwFileOpenFlags, m_strFilter, m_pWndList);
		if (dlg.DoModal() == IDOK)
		{
			bUpdate = TRUE;
			SetFilePathName( dlg.GetPathName() );
		}
	}
	
	if (bUpdate)
	{
		mUpdateEvent.EmitSignal( this );
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

void GcPropertyGridFileProperty::SetFilePathName(const CString &strFileName)
{
	if( mDrawFileName == false )
	{
		SetValue( strFileName.GetString() );
		mFullFilePath = strFileName;
		return;
	}

	
	if( strFileName.Find( _T( ":" ) ) == -1 )
	{
		GtConvertString fullFilePath = GnSystem::GetWorkDirectory();
		fullFilePath += strFileName;
		mFullFilePath = fullFilePath.c_str();
	}
	else
	{
		mFullFilePath = strFileName;
	}
	
	m_strDescr = mUserDescr + _T( "\n" ) + mFullFilePath;		

	gtchar filePath[GN_MAX_PATH] = { 0, };
	GnVerify( GnPath::GetFileName( mFullFilePath.GetString(), filePath, GN_MAX_PATH, true ) );
	m_varValue = filePath;

	Redraw();
}