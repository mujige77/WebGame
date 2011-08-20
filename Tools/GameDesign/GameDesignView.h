#pragma once

#include "resource.h"

class CGameDesignDoc;
class CGameDesignView : public CTabView
{
protected: // serialization에서만 만들어집니다.
	CGameDesignView();
	DECLARE_DYNCREATE(CGameDesignView)

public:
	virtual void OnInitialUpdate();
	void Save(LPCTSTR lpszPathName);
	void Load(LPCTSTR lpszPathName);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual void OnActivateView(CView* pView);

// 특성입니다.
public:
	CGameDesignDoc* GetDocument() const;

public:
	BOOL IsScrollBar () const {
		return TRUE;
	}


// 구현입니다.
public:
	virtual ~CGameDesignView();
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
};

#ifndef _DEBUG  // GStageLevelDesignView.cpp의 디버그 버전
inline CGameDesignDoc* CGameDesignView::GetDocument() const
   { return reinterpret_cast<CGameDesignDoc*>(m_pDocument); }
#endif

