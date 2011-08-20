#include "StdAfx.h"
#include ".\proptreedlginfo.h"

CPropTreeDlgInfo::CPropTreeDlgInfo(void)
{
}

CPropTreeDlgInfo::~CPropTreeDlgInfo(void)
{
}
BEGIN_MESSAGE_MAP(CPropTreeDlgInfo, CDialog)
	ON_WM_PAINT()
END_MESSAGE_MAP()
/////////////////////////////////////////////////////////////////////////////
// CPropTreeInfo message handlers

void CPropTreeDlgInfo::SetPropOwner(CPropTree* pProp)
{
	m_pProp = pProp;
}
void CPropTreeDlgInfo::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	// 그리기 메시지에 대해서는 CPropertyPage::OnPaint()을(를) 호출하지 마십시오.
	if ( this->GetSafeHwnd() != NULL )
	{
		CBrush test;
		CRect  rect;
		test.CreateSolidBrush(RGB(0xDD, 0x87, 0xFA));
		GetClientRect(&rect);
		dc.SelectObject(&test);
		dc.Rectangle(-1,-1,rect.Width()+1,rect.Height()+1);
		dc.SetBkMode(TRANSPARENT);

	}
}
