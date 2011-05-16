// GtPropertyGridCtrl.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "GnTools.h"
#include "GtPropertyGridCtrl.h"
#include "GtPropertyGridMultiFileProperty.h"
#include "GtPropertyGridProperty.h"


// GtPropertyGridCtrl

IMPLEMENT_DYNAMIC(GtPropertyGridCtrl, CMFCPropertyGridCtrl)

BEGIN_MESSAGE_MAP(GtPropertyGridCtrl, CMFCPropertyGridCtrl)
	ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()


GtPropertyGridCtrl::GtPropertyGridCtrl()
{
}

GtPropertyGridCtrl::~GtPropertyGridCtrl()
{
}


BOOL GtPropertyGridCtrl::OnDrawProperty(CDC* pDC, CMFCPropertyGridProperty* pProp) const
{
	CMFCPropertyGridCtrl::OnDrawProperty(pDC, pProp);

	GtPropertyGridMultiFileProperty* gtProp = dynamic_cast<GtPropertyGridMultiFileProperty*>(pProp);
	if( gtProp )	
		gtProp->DrawButton(pDC);
	else
	{
		GtPropertyGridProperty*  gtGridProp = dynamic_cast<GtPropertyGridProperty*>(pProp);
		if( gtGridProp )
			gtGridProp->DrawButton(pDC);
	}
	
	return TRUE;
}

BOOL GtPropertyGridCtrl::EditItem(CMFCPropertyGridProperty* pProp, LPPOINT lptClick)
{
	GtPropertyGridMultiFileProperty* gtProp = dynamic_cast<GtPropertyGridMultiFileProperty*>(pProp);
	if( gtProp )
	{		
		pProp->OnEdit(lptClick);
		return true;
	}
	else
	{
		GtPropertyGridProperty*  gtGridProp = dynamic_cast<GtPropertyGridProperty*>(pProp);
		if( gtGridProp )
		{
			gtGridProp->OnEdit(lptClick);
			return true;
		}
	}

	return CMFCPropertyGridCtrl::EditItem(pProp, lptClick);
}

void GtPropertyGridCtrl::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	if (m_pSel == NULL)
		return;
	
	GtPropertyGridMultiFileProperty* gtProp = dynamic_cast<GtPropertyGridMultiFileProperty*>(m_pSel);
	if( gtProp )
	{
		if( gtProp->ButtonHitTest(point) )
			return;
	}
	else
	{
		GtPropertyGridProperty*  gtGridProp = dynamic_cast<GtPropertyGridProperty*>(m_pSel);
		if( gtGridProp && gtGridProp->ButtonHitTest(point) )
			return;
	}
	
	CMFCPropertyGridCtrl::OnLButtonDblClk(nFlags, point);
}

BOOL GtPropertyGridCtrl::RemoveProperty(CMFCPropertyGridProperty*& pProp, BOOL bRedraw, BOOL bAdjustLayout)
{
	ASSERT_VALID(this);
	ASSERT_VALID(pProp);

	BOOL bFound = FALSE;

	for (POSITION pos = m_lstProps.GetHeadPosition(); pos != NULL;)
	{
		POSITION posSaved = pos;

		CMFCPropertyGridProperty* pListProp = m_lstProps.GetNext(pos);
		ASSERT_VALID(pListProp);

		if (pListProp == pProp) // Top level property
		{
			bFound = TRUE;

			m_lstProps.RemoveAt(posSaved);
			break;
		}

		if (pListProp->RemoveSubItem(pProp, FALSE))
		{
			bFound = TRUE;
			break;
		}
	}

	if (!bFound)
	{
		return FALSE;
	}

	if (m_pSel == pProp)
	{
		m_pSel = NULL;
	}

	if (bAdjustLayout)
	{
		AdjustLayout();
		return TRUE;
	}

	if (bRedraw && GetSafeHwnd() != NULL)
	{
		RedrawWindow();
	}

	return TRUE;
}