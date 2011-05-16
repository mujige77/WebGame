// GtTasksPane.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "GnTools.h"
#include "GtTasksPane.h"


// GtTasksPane

IMPLEMENT_DYNAMIC(GtTasksPane, CMFCTasksPane)

GtTasksPane::GtTasksPane()
{

}

GtTasksPane::~GtTasksPane()
{
}


BEGIN_MESSAGE_MAP(GtTasksPane, CMFCTasksPane)
	ON_WM_CREATE()
END_MESSAGE_MAP()



// GtTasksPane 메시지 처리기입니다.





int GtTasksPane::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMFCTasksPane::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.

	return 0;
}

void GtTasksPane::SetVisibleCaptionBar(bool bShow)
{
	m_bHasGripper = false;
}