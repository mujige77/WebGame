#pragma once
#include "afxwin.h"


// GcCreateCollisionDlg 대화 상자입니다.

class GcCreateCollisionDlg : public CDialogEx
{
	DECLARE_DYNAMIC(GcCreateCollisionDlg)
public:
	enum { IDD = IDD_GCCREATECOLLISIONDLG };

protected:
	CComboBox mCollisionType;
	int mSelectedCollisionType;

public:
	GcCreateCollisionDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~GcCreateCollisionDlg();

	inline int GetSelectedCollisionType() {
		return mSelectedCollisionType;
	}

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
