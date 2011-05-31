// GtEditorPropSheet.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "CocosTool.h"
#include "GtEditorPropSheet.h"


// GtEditorPropSheet

IMPLEMENT_DYNAMIC(GtEditorPropSheet, CMFCPropertySheet)

GtEditorPropSheet::GtEditorPropSheet(CWnd* pParent) : CMFCPropertySheet( _T("ObjectEditor"), pParent )
{
	BOOL b32BitIcons = TRUE;

	if (afxGlobalData.m_nBitsPerPixel < 16)
	{
		b32BitIcons = FALSE;
	}
	SetLook(CMFCPropertySheet::PropSheetLook_List);
	AddPage( &mSequenceMainPage );
	AddPage( &mSequenceTexturepage );		
}

GtEditorPropSheet::~GtEditorPropSheet()
{
}


BEGIN_MESSAGE_MAP(GtEditorPropSheet, CMFCPropertySheet)
END_MESSAGE_MAP()



// GtEditorPropSheet 메시지 처리기입니다.




BOOL GtEditorPropSheet::OnInitDialog()
{
	BOOL bResult = CMFCPropertySheet::OnInitDialog();
	return bResult;
}

void GtEditorPropSheet::SetObject(GtObject* pObject, Gt2DSequence* pSequence)
{
	for( int i = 0 ; i < GetPageCount() ; i++ )
	{
		GcEditorPropertyPage* page = (GcEditorPropertyPage*)GetPage( i );
		page->SetSequence( pSequence );
		page->SetObject( pObject );
	}
}


void GtEditorPropSheet::SetModifyMode(int mode)
{
	for( int i = 0 ; i < GetPageCount() ; i++ )
	{
		GcEditorPropertyPage* page = (GcEditorPropertyPage*)GetPage( i );
		page->SetModifyMode( (bool)mode );
	}
}

void GtEditorPropSheet::RemoveAllButton()
{
	CWnd* pApplyButton = GetDlgItem (IDOK);
	ASSERT (pApplyButton);
	pApplyButton->DestroyWindow();

	pApplyButton = GetDlgItem (IDCANCEL);
	ASSERT (pApplyButton);
	pApplyButton->DestroyWindow();

	pApplyButton = GetDlgItem (ID_APPLY_NOW);
	ASSERT (pApplyButton);
	pApplyButton->DestroyWindow();
}

BOOL GtEditorPropSheet::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	NMHDR* pnmh = (LPNMHDR) lParam;

	switch( pnmh->code )
	{
	case GTMG_CHECKENABLE_OKBUTTON:
		{
			CheckEnableOKButton();
		}
		break;
	case TCN_SELCHANGE:
		{
			CPropertyPage* page = GetActivePage();
			if( page->GetSafeHwnd() == mSequenceTexturepage.GetSafeHwnd() )
			{
				ChangeTexturePage();
			}
		}
		break;
	}

	return CMFCPropertySheet::OnNotify(wParam, lParam, pResult);
}

void GtEditorPropSheet::ChangeTexturePage()
{
	//mSequenceTexturepage.
}

void GtEditorPropSheet::CheckEnableOKButton()
{
	for( int i = 0 ; i < GetPageCount() ; i++ )
	{
		GcEditorPropertyPage* page = (GcEditorPropertyPage*)GetPage( i );
		if( page->CheckEnableButton() == false )
		{
			EnableOKButton( false );
			return;
		}
	}

	EnableOKButton( true );
}

void GtEditorPropSheet::EnableOKButton(bool bEnable)
{
	GnAssert( GetParent() );
	CWnd* pApplyButton = GetParent()->GetDlgItem(IDOK);
	ASSERT (pApplyButton);
	pApplyButton->EnableWindow( bEnable );
}