#pragma once
#include "GnMessageDefine.h"

// GtVSListBox

class GtVSListBox : public CVSListBox
{
	DECLARE_DYNAMIC(GtVSListBox)
protected:
	bool mSendMessageToParent;
	CString mBeforeEditText;

public:
	GtVSListBox(bool bSendMessageToParent = false);
	virtual ~GtVSListBox();

	// "Standard" action overrides
	virtual BOOL OnBeforeRemoveItem(int iItem);
	virtual void OnAfterAddItem(int iItem);
	virtual void OnAfterRenameItem(int iItem);
	virtual void OnAfterMoveItemUp(int iItem);
	virtual void OnAfterMoveItemDown(int iItem);
	virtual void OnSelectionChanged();
	virtual void SetItemText(int iIndex, const CString& strText);

	BOOL SendMessageToParent(UINT message, WPARAM wParam, LPARAM lParam) {		
		if( mSendMessageToParent )
		{
			GnAssert( GetParent() );
			GTVSITEMACTIVATE  msg;	
			msg.hdr.hwndFrom = GetSafeHwnd();
			msg.hwndListCtrl = GetListHwnd();
			msg.iItem = lParam;
			return GetParent()->SendNotifyMessage( message, wParam, (LPARAM)&msg );
		}
		return true;
	}

	inline bool GetSendMessageToParent() {
		return mSendMessageToParent;
	}
	inline void SetSendMessageToParent(bool val) {
		mSendMessageToParent = val;
	}
	inline CString& GetBeforeEditText() {
		return mBeforeEditText;
	}
	inline void SetBeforeEditText(CString val) {
		mBeforeEditText = val;
	}
protected:
	DECLARE_MESSAGE_MAP()
};