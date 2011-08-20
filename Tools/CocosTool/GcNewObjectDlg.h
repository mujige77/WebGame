#pragma once
#include "afxwin.h"


// GcNewObjectDlg 대화 상자입니다.

class GcNewObjectDlg : public CDialogEx
{
	DECLARE_DYNAMIC(GcNewObjectDlg)
private:
	CComboBox mCBObjectType;
	int mObjectType;
	int mShowObjectType;
protected:
	CString mObjectName;
	CEdit mObjectNameEdt;

public:
	// 대화 상자 데이터입니다.
	enum { IDD = IDD_GTNEWOBJECTDLG };

public:
	GcNewObjectDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~GcNewObjectDlg();

	inline CString& GetObjectName() {
		return mObjectName;
	}
	inline int GetObjectType() {
		return mObjectType;
	}
	inline void HideObjectTypeComboBox() {
		mShowObjectType = SW_HIDE;
	}

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
public:
	virtual BOOL OnInitDialog();
};
