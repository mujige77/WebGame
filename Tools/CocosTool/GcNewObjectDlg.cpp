// GcNewObjectDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "CocosTool.h"
#include "GcNewObjectDlg.h"
#include "afxdialogex.h"


// GcNewObjectDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(GcNewObjectDlg, CDialogEx)

	GcNewObjectDlg::GcNewObjectDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(GcNewObjectDlg::IDD, pParent)
{

}

GcNewObjectDlg::~GcNewObjectDlg()
{
}

void GcNewObjectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDT_NEWOBJECTNAME, mObjectNameEdt);	
}


BEGIN_MESSAGE_MAP(GcNewObjectDlg, CDialogEx)
END_MESSAGE_MAP()


// GcNewObjectDlg 메시지 처리기입니다.


void GcNewObjectDlg::OnOK()
{
	mObjectNameEdt.GetWindowText( mObjectName );
	CDialogEx::OnOK();
}


BOOL GcNewObjectDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();		
	return TRUE;  // return TRUE unless you set the focus to a control
}
