#pragma once
#include "GtActorObject.h"
#include "GtMediateObject.h"

class GtSequenceListCtrl : public CMFCListCtrl, public GtMediateObject
{
	DECLARE_DYNAMIC(GtSequenceListCtrl)
protected:
	GtActorObjectPtr mpsCurrentObject;
	int mSelectedItem;

public:
	GtSequenceListCtrl();
	virtual ~GtSequenceListCtrl();
	void ResetData(GtActorObject* pObject);
	void AddSequence(GtSequenceInfo* pSequence, bool bAddActor = true);
	void RemoveCurrentSequence();
	inline int GetSelectedItem() {
		return mSelectedItem;
	}
	inline void SetSelectedItem(int val) {
		mSelectedItem = val;
	}

	GtSequenceInfo* FindSequenceFromListItem(gtuint uiNum);
	GtSequenceInfo* FindSequenceFromID(CString strNum);
	GtSequenceInfo* FindSequenceFromID(guint32 uiNum);

protected:
	DECLARE_MESSAGE_MAP()

public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLvnItemchanged(NMHDR *pNMHDR, LRESULT *pResult);
};


