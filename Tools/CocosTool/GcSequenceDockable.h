#pragma once
#include "GcToolBarDockable.h"
#include "GcSequenceListCtrl.h"
#include "GcPropertyGridCtrl.h"
#include "GcCollectionEntities.h"

// GcSequenceDockable

class GcSequenceDockable : public GcToolBarDockable
{
protected:
	GcPropertyGridCtrl m_wndPropList;
	GcSequenceListCtrl mSequenceListCtrl;
	Gt2DActorPtr mpsCurrentObject;
	GcCollectionEntities* mpEntities;

public:
	GcSequenceDockable();
	virtual ~GcSequenceDockable();

protected:
	DECLARE_MESSAGE_MAP()
protected:
	void AdjustLayout();
	virtual void ReceiveMediateMessage(gtuint messageIndex, GcMediateObjectMessage* pMessage);
	void ChangeProperty(GcMediateObjectMessage* pMessage);
	void ChangeSequence(GcMediateObjectMessage* pMessage);

public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnBtSavetemplate();
	afx_msg void OnBtNewtemplate();
	afx_msg void OnBtDeltemplate();	
	

};


