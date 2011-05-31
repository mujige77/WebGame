// GcCreateCollisionDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "CocosTool.h"
#include "GcCreateCollisionDlg.h"
#include "afxdialogex.h"


// GcCreateCollisionDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(GcCreateCollisionDlg, CDialogEx)

GcCreateCollisionDlg::GcCreateCollisionDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(GcCreateCollisionDlg::IDD, pParent), mSelectedCollisionType(0)
{

}

GcCreateCollisionDlg::~GcCreateCollisionDlg()
{
}

void GcCreateCollisionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CB_COLLISIONTYPE, mCollisionType);
	DDX_CBIndex(pDX, IDC_CB_COLLISIONTYPE, mSelectedCollisionType);
}


BEGIN_MESSAGE_MAP(GcCreateCollisionDlg, CDialogEx)
END_MESSAGE_MAP()


// GcCreateCollisionDlg 메시지 처리기입니다.


BOOL GcCreateCollisionDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	mCollisionType.SetCurSel(1);
	return TRUE;  // return TRUE unless you set the focus to a control
}
