// PropTreeInfo.cpp : implementation file
//
//  Copyright (C) 1998-2001 Scott Ramsay
//	sramsay@gonavi.com
//	http://www.gonavi.com
//
//  This material is provided "as is", with absolutely no warranty expressed
//  or implied. Any use is at your own risk.
// 
//  Permission to use or copy this software for any purpose is hereby granted 
//  without fee, provided the above notices are retained on all copies.
//  Permission to modify the code and to distribute modified code is granted,
//  provided the above notices are retained, and a notice that the code was
//  modified is included with the above copyright notice.
// 
//	If you use this code, drop me an email.  I'd like to know if you find the code
//	useful.

#include "stdafx.h"
#include "PropTree.h"
#include "PropTreeInfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPropTreeInfo

CPropTreeInfo::CPropTreeInfo() : m_pProp(NULL)
{
	m_pInfo = NULL;
}

CPropTreeInfo::~CPropTreeInfo()
{
	if ( m_pInfo )
	{
		delete m_pInfo;
		m_pInfo = NULL;
	}
}

BEGIN_MESSAGE_MAP(CPropTreeInfo, CStatic)
	//{{AFX_MSG_MAP(CPropTreeInfo)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CPropTreeInfo::OnPaint() 
{


	CPaintDC dc(this);
	CRect rc;

	GetClientRect(rc);

	dc.SelectObject(GetSysColorBrush(COLOR_BTNFACE));
	if ( m_pInfo && m_pInfo->IsWindowVisible() )	
		return;
		
	dc.PatBlt(rc.left, rc.top, rc.Width(), rc.Height(), PATCOPY);

	dc.DrawEdge(&rc, BDR_SUNKENOUTER, BF_RECT);
	rc.DeflateRect(4, 4);

	ASSERT(m_pProp!=NULL);

	CPropTreeItem* pItem = m_pProp->GetFocusedItem();

	if (!m_pProp->IsWindowEnabled())
		dc.SetTextColor(GetSysColor(COLOR_GRAYTEXT));
	else
		dc.SetTextColor(GetSysColor(COLOR_BTNTEXT));

	dc.SetBkMode(TRANSPARENT);
	dc.SelectObject(m_pProp->GetBoldFont());

	CString txt;

	if (!pItem)
		txt=_T("님하즐");
	else
		txt = pItem->GetLabelText();

	CRect ir;
	ir = rc;

	// draw label
	dc.DrawText(txt, &ir, DT_SINGLELINE|DT_CALCRECT);
	dc.DrawText(txt, &ir, DT_SINGLELINE);

	ir.top = ir.bottom;
	ir.bottom = rc.bottom;
	ir.right = rc.right;

	if (pItem)
		txt = pItem->GetInfoText();
	
	dc.SelectObject(m_pProp->GetNormalFont());
	dc.DrawText(txt, &ir, DT_WORDBREAK);
}

CPropTreeDlgInfo::CPropTreeDlgInfo()
{
}

CPropTreeDlgInfo::~CPropTreeDlgInfo(void)
{
}
BEGIN_MESSAGE_MAP(CPropTreeDlgInfo, CWnd)
	ON_WM_PAINT()
END_MESSAGE_MAP()
/////////////////////////////////////////////////////////////////////////////
// CPropTreeInfo message handlers

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
