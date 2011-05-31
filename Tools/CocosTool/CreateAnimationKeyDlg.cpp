// CreateAnimationKeyDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "CocosTool.h"
#include "CreateAnimationKeyDlg.h"
#include "afxdialogex.h"

IMPLEMENT_DYNAMIC(CreateAnimationKeyDlg, CDialogEx)
	CreateAnimationKeyDlg::CreateAnimationKeyDlg(CWnd* pParent)
	: CDialogEx(CreateAnimationKeyDlg::IDD, pParent) , mSelectString(_T(""))
{
}

CreateAnimationKeyDlg::~CreateAnimationKeyDlg()
{
}

void CreateAnimationKeyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CB_ANIMATIONKEYTYPE, mAnimationKeyType);
	DDX_CBString(pDX, IDC_CB_ANIMATIONKEYTYPE, mSelectString);
	DDX_CBIndex(pDX, IDC_CB_ANIMATIONKEYTYPE, mSelectType);
}
BEGIN_MESSAGE_MAP(CreateAnimationKeyDlg, CDialogEx)
END_MESSAGE_MAP()

// CreateAnimationKeyDlg 메시지 처리기입니다.


BOOL CreateAnimationKeyDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	mAnimationKeyType.SetCurSel( 0 );

	return TRUE;
}
