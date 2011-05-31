#pragma once


// GcTemplateListCtrl

class GcTemplateListCtrl : public CListCtrl
{
	DECLARE_DYNAMIC(GcTemplateListCtrl)
protected:
	int mSelectedItem;
	CString mSelectedItemText;

public:
	GcTemplateListCtrl();
	virtual ~GcTemplateListCtrl();

	inline CString& GetSelectedItemText() {
		return mSelectedItemText;
	}
	inline int GetSelectedItem() {
		return mSelectedItem;
	}
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnNMClick(NMHDR *pNMHDR, LRESULT *pResult);	
};


