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

/////////////////////////////////////////////////////////////////////////////
// CCalendarBar 창

class CCalendarBar : public CWnd
{
// 생성입니다.
public:
	CCalendarBar();

// 특성입니다.
protected:
	CMonthCalCtrl m_wndCalendar;
	int m_nMyCalendarsY;
	CImageList m_Images;

// 재정의입니다.
public:
	virtual BOOL Create(const RECT& rect, CWnd* pParentWnd, UINT nID = (UINT)-1);

// 구현입니다.
public:
	virtual ~CCalendarBar();

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();

	DECLARE_MESSAGE_MAP()
};
