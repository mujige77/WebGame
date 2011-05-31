#pragma once
#include "GtEditorPropSheet.h"
#include "GcPropertyGridCtrl.h"


// GtEditorPropSheetDlg 대화 상자입니다.

class GtEditorPropSheetDlg : public CDialogEx
{
	DECLARE_DYNAMIC(GtEditorPropSheetDlg)
public:
	enum { IDD = IDD_GtEditorPropSheetDlg2 };

protected:
	GtEditorPropSheet mEditorSheet;
	GcPropertyGridCtrl mPropList;

public:
	GtEditorPropSheetDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~GtEditorPropSheetDlg();

	void AdjustLayout();

	inline GtEditorPropSheet* GetEditorSheet() {
		return &mEditorSheet;
	}
	inline GcPropertyGridCtrl* GetPropList() {
		return &mPropList;
	}
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
