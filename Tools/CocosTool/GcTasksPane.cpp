// GcTasksPane.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "CocosTool.h"
#include "GcTasksPane.h"


// GcTasksPane

IMPLEMENT_DYNAMIC(GcTasksPane, CMFCTasksPane)

GcTasksPane::GcTasksPane()
{

}

GcTasksPane::~GcTasksPane()
{
}


BEGIN_MESSAGE_MAP(GcTasksPane, CMFCTasksPane)
	ON_WM_CREATE()
END_MESSAGE_MAP()



// GcTasksPane 메시지 처리기입니다.





int GcTasksPane::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMFCTasksPane::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.

	return 0;
}

void GcTasksPane::SetVisibleCaptionBar(bool bShow)
{
	m_bHasGripper = false;
}