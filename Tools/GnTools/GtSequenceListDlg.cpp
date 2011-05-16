// GtSequenceListDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "GnTools.h"
#include "GtSequenceListDlg.h"
#include "afxdialogex.h"


// GtSequenceListDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(GtSequenceListDlg, CDialogEx)

GtSequenceListDlg::GtSequenceListDlg(CWnd* pParent /*=NULL*/) : CDialogEx(GtSequenceListDlg::IDD, pParent)
{

}

GtSequenceListDlg::~GtSequenceListDlg()
{
}

void GtSequenceListDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, LISTCTRL_SEQUENCE, mListCtrl);
}


BEGIN_MESSAGE_MAP(GtSequenceListDlg, CDialogEx)
	ON_WM_SIZE()
	ON_BN_CLICKED(BT_ADDSEQUENCE, &GtSequenceListDlg::OnBnClickedAddsequence)
	ON_BN_CLICKED(BT_DELSEQUENCE, &GtSequenceListDlg::OnBnClickedDelsequence)
END_MESSAGE_MAP()



BOOL GtSequenceListDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	mListCtrl.InsertColumn(0, _T("인덱스"), LVCFMT_LEFT, 50);
	mListCtrl.InsertColumn(1,  _T("이름"), LVCFMT_LEFT, 150);		
	mListCtrl.SetFont( CFont::FromHandle(	(HFONT)::GetStockObject(DEFAULT_GUI_FONT) )	);
	mListCtrl.SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	mListCtrl.EnableMarkSortedColumn();
	return TRUE;
}


void GtSequenceListDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	if( mListCtrl.GetSafeHwnd() )
	{
		CRect rectClient, rectList;
		GetClientRect( rectClient );
		mListCtrl.GetWindowRect( &rectList );	
		mListCtrl.SetWindowPos( NULL, rectClient.left, rectClient.top, cx, rectList.Size().cy, SWP_NOACTIVATE | SWP_NOZORDER);
	}	
}


void GtSequenceListDlg::OnBnClickedAddsequence()
{
	CString itemName;
	itemName.Format (GnText("New Sequence %d"), mListCtrl.GetItemCount() );

	LVITEM item;	
	item.cColumns = 0;	
	item.mask = LVIF_TEXT;
	item.pszText = itemName.GetBuffer();

	int  key = mListCtrl.InsertItem( mListCtrl.GetItemCount(), itemName );
	mListCtrl.SetItemData( mListCtrl.GetItemCount(), mListCtrl.GetItemCount());
	mListCtrl.SetItemText(key, 1, itemName );
	itemName.Format ( GnText("%d"), mListCtrl.GetItemCount() );
	mListCtrl.SetItemText(key, 0, itemName );
	
}


void GtSequenceListDlg::OnBnClickedDelsequence()
{
	CList<int> selectList;

	POSITION p = mListCtrl.GetFirstSelectedItemPosition();
	while (p)
	{
		selectList.AddHead( mListCtrl.GetNextSelectedItem(p) );
	}

	while( selectList.IsEmpty() == false )
	{
		mListCtrl.DeleteItem( selectList.GetHead() );
		selectList.RemoveHead();
	}
}