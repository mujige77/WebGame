#pragma once
#include "GcMediateObject.h"
#include "GcAnimationKeyList.h"
#include "GcPropertyGridCtrl.h"
#include "GcAnimationKeyPropEntity.h"
#include "afxcmn.h"
#include "afxwin.h"


class GcSequenceTimeDlg : public CDialogEx, public GcMediateObject
{
	DECLARE_DYNAMIC(GcSequenceTimeDlg)
public:
	enum { IDD = IDD_GCSEQUENCETIMEDLG };

protected:
	float mCurrentAniTime;
	GcAnimationKeyList mAnimationKeyList;
	CStatic mAnimationKeyLocaton;
	GcPropertyGridCtrl mAnimationKeyProp;
	GcAnimationKeyPropEntity mAnimationKeyPropEntity;
	Gt2DSequence* mpSequence;

public:
	GcSequenceTimeDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~GcSequenceTimeDlg();

	void ResetData(Gt2DSequence* val);
	void SetCurrentAniTime(float val);

	inline Gt2DSequence* GetGtSequence() {
		return mpSequence;
	}
	inline float GetCurrentAniTime() {
		return mCurrentAniTime;
	}
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	DECLARE_MESSAGE_MAP()

	void ReceiveMediateMessage(gtuint messageIndex, GcMediateObjectMessage* pMessage);
	virtual BOOL OnInitDialog();
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
public:
	afx_msg void OnBnClickedApplyCurrenttimeanikey();
};
