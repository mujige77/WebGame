#pragma once
#include "GcTabCtrl.h"
#include "GcToolBarDockable.h"
// GcSequenceModifyDockable

class GcSequenceModifyDockable : public GcToolBarDockable
{
private:
	static const gtchar* msSequenceCollisionDlgName;
	static const gtchar* msSequenceTimeDlgName;
	static const gtchar* msActorEventDlgName;

protected:
	GcTabCtrl mTabCtrl;
	float mCurrentAniTime;
	GtObjectPtr mpsCurrentObject;

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

protected:
	virtual void ReceiveMediateMessage(gtuint messageIndex, GcMediateObjectMessage* pMessage);
	void ChangeProperty(GcMediateObjectMessage* pMessage);
	void ChangeSequence(GcMediateObjectMessage* pMessage);
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual void PostNcDestroy();
};


