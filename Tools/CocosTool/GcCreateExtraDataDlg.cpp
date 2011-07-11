// GcCreateExtraDataDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "CocosTool.h"
#include "GcCreateExtraDataDlg.h"
#include "afxdialogex.h"


// GcCreateExtraDataDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(GcCreateExtraDataDlg, CDialogEx)

GcCreateExtraDataDlg::GcCreateExtraDataDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(GcCreateExtraDataDlg::IDD, pParent)
{

}

GcCreateExtraDataDlg::~GcCreateExtraDataDlg()
{
}

void GcCreateExtraDataDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CB_EXTRADATATYPE, mComboExtraDataType);
	DDX_CBIndex(pDX, IDC_CB_EXTRADATATYPE, mSelectedExtraDataType);
}


BEGIN_MESSAGE_MAP(GcCreateExtraDataDlg, CDialogEx)
END_MESSAGE_MAP()


BOOL GcCreateExtraDataDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	for( gtuint i = 0; i < GExtraData::EXTRA_DATA_MAX; i++ )
	{
		mComboExtraDataType.AddString( gsExtraType[i] );
	}
	
	mComboExtraDataType.SetCurSel( 0 );
	return TRUE;  // return TRUE unless you set the focus to a control
}
