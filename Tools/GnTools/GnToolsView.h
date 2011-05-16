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

// GnToolsView.h : CGnToolsView 클래스의 인터페이스
//


#pragma once

#include <GnFrame.h>
class CGnToolsView : public CView
{
private:
	GnFramePtr mGnFrame;
	UINT_PTR mTimerID;
	
protected: // serialization에서만 만들어집니다.
	CGnToolsView();
	DECLARE_DYNCREATE(CGnToolsView)

// 특성입니다.
public:
	CGnToolsDoc* GetDocument() const;

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

	inline GnFrame* GetGnFrame() {
		return mGnFrame;
	}
	inline void SetGnFrame(GnFrame* val) {
		mGnFrame = val;
	}

protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CGnToolsView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();

	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnAniPlay();
	afx_msg void OnAniPause();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};

#ifndef _DEBUG  // GnToolsView.cpp의 디버그 버전
inline CGnToolsDoc* CGnToolsView::GetDocument() const
   { return reinterpret_cast<CGnToolsDoc*>(m_pDocument); }
#endif

