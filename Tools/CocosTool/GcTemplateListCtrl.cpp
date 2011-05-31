// GcTemplateListCtrl.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "CocosTool.h"
#include "GcTemplateListCtrl.h"


// GcTemplateListCtrl

IMPLEMENT_DYNAMIC(GcTemplateListCtrl, CListCtrl)

GcTemplateListCtrl::GcTemplateListCtrl() : mSelectedItem(-1)
{

}

GcTemplateListCtrl::~GcTemplateListCtrl()
{
}


BEGIN_MESSAGE_MAP(GcTemplateListCtrl, CListCtrl)
	ON_NOTIFY_REFLECT(NM_CLICK, &GcTemplateListCtrl::OnNMClick)
END_MESSAGE_MAP()



// GcTemplateListCtrl 메시지 처리기입니다.




void GcTemplateListCtrl::OnNMClick(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	*pResult = 0;
	mSelectedItem = pNMItemActivate->iItem;
	mSelectedItemText = GetItemText( pNMItemActivate->iItem, 0 );
}
