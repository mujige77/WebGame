// GtToolBarForm.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "GtToolLib.h"
#include "GtToolBarForm.h"


// GtToolBarForm

IMPLEMENT_DYNAMIC(GtToolBarForm, CDockablePane)

GtToolBarForm::GtToolBarForm()
{

}

GtToolBarForm::~GtToolBarForm()
{
}


BEGIN_MESSAGE_MAP(GtToolBarForm, CDockablePane)
	ON_WM_SIZE()
END_MESSAGE_MAP()



void GtToolBarForm::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);

	CRect rectClient,rectCombo;
	GetClientRect(rectClient);

	if( mToolBar.GetSafeHwnd() )
	{
		int cyTlb = mToolBar.CalcFixedLayout(FALSE, TRUE).cy;
		mToolBar.SetWindowPos(NULL, rectClient.left, rectClient.top,
			rectClient.Width(), cyTlb, SWP_NOACTIVATE | SWP_NOZORDER);
	}
}
