#pragma once
#include "GtSequenceTextureEditPage.h"
#include "GtSequenceMainEdiPage.h"


// GtEditorPropSheet

class GtEditorPropSheet : public CMFCPropertySheet
{
	DECLARE_DYNAMIC(GtEditorPropSheet)
protected:
	GtSequenceTextureEditPage mSequenceTexturepage;
	GtSequenceMainEdiPage mSequenceMainPage;
	GtPropertyGridCtrl mPropList;

public:
	GtEditorPropSheet(CWnd* pParent = NULL);
	virtual ~GtEditorPropSheet();	

	void SetObject(GtObject* pObject, GtSequenceInfo* pEditSequence);
	void SetModifyMode(int mode);

	inline GtSequenceTextureEditPage* GetSequenceTexturepage() {
		return &mSequenceTexturepage;
	}

protected:
	DECLARE_MESSAGE_MAP()


public:
	virtual void RemoveAllButton();

	virtual BOOL OnInitDialog();	
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);

protected:
	void ChangeTexturePage();	
	void CheckEnableOKButton();
	void EnableOKButton(bool bEnable = true);
};


