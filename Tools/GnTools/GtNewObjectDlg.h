#pragma once
#include "afxwin.h"


// GtNewObjectDlg 대화 상자입니다.

class GtNewObjectDlg : public CDialogEx
{
	DECLARE_DYNAMIC(GtNewObjectDlg)

protected:
	CString mObjectName;
	CEdit mObjectNameEdt;

public:
	// 대화 상자 데이터입니다.
	enum { IDD = IDD_GTNEWOBJECTDLG };

public:
	GtNewObjectDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~GtNewObjectDlg();

	inline CString& GetObjectName() {
		return mObjectName;
	}

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
public:
	virtual BOOL OnInitDialog();
};
