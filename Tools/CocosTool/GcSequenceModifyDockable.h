#pragma once
#include "GcTabCtrl.h"
#include "GcToolBarDockable.h"
// GcSequenceModifyDockable

class GcSequenceModifyDockable : public GcToolBarDockable
{
private:
	static const gtchar* msSequenceCollisionDlgName;
	static const gtchar* msSequenceTimeDlgName;
	static const gtchar* msActorExtraDlgName;
	static const gtchar* ms2DObjectExtraDlgName;

protected:
	GcTabCtrl mTabCtrl;
	float mCurrentAniTime;
	GtObjectPtr mps2DObject;
	GtObjectPtr mpsActorObject;

public:
	GcSequenceModifyDockable();
	virtual ~GcSequenceModifyDockable();

	inline float GetCurrentAniTime() {
		return mCurrentAniTime;
	}
	inline void SetCurrentAniTime(float val) {
		mCurrentAniTime = val;
	}
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	void AddTab(CWnd* pAddWnd, CString strName);	
	void RemoveAllTab();
	void RemoveSequenceTab();
	void RemoveSequence(const gtchar* pcName);

protected:
	virtual void ReceiveMediateMessage(gtuint messageIndex, GcMediateObjectMessage* pMessage);
	void ChangeProperty(GcMediateObjectMessage* pMessage);
	void ChangeSequence(GcMediateObjectMessage* pMessage);
	void SetActiveTab(CString strActiveName);
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual void PostNcDestroy();
};


