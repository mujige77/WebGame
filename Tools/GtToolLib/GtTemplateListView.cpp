// GtTemplateListView.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "GtToolLib.h"
#include "GtTemplateListView.h"


// GtTemplateListView

IMPLEMENT_DYNAMIC(GtTemplateListView, GtToolBarForm)

GtTemplateListView::GtTemplateListView()
{

}

GtTemplateListView::~GtTemplateListView()
{
}


BEGIN_MESSAGE_MAP(GtTemplateListView, GtToolBarForm)
END_MESSAGE_MAP()



// GtTemplateListView 메시지 처리기입니다.




int GtTemplateListView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	//AFX_MANAGE_STATE(AfxGetStaticModuleState());
	//afxGlobalData.Is32BitIcons() ? IDB_AFXBARRES_NEW32 : IDB_AFXBARRES_NEW
	mToolBar.Create(this, AFX_DEFAULT_TOOLBAR_STYLE, IDR_TEMPLATELISTVIEWTOOLBAR);
	mToolBar.LoadToolBar(IDR_TEMPLATELISTVIEWTOOLBAR, 0, 0, TRUE);
	mToolBar.CleanUpLockedImages();	
	mToolBar.LoadBitmap(IDR_TEMPLATELISTVIEWTOOLBAR, 0, 0, TRUE);	
	mToolBar.SetPaneStyle(mToolBar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);
	mToolBar.SetPaneStyle(mToolBar.GetPaneStyle() & ~(CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));
	mToolBar.SetOwner(this);

	// 모든 명령은 부모 프레임이 아닌 이 컨트롤을 통해 라우팅됩니다.
	mToolBar.SetRouteCommandsViaFrame(FALSE);

	return 0;
}
