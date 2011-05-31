#pragma once
#include "GcEditorPropertyPage.h"
#include "afxwin.h"

// GcEditorSequenceMain 대화 상자입니다.

class GcEditorSequenceMain : public GcEditorPropertyPage
{
	DECLARE_DYNAMIC(GcEditorSequenceMain)
public:
		enum { IDD = IDD_SEQUENCE_PAGE1 };

protected:
	CEdit mEtID;
	CEdit mEtSequenceName;
	CEdit mEtSequenctFileName;
	Gt2DActor* mpActorObject;

public:
	GcEditorSequenceMain();
	virtual ~GcEditorSequenceMain();

	virtual void SetObject(GtObject* val) {
		GcEditorPropertyPage::SetObject( val );
		mpActorObject = (Gt2DActor*)val;
	}
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual bool CheckEnableButton();
	DECLARE_MESSAGE_MAP()
	void SetFileName();

public:
	virtual BOOL OnInitDialog();	
	afx_msg void OnEnChangeSequencename();	
	afx_msg void OnChangeSequencefilename();
	afx_msg void OnChangeSequenceindex();
	virtual void OnOK();
};
