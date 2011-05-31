#pragma once
#include "GcPropertyGridCtrl.h"
#include "GcAnimationKeyPropEntity.h"
#include "GcMediateObject.h"
#include "GcCollisionList.h"
#include "afxcmn.h"
#include "afxwin.h"
#include "Gc2DCollisionBoxPropEntity.h"

// GcSequenceCollisionDlg 대화 상자입니다.

class GcSequenceCollisionDlg : public CDialogEx, public GcMediateObject
{
	DECLARE_DYNAMIC(GcSequenceCollisionDlg)

protected:
	GcCollisionList mCollisionList;
	CStatic mCollisionPropLocaton;
	GcPropertyGridCtrl mCollisionProp;
	Gc2DCollisionBoxPropEntity mCollisionPropEntity;

	Gt2DActor* mpActor;
	Gt2DSequence* mpSequence;
	
public:
	GcSequenceCollisionDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~GcSequenceCollisionDlg();
	enum { IDD = IDD_GCSEQUENCECOLLISIONDLG };
	void ResetData(Gt2DActor* pActor, Gt2DSequence* pSequence);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

	virtual BOOL OnInitDialog();
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	virtual void ReceiveMediateMessage(gtuint messageIndex, GcMediateObjectMessage* pMessage);
};
