#pragma once


// GtTemplateListCtrl

class GtTemplateListCtrl : public CListCtrl
{
	DECLARE_DYNAMIC(GtTemplateListCtrl)
protected:
	int mSelectedItem;
	CString mSelectedItemText;

public:
	GtTemplateListCtrl();
	virtual ~GtTemplateListCtrl();

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


