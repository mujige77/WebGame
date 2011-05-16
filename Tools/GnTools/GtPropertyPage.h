#pragma once
#include "GnMessageDefine.h"

class GtPropertyPage : public CMFCPropertyPage 
{
	DECLARE_DYNAMIC(GtPropertyPage)
protected:
	GtSequenceInfo* mpSequence;
	GtObject* mpObject;
	bool mModifyMode;

public:
	GtPropertyPage();
	GtPropertyPage(UINT nIDTemplate, UINT nIDCaption = 0);
	GtPropertyPage(LPCTSTR lpszTemplateName, UINT nIDCaption = 0);
	virtual ~GtPropertyPage();

	inline GtSequenceInfo* SetSequenceInfo() {
		return mpSequence;
	}
	inline void SetSequenceInfo(GtSequenceInfo* val) {
		mpSequence = val;
	}

	inline GtObject* GetObject() {
		return mpObject;
	}
	virtual void SetObject(GtObject* val) {
		mpObject = val;
	}

	inline bool GetModifyMode() {
		return mModifyMode;
	}
	inline void SetModifyMode(bool val) {
		mModifyMode = val;
	}

	virtual bool CheckEnableButton();
protected:
	void CheckEnableOKButton();

protected:
	DECLARE_MESSAGE_MAP()
};


