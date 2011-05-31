#pragma once
#include "afxwin.h"


// CreateAnimationKeyDlg 대화 상자입니다.

class CreateAnimationKeyDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CreateAnimationKeyDlg)
public:
	enum { IDD = IDD_ADDANIMATIONKEY };

public:
	CreateAnimationKeyDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CreateAnimationKeyDlg();

	inline CString GetSelectString() {
		return mSelectString;
	}
	inline int GetSelectType() {
		return mSelectType;
	}

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
protected:
	CComboBox mAnimationKeyType;
	CString mSelectString;
	int mSelectType;
public:
	virtual BOOL OnInitDialog();
};
