// GtOpenDialog.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "GnTools.h"
#include "GtOpenDialog.h"
#include "afxdialogex.h"
#include "afxshellmanager.h"

CString GtOpenDialog::mLastPath;

IMPLEMENT_DYNAMIC(GtOpenDialog, CFileDialog)

GtOpenDialog::GtOpenDialog(BOOL bOpenFileDialog, LPCTSTR lpszDefExt, LPCTSTR lpszFileName, DWORD dwFlags,
	LPCTSTR lpszFilter, CWnd* pParentWnd, DWORD dwSize, BOOL bVistaStyle) : CFileDialog(bOpenFileDialog,
	lpszDefExt, lpszFileName, dwFlags, lpszFilter, pParentWnd, dwSize, bVistaStyle)
{
	mFilter = lpszFilter;
}

GtOpenDialog::~GtOpenDialog()
{
}

CString& GtOpenDialog::GetLastOpenPath()
{
	return mLastPath;
}

BEGIN_MESSAGE_MAP(GtOpenDialog, CFileDialog)
END_MESSAGE_MAP()

int CALLBACK GtOpenDialog::BrowseCallbackProc(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData)
{
	if (uMsg == BFFM_INITIALIZED)
	{
		GtOpenDialog* pThis = (GtOpenDialog*) lpData;
		ASSERT_VALID(pThis);

		if (pThis->mLastPath.GetLength())
		{
			::SendMessage(hwnd, BFFM_SETSELECTION, (WPARAM)TRUE, (LPARAM)pThis->mLastPath.GetBuffer());
		}
	}

	return 0;
}

INT_PTR GtOpenDialog::DoFolderDialog()
{
	TCHAR szDisplayName [MAX_PATH];

	BROWSEINFO bi;
	ZeroMemory(&bi, sizeof(bi));

	bi.lpszTitle = m_szFileTitle;
	bi.pszDisplayName = szDisplayName;
	bi.hwndOwner = NULL;
	bi.lpfn = BrowseCallbackProc;
	bi.lParam = (LPARAM) this;
	bi.pidlRoot = NULL;
	bi.ulFlags = BIF_RETURNONLYFSDIRS;
	bi.iImage = -1;

	INT_PTR ret = IDCANCEL;

	LPITEMIDLIST pidlRes = SHBrowseForFolder(&bi);
	if (pidlRes != NULL)
	{
		TCHAR szPath [MAX_PATH];
		if (SHGetPathFromIDList(pidlRes, szPath ))
		{
			ret = IDOK;
			mLastPath = szPath;
		}		
	}
	return ret;
}

INT_PTR GtOpenDialog::DoFileDialog()
{
	//(static_cast<IFileDialog*>(m_pIFileDialog))->
	//// 원래 그냥 이 클래스 DoModal 쓸려고 했는데 윈 세븐에서 에러가 난다.
	//CFileDialog file(m_bOpenFileDialog, m_ofn.lpstrDefExt, m_szFileName, m_ofn.Flags, mFilter.GetBuffer(), m_pParentWnd,
	//	m_ofn.lStructSize, m_bVistaStyle);
	INT_PTR ret  = DoModal();
	if ( ret == IDOK )
	{
		mLastPath = m_szFileName;
	}
	return ret;
	
}