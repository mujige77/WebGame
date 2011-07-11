#pragma once


// GcCreateExtraDataDlg 대화 상자입니다.

class GcCreateExtraDataDlg : public CDialogEx
{
	DECLARE_DYNAMIC(GcCreateExtraDataDlg)
public:
	enum { IDD = IDD_GCCREATEEXTRADATA };

protected:
	CComboBox mComboExtraDataType;
	int mSelectedExtraDataType;

public:
	GcCreateExtraDataDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~GcCreateExtraDataDlg();

public:
	inline int GetSelectedExtraDataType() {
		return mSelectedExtraDataType;
	}

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
