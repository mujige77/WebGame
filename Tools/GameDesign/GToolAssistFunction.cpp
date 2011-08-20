#include "StdAfx.h"
#include "GToolAssistFunction.h"
#include "MainFrm.h"
#include "ChildFrm.h"
#include "GameDesignView.h"

CGameDesignView* GetActiveView()
{
	CMainFrame*	 pActivFrame = (CMainFrame*)AfxGetMainWnd();
	CChildFrame* childFrame =  (CChildFrame*) pActivFrame->GetActiveFrame();
	if( childFrame )
	{
		CView* view = (CView*)childFrame->GetActiveView();
		CGameDesignView* designView = (CGameDesignView*)view->GetParent()->GetParent();
		if( designView )
			return designView;
	}
	return NULL;
}