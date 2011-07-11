#pragma once
#include "GcEditorSequenceTexture.h"
#include "GcEditorSequenceMain.h"
#include "GcEditorTexture.h"

// GtEditorPropSheet

class GtEditorPropSheet : public CMFCPropertySheet
{
	DECLARE_DYNAMIC(GtEditorPropSheet)
protected:
	GcEditorSequenceTexture mSequenceTexturepage;
	GcEditorSequenceMain mSequenceMainPage;
	GcEditorTexture	mTexturepage;
	GcPropertyGridCtrl mPropList;

public:
	GtEditorPropSheet(CWnd* pParent = NULL);
	virtual ~GtEditorPropSheet();	

	void SetObject(GtObject* pObject, Gt2DSequence* pSequence);
	void SetModifyMode(int mode);

	inline GcEditorSequenceTexture* GetSequenceTexturepage() {
		return &mSequenceTexturepage;
	}
	inline GcEditorTexture* GetTexturepage() {
		return &mTexturepage;
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


