#pragma once
#include "GcToolBarDockable.h"
#include "Gc2DObjectListCtrl.h"
#include "GcPropertyGridCtrl.h"
#include "GcCollectionEntities.h"

// Gc2DObjectDockable
class GcEditorTexture;
class Gc2DObjectDockable : public GcToolBarDockable
{
protected:
	GcPropertyGridCtrl m_wndPropList;
	Gc2DObjectListCtrl mListCtrl;
	Gt2DObjectPtr mpsCurrentObject;
	GcCollectionEntities* mpEntities;

public:
	Gc2DObjectDockable();
	virtual ~Gc2DObjectDockable();

protected:
	void AddTextureController(GcEditorTexture* pTexturepage);

protected:
	DECLARE_MESSAGE_MAP()

protected:
	void AdjustLayout();
	virtual void ReceiveMediateMessage(gtuint messageIndex, GcMediateObjectMessage* pMessage);
	void ChangeProperty(GcMediateObjectMessage* pMessage);

public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnBtSavetemplate();
	afx_msg void OnBtNewtemplate();
	afx_msg void OnBtDeltemplate();	


};


