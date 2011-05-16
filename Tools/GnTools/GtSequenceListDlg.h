#pragma once
#include "GtSequenceListCtrl.h"

class GtSequenceListDlg : public CDialogEx
{
	DECLARE_DYNAMIC(GtSequenceListDlg)
protected:
	GtSequenceListCtrl mListCtrl;

public:
	GtSequenceListDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~GtSequenceListDlg();

// 대화 상자 데이터입니다.
	enum { IDD = PROPPAGE_SEQUENCE_EDITOR };

	DECLARE_MESSAGE_MAP()
public:
	inline GtSequenceListCtrl& GetListControl() {
		return mListCtrl;
	}
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);	
	afx_msg void OnBnClickedAddsequence();
	afx_msg void OnBnClickedDelsequence();	

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
};
