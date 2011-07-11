#pragma once
#include "Gt2DObject.h"
#include "GcMediateObject.h"

class Gc2DObjectListCtrl : public CMFCListCtrl, public GcMediateObject
{
	DECLARE_DYNAMIC(Gc2DObjectListCtrl)
protected:
	Gt2DObject* mpsCurrentObject;
	int mSelectedItem;

public:
	Gc2DObjectListCtrl();
	virtual ~Gc2DObjectListCtrl();
	void ResetData(Gt2DObject* pObject);
	inline int GetSelectedItem() {
		return mSelectedItem;
	}
	inline void SetSelectedItem(int val) {
		mSelectedItem = val;
	}
	inline void AddItem(const gtchar* pcItemName) {
		int itemIndex = GetItemCount();
		InsertItem( itemIndex, pcItemName );
	}

protected:
	DECLARE_MESSAGE_MAP()

public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLvnItemchanged(NMHDR *pNMHDR, LRESULT *pResult);
};


