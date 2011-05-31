#pragma once
#include "GnSignal.h"
#include "GcPropertyGridProperty.h"

class GcPropertyGridCtrl : public CMFCPropertyGridCtrl
{
	DECLARE_DYNAMIC(GcPropertyGridCtrl)

public:
	GcPropertyGridCtrl();
	virtual ~GcPropertyGridCtrl();

public:
	virtual int OnDrawProperty(CDC* pDC, CMFCPropertyGridProperty* pProp) const;
	virtual BOOL EditItem(CMFCPropertyGridProperty* pProp, LPPOINT lptClick = NULL);	
	virtual BOOL RemoveProperty(CMFCPropertyGridProperty*& pProp, BOOL bRedraw = true, BOOL bAdjustLayout = true);
protected:
	DECLARE_MESSAGE_MAP();

public:
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
};


