#pragma once
#include "GtPropertyPage.h"
#include "afxwin.h"

// GtSequenceMainEdiPage 대화 상자입니다.

class GtSequenceMainEdiPage : public GtPropertyPage
{
	DECLARE_DYNAMIC(GtSequenceMainEdiPage)
public:
		enum { IDD = IDD_SEQUENCE_PAGE1 };

protected:
	CEdit mEtID;
	CEdit mEtSequenceName;
	CEdit mEtSequenctFileName;
	GtActorObject* mpActorObject;
public:
	GtSequenceMainEdiPage();
	virtual ~GtSequenceMainEdiPage();

	virtual void SetObject(GtObject* val) {
		GtPropertyPage::SetObject( val );
		mpActorObject = (GtActorObject*)val;
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
