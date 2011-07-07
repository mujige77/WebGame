#pragma once
#include "afxwin.h"
#include "GcActorExtraDataList.h"
#include "GcMediateObject.h"
#include "GcPropertyGridCtrl.h"
#include "GcExtraDataPropEntity.h"
// GcActorExtraDataDlg 대화 상자입니다.

class GcActorExtraDataDlg : public CDialogEx
{
	DECLARE_DYNAMIC(GcActorExtraDataDlg)
public:
	enum { IDD = IDD_GCACTOREVENTDLG };

protected:
	GtObject* mpObject;
	Gn2DMeshObject* mpMeshObject;
	GcActorExtraDataList mActorEventList;
	GcPropertyGridCtrl mActorEventProp;
	CStatic mActorEventPropLocation;
	GcExtraDataPropEntity mExtraDataPropEntity;

public:
	GcActorExtraDataDlg(CWnd* pParent = NULL);
	virtual ~GcActorExtraDataDlg();
	void ResetData(GtObject* pObject, Gn2DMeshObject* pMeshObject);

protected:
	void EnablePropertyGridCtrl(bool bEnable);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.	
	

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL OnInitDialog();
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
};
