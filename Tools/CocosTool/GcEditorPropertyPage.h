#pragma once

class GcEditorPropertyPage : public CMFCPropertyPage 
{
	DECLARE_DYNAMIC(GcEditorPropertyPage)
protected:
	GtObject* mpObject;
	Gt2DSequence* mpSequence;
	gint mModifyMode;

public:
	GcEditorPropertyPage();
	GcEditorPropertyPage(UINT nIDTemplate, UINT nIDCaption = 0);
	GcEditorPropertyPage(LPCTSTR lpszTemplateName, UINT nIDCaption = 0);
	virtual ~GcEditorPropertyPage();

	inline Gt2DSequence* GetSequence() {
		return mpSequence;
	}
	inline void SetSequence(Gt2DSequence* val) {
		mpSequence = val;
	}
	inline GtObject* GetObject() {
		return mpObject;
	}
	virtual void SetObject(GtObject* val) {
		mpObject = val;
	}
	inline gint GetModifyMode() {
		return mModifyMode;
	}
	inline void SetModifyMode(gint val) {
		mModifyMode = val;
	}
	virtual bool CheckEnableButton();

protected:
	void CheckEnableOKButton();

protected:
	DECLARE_MESSAGE_MAP()
};


