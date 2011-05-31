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

// CocosToolView.h : CCocosToolView 클래스의 인터페이스
//

#pragma once


#include "GtCocos2DApp.h"
#include "GcMediateObject.h"
#include "afxwin.h"
#include "CategoryAnimationManager.h"
class CCocosToolView : public CFormView, GcMediateObject
{
	BOOL PreTranslateMessage(MSG* pMsg)
	{
		if(pMsg->message == WM_CHAR)
		{
			SendMessage(pMsg->message, pMsg->wParam, pMsg->lParam);
			return TRUE;
		}

		return CFormView::PreTranslateMessage(pMsg);
	}
protected: // serialization에서만 만들어집니다.
	CCocosToolView();
	DECLARE_DYNCREATE(CCocosToolView)

// 특성입니다.
public:
	enum { IDD = IDD_MAINRENDERVIEW };

private:
	GtCocos2DApp* mpApp;
	Gt2DActorPtr mpsActor;
	Gt2DSequencePtr mpsSequence;
	GnDrawPrimitivesPtr mpsDrawSequenceRect;
	CString mStrCurrentTime;
	float mfCurrentTime;
	float mBforeTime;
	float mfStartTime;
	float mfEndTime;
	float mfTick;
	float mfLastTick;
	CategoryAnimationManager mCategoryAnimation;
	GnLayerDrawPrimitives* mpDrawLayer;
	CMFCSpinButtonCtrl* mpSpinCurrentTime;
	int	mBackgroundMoveRange;
	UINT_PTR mTimerID;

protected:
	CStatic mLoactionRender;
	bool mModifyCollsionBoxsCheck;


public:
	void SetCurrentTime(float val);
	inline float GetCurrentTime() {
		return mfCurrentTime;
	}

protected:
	void SetCurrentTimeFromOnTimer();
	void Loadbackground(const gchar* pcFilePath);

public:
	virtual ~CCocosToolView();
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 생성된 메시지 맵 함수
protected:
	CCocosToolDoc* GetDocument() const;
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	virtual void ReceiveMediateMessage(gtuint messageIndex, GcMediateObjectMessage* pSanderInfo);

	void ChageSequenceAniTime( Gt2DSequence* sequence );
	void AddCurrentActorToLayerDrawPprimitives();
	DECLARE_MESSAGE_MAP()
	

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	virtual void OnInitialUpdate();
	virtual void DoDataExchange(CDataExchange* pDX);	
	virtual void PostNcDestroy();
	afx_msg void OnAniPlay();
	afx_msg void OnAniPause();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	
	afx_msg void OnModifyCollisionboxs();
	afx_msg void OnUpdateModifyCollisionboxs(CCmdUI *pCmdUI);
	afx_msg void OnAnicurrenttime();
	afx_msg void OnAnitimeslider();
	afx_msg void OnBtLoadbackground();
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	afx_msg void OnBackgroundMoverange();
};

#ifndef _DEBUG  // CocosToolView.cpp의 디버그 버전
inline CCocosToolDoc* CCocosToolView::GetDocument() const
   { return reinterpret_cast<CCocosToolDoc*>(m_pDocument); }
#endif

