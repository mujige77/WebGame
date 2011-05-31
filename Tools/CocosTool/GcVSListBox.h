#pragma once

class GcVSListBox : public CVSListBox
{
	DECLARE_DYNAMIC(GcVSListBox)
protected:
	bool mSendMessageToParent;
	CString mBeforeEditText;
	bool mEnableEdit;

public:
	GcVSListBox(bool bSendMessageToParent = false);
	virtual ~GcVSListBox();

	// "Standard" action overrides
	virtual BOOL OnBeforeRemoveItem(int iItem);
	virtual void OnAfterAddItem(int iItem);
	virtual void OnAfterRenameItem(int iItem);
	virtual void OnAfterMoveItemUp(int iItem);
	virtual void OnAfterMoveItemDown(int iItem);
	virtual void OnSelectionChanged();
	virtual void SetItemText(int iIndex, const CString& strText);
	virtual BOOL EditItem(int iIndex);
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
	inline bool GetEnableEdit() {
		return mEnableEdit;
	}
	inline void SetEnableEdit(bool val) {
		mEnableEdit = val;
	}
protected:
	void RemoveAllItem(bool bSignalChildeClass = false);
protected:
	DECLARE_MESSAGE_MAP()

};