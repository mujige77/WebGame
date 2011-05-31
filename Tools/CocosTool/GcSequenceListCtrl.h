#pragma once
#include "Gt2DActor.h"
#include "GcMediateObject.h"

class GcSequenceListCtrl : public CMFCListCtrl, public GcMediateObject
{
	DECLARE_DYNAMIC(GcSequenceListCtrl)
protected:
	Gt2DActorPtr mpsCurrentActor;
	int mSelectedItem;

public:
	GcSequenceListCtrl();
	virtual ~GcSequenceListCtrl();
	void ResetData(Gt2DActor* pObject);
	void AddSequence(guint32 uiID, const gchar* pcName, const gchar* pcFileName
		, bool bAddActor = true);
	void RemoveCurrentSequence();
	inline int GetSelectedItem() {
		return mSelectedItem;
	}
	inline void SetSelectedItem(int val) {
		mSelectedItem = val;
	}

	GtActorTool::SequenceInfo* FindSequenceFromListItem(gtuint uiNum);
	GtActorTool::SequenceInfo* FindSequenceFromID(CString strNum);
	GtActorTool::SequenceInfo* FindSequenceFromID(guint32 uiNum);

protected:
	DECLARE_MESSAGE_MAP()

public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLvnItemchanged(NMHDR *pNMHDR, LRESULT *pResult);
};


