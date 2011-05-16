// GtPropertyPage.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "GnTools.h"
#include "GtPropertyPage.h"


// GtPropertyPage

IMPLEMENT_DYNAMIC(GtPropertyPage, CMFCPropertyPage)

GtPropertyPage::GtPropertyPage() : mModifyMode(0)
{

}

GtPropertyPage::GtPropertyPage(UINT nIDTemplate, UINT nIDCaption /*= 0*/) : CMFCPropertyPage( nIDTemplate, nIDCaption )
		, mModifyMode(0)
{

}

GtPropertyPage::GtPropertyPage(LPCTSTR lpszTemplateName, UINT nIDCaption /*= 0*/) 
	: CMFCPropertyPage( lpszTemplateName, nIDCaption ), mModifyMode(0)
{

}
GtPropertyPage::~GtPropertyPage()
{
}


BEGIN_MESSAGE_MAP(GtPropertyPage, CMFCPropertyPage)
END_MESSAGE_MAP()

// GtPropertyPage 메시지 처리기입니다.

bool GtPropertyPage::CheckEnableButton()
{
	bool enableButton = false;
	for( gtuint i = 0 ; i < mpSequence->GetTimeControllerCount() ; i++ )
	{
		GtTimeController* ctlr =mpSequence->GetTimeController( i );
		if( ctlr->ExistSaveData() )
		{
			enableButton = true;
			break;
		}		
	}
	return enableButton;
}

void GtPropertyPage::CheckEnableOKButton()
{
	NMHDR msg;
	msg.code = GTMG_CHECKENABLE_OKBUTTON;
	msg.hwndFrom = GetSafeHwnd();
	msg.idFrom = GetDlgCtrlID();

	GetParent()->SendNotifyMessage( WM_NOTIFY, GTMG_CHECKENABLE_OKBUTTON, (LPARAM)&msg );
}
