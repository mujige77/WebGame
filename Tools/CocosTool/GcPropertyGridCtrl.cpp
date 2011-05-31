#include "StdAfx.h"
#include "GcPropertyGridCtrl.h"
#include "GcPropertyGridProperty.h"


// GcPropertyGridCtrl

IMPLEMENT_DYNAMIC(GcPropertyGridCtrl, CMFCPropertyGridCtrl)

BEGIN_MESSAGE_MAP(GcPropertyGridCtrl, CMFCPropertyGridCtrl)
	ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()


GcPropertyGridCtrl::GcPropertyGridCtrl()
{
}

GcPropertyGridCtrl::~GcPropertyGridCtrl()
{
}


BOOL GcPropertyGridCtrl::OnDrawProperty(CDC* pDC, CMFCPropertyGridProperty* pProp) const
{
	CMFCPropertyGridCtrl::OnDrawProperty(pDC, pProp);
	
	GcPropertyGridProperty*  gtGridProp = dynamic_cast<GcPropertyGridProperty*>(pProp);
	if( gtGridProp )
		gtGridProp->DrawButton(pDC);

	return TRUE;
}

BOOL GcPropertyGridCtrl::EditItem(CMFCPropertyGridProperty* pProp, LPPOINT lptClick)
{

	GcPropertyGridProperty*  gtGridProp = dynamic_cast<GcPropertyGridProperty*>(pProp);
	if( gtGridProp )
	{
		gtGridProp->OnEdit(lptClick);
		return true;
	}

	return CMFCPropertyGridCtrl::EditItem(pProp, lptClick);
}

void GcPropertyGridCtrl::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	if (m_pSel == NULL)
		return;

	GcPropertyGridProperty*  gtGridProp = dynamic_cast<GcPropertyGridProperty*>(m_pSel);
	if( gtGridProp && gtGridProp->ButtonHitTest(point) )
		return;

	CMFCPropertyGridCtrl::OnLButtonDblClk(nFlags, point);
}

BOOL GcPropertyGridCtrl::RemoveProperty(CMFCPropertyGridProperty*& pProp, BOOL bRedraw, BOOL bAdjustLayout)
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