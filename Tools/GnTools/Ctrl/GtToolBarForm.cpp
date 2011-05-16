// GtToolBarForm.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "GnTools.h"
#include "GtToolBarForm.h"

#include <afxdockablepane.h>
// GtToolBarForm

IMPLEMENT_DYNAMIC(GtToolBarForm, CDockablePane)

GtToolBarForm::GtToolBarForm() : mpMainWnd(NULL)
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
	
	mChildBeginTop = rectClient.top;
	if( mToolBar.GetSafeHwnd() )
	{
		int cyTlb = mToolBar.CalcFixedLayout(FALSE, TRUE).cy;
		mToolBar.SetWindowPos(NULL, rectClient.left, rectClient.top,
			rectClient.Width(), cyTlb, SWP_NOACTIVATE | SWP_NOZORDER);
		mChildBeginTop += cyTlb;
	}

	if( mpMainWnd && mpMainWnd->GetSafeHwnd() )
	{
		int setBottom = rectClient.Height() - ( mChildBeginTop - rectClient.top );
		mpMainWnd->SetWindowPos(NULL, rectClient.left, mChildBeginTop,
			rectClient.Width(), setBottom, SWP_NOACTIVATE | SWP_NOZORDER);
	}
}

void GtToolBarForm::SetVisibleCaptionBar(bool bShow)
{
	m_bHasGripper = false;
}


LRESULT GtToolBarForm::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	if( WM_NOTIFY == message )
	{
		ReciveNotiyfiMessage(wParam, lParam);
	}
	return CDockablePane::WindowProc(message, wParam, lParam);
}