// GcEditorPropertyPage.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "CocosTool.h"
#include "GcEditorPropertyPage.h"


// GcEditorPropertyPage

IMPLEMENT_DYNAMIC(GcEditorPropertyPage, CMFCPropertyPage)

GcEditorPropertyPage::GcEditorPropertyPage() : mModifyMode(0)
{

}

GcEditorPropertyPage::GcEditorPropertyPage(UINT nIDTemplate, UINT nIDCaption /*= 0*/) 
	: CMFCPropertyPage( nIDTemplate, nIDCaption ), mModifyMode(0)
{

}

GcEditorPropertyPage::GcEditorPropertyPage(LPCTSTR lpszTemplateName, UINT nIDCaption /*= 0*/) 
	: CMFCPropertyPage( lpszTemplateName, nIDCaption ), mModifyMode(0)
{

}
GcEditorPropertyPage::~GcEditorPropertyPage()
{
}


BEGIN_MESSAGE_MAP(GcEditorPropertyPage, CMFCPropertyPage)
END_MESSAGE_MAP()

// GcEditorPropertyPage 메시지 처리기입니다.

bool GcEditorPropertyPage::CheckEnableButton()
{
	bool enableButton = true;
	return enableButton;
}

void GcEditorPropertyPage::CheckEnableOKButton()
{
	NMHDR msg;
	msg.code = GTMG_CHECKENABLE_OKBUTTON;
	msg.hwndFrom = GetSafeHwnd();
	msg.idFrom = GetDlgCtrlID();

	GetParent()->SendNotifyMessage( WM_NOTIFY, GTMG_CHECKENABLE_OKBUTTON, (LPARAM)&msg );
}
