// 이 MFC 샘플 소스 코드는 MFC Microsoft Office Fluent 사용자 인터페이스("Fluent UI")를 
// 사용하는 방법을 보여 주며, MFC C++ 라이브러리 소프트웨어에 포함된 
// Microsoft Foundation Classes Reference 및 관련 전자 문서에 대해 
// 추가적으로 제공되는 내용입니다.  
// Fluent UI를 복사, 사용 또는 배포하는 데 대한 사용 약관은 별도로 제공됩니다.  
// Fluent UI 라이선싱 프로그램에 대한 자세한 내용은 
// http://msdn.microsoft.com/officeui를 참조하십시오.
//
// Copyright (C) Microsoft Corporation
// 모든 권리 보유.

#pragma once
#include "GtPropertyGridCtrl.h"
#include "GtCollectionEntities.h"
#include "GtSequenceListDlg.h"
#include "GtToolBarForm.h"
#include "GtEditorPropSheet.h"

class GnSMTextureAniCtrl;
class GtProperties : public GtToolBarForm
{
protected:	
	bool mModified;
	CComboBox m_wndObjectCombo;
	GtPropertyGridCtrl m_wndPropList;
	GtSequenceListCtrl mSequenceListCtrl;
	GtCollectionEntities* mpEntities;
	GtActorObjectPtr mpsCurrentObject;

// 생성입니다.
public:
	GtProperties();
	virtual ~GtProperties();
	void AdjustLayout();

public:
	inline GtPropertyGridCtrl& GetWndPropList() { return m_wndPropList; }
	virtual void ReceiveMediateMessage(gtuint messageIndex, GtMediateObjectMessage* pInfo);	
	void ChangeProperty(GtMediateObjectMessage* pInfo);
	void ChangeSequence(GtMediateObjectMessage* pInfo);

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnExpandAllProperties();	
	afx_msg void OnSortProperties();	
	afx_msg void OnProperties1();	
	afx_msg void OnProperties2();	
	afx_msg void OnSetFocus(CWnd* pOldWnd);

	DECLARE_MESSAGE_MAP()

	void InitPropList();
	void SetPropListFont();
	LRESULT OnPropertyChanged(WPARAM wparam, LPARAM lparam);	
public:
	void OnSaveObjectstate();
};

