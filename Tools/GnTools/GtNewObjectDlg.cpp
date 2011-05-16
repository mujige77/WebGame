// GtNewObjectDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "GnTools.h"
#include "GtNewObjectDlg.h"
#include "afxdialogex.h"


// GtNewObjectDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(GtNewObjectDlg, CDialogEx)

GtNewObjectDlg::GtNewObjectDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(GtNewObjectDlg::IDD, pParent)
{

}

GtNewObjectDlg::~GtNewObjectDlg()
{
}

void GtNewObjectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDT_NEWOBJECTNAME, mObjectNameEdt);	
}


BEGIN_MESSAGE_MAP(GtNewObjectDlg, CDialogEx)
END_MESSAGE_MAP()


// GtNewObjectDlg 메시지 처리기입니다.


void GtNewObjectDlg::OnOK()
{
	mObjectNameEdt.GetWindowText( mObjectName );
	CDialogEx::OnOK();
}


BOOL GtNewObjectDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();		
	return TRUE;  // return TRUE unless you set the focus to a control
}
