// ./Ctrl/GtTemplateTasksPane.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "GnTools.h"
#include "./Ctrl/GtTemplateTasksPane.h"


// GtTemplateTasksPane

IMPLEMENT_DYNAMIC(GtTemplateTasksPane, GtTasksPane)

GtTemplateTasksPane::GtTemplateTasksPane()
{

}

GtTemplateTasksPane::~GtTemplateTasksPane()
{
}


BEGIN_MESSAGE_MAP(GtTemplateTasksPane, GtTasksPane)
	ON_WM_CREATE()
END_MESSAGE_MAP()



// GtTemplateTasksPane 메시지 처리기입니다.
int GtTemplateTasksPane::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (GtTasksPane::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	//EnableNavigationToolbar (FALSE);
	//EnableWrapLabels (FALSE);
	//EnableOffsetCustomControls (FALSE);


	DWORD defaultStyle = WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_NOALIGN;
	if (!mTemplateList.Create(_T("FDSF"), this, CRect(0, 0, 0, 0), TRUE, ID_CTRL_TEMPLATELIST,
		defaultStyle ))
	{
		TRACE0("속성 창을 만들지 못했습니다.\n");
		return FALSE; // 만들지 못했습니다.
	}

	int groupIndex = AddGroup (_T("Template List"), FALSE, TRUE);
	AddWindow (groupIndex, mTemplateList.GetSafeHwnd (), 300);

	SetVisibleCaptionBar(true);
	return 0;
}
