#pragma once
#include "GtCollectionEntities.h"
#include "GtToolBarForm.h"
#include "GtMediateObject.h"

// GtMainProperties

class GtMainProperties : public GtToolBarForm
{
	DECLARE_DYNAMIC(GtMainProperties)
protected:
	GtPropertyGridCtrl mPropList;	
	GtObjectPtr mpsCurrentObject;

public:
	GtMainProperties();
	virtual ~GtMainProperties();
	GtCollectionEntities* mpEntities;

	bool SetObject(GnAVObject* object);
protected:
	DECLARE_MESSAGE_MAP()

public:		
	virtual void ReceiveMediateMessage(gtuint messageIndex, GtMediateObjectMessage* pInfo);

protected:
	void ChangeProperty(GtMediateObjectMessage* pInfo);
	void AdjustLayout();

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnEditSequence();
	LRESULT OnPropertyChanged(WPARAM wparam, LPARAM lparam);
public:
	void OnSaveObjectstate();
};