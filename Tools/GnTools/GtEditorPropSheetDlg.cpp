// GtEditorPropSheetDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "GnTools.h"
#include "GtEditorPropSheetDlg.h"
#include "afxdialogex.h"


// GtEditorPropSheetDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(GtEditorPropSheetDlg, CDialogEx)

GtEditorPropSheetDlg::GtEditorPropSheetDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(GtEditorPropSheetDlg::IDD, pParent)
{

}

GtEditorPropSheetDlg::~GtEditorPropSheetDlg()
{
}

void GtEditorPropSheetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(GtEditorPropSheetDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &GtEditorPropSheetDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &GtEditorPropSheetDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// GtEditorPropSheetDlg 메시지 처리기입니다.


BOOL GtEditorPropSheetDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	CRect rectpRrop;	
	mPropList.Create(WS_VISIBLE | WS_CHILD, rectpRrop, this, 2);
	mPropList.EnableHeaderCtrl(FALSE);
	mPropList.EnableDescriptionArea();
	mPropList.SetVSDotNetLook();
	mPropList.MarkModifiedProperties();
	
	mEditorSheet.m_psh.dwFlags = PSH_DEFAULT |  PSH_PROPSHEETPAGE;
	mEditorSheet.Create(this, WS_CHILD | WS_VISIBLE, PSH_DEFAULT);
	mEditorSheet.ModifyStyleEx (0, WS_EX_CONTROLPARENT);
	mEditorSheet.ModifyStyle( 0, WS_TABSTOP );
	mEditorSheet.EnableStackedTabs(FALSE); 	

	AdjustLayout();

	CWnd* button = GetDlgItem(IDOK);
	if( button )
		button->EnableWindow( false );
	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void GtEditorPropSheetDlg::AdjustLayout()
{
	CRect rectSheet, rectClient, rectBtn;

	GetClientRect( rectClient );
	CWnd* button = mEditorSheet.GetDlgItem (IDOK);
	ASSERT (button);
	button->GetWindowRect( &rectBtn );
	mEditorSheet.GetWindowRect( &rectSheet );

	rectSheet.bottom=rectBtn.top - 4; // 버튼 간격 땜에 마이너스 함
	rectSheet.right=rectSheet.right - 10;
	mEditorSheet.MoveWindow( rectSheet );

	mEditorSheet.GetWindowRect( rectSheet );	
	mEditorSheet.SetWindowPos( NULL, 0, 0, rectSheet.Size().cx, rectSheet.Size().cy
		, SWP_NOACTIVATE | SWP_NOZORDER );

	int cxProp = 300;
	int ctrlOffset = 3;	
	mPropList.SetWindowPos( NULL, rectSheet.Width()+ctrlOffset, rectClient.top, cxProp, rectSheet.Size().cy
		, SWP_NOACTIVATE | SWP_NOZORDER );

	int btnOffsetY = 0;
	button = GetDlgItem( IDOK );
	if( button ) 
	{
		button->GetWindowRect( &rectBtn );
		btnOffsetY = rectBtn.Height() * 3;
	}

	SetWindowPos( NULL, 0, 0, rectSheet.Size().cx+cxProp+5 + ctrlOffset * 2
		, rectSheet.Size().cy + btnOffsetY
		, SWP_NOACTIVATE | SWP_NOZORDER );	

	button = GetDlgItem( IDOK );
	button->GetWindowRect( &rectBtn );
	GetClientRect( rectClient );
	int btnCtrlOffset = 5;
	int buttonTop = rectClient.bottom - ( rectBtn.Height() + rectBtn.Height() / 2 );
	int okButtonLeft = rectClient.right - (int)(rectBtn.Width() * 2.5);

	button->SetWindowPos( NULL, okButtonLeft, buttonTop, rectBtn.Width(), rectBtn.Height()
		, SWP_NOACTIVATE | SWP_NOSIZE | SWP_NOZORDER );

	button = GetDlgItem( IDCANCEL );
	button->GetWindowRect( &rectBtn );
	int cancelButtonLeft = rectClient.right - (int)(rectBtn.Width() * 1.5) + btnCtrlOffset;
	button->SetWindowPos( NULL, cancelButtonLeft, buttonTop, rectBtn.Width(), rectBtn.Height()
		, SWP_NOACTIVATE | SWP_NOSIZE | SWP_NOZORDER );

	CenterWindow();

	mEditorSheet.RemoveAllButton(); // 버튼 필요 없으니 삭제
}

void GtEditorPropSheetDlg::OnBnClickedOk()
{
	for( int i = 0 ; i < mEditorSheet.GetPageCount() ; i++ )
	{
		CPropertyPage* page = mEditorSheet.GetPage( i );
		page->OnOK();
	}
	CDialogEx::OnOK();
}

void GtEditorPropSheetDlg::OnBnClickedCancel()
{
	for( int i = 0 ; i < mEditorSheet.GetPageCount() ; i++ )
	{
		CPropertyPage* page = mEditorSheet.GetPage( i );
		page->OnCancel();
	}
	CDialogEx::OnCancel();
}
