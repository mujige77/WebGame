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

// GnToolsView.cpp : CGnToolsView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "GnTools.h"
#endif

#include "GnToolsDoc.h"
#include "GnToolsView.h"
//#include "MainFrm.h"
#include <GnToolManager.h>
#include <GnFrame.h>
#include <GnTimer.h>
#include <GnSMTextureAniCtrl.h>
#include "GtWindowCreater.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CGnToolsView, CView)

BEGIN_MESSAGE_MAP(CGnToolsView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CGnToolsView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_SIZE()
	ON_WM_SETFOCUS()
	ON_COMMAND(ID_RBBT_PLAY, &CGnToolsView::OnAniPlay)
	ON_COMMAND(ID_RBBT_PAUSE, &CGnToolsView::OnAniPause)
	ON_WM_TIMER()
END_MESSAGE_MAP()

// CGnToolsView 생성/소멸

CGnToolsView::CGnToolsView()
{
	// TODO: 여기에 생성 코드를 추가합니다.
	static int i = 0;
	mTimerID = i++;

}

CGnToolsView::~CGnToolsView()
{
}

BOOL CGnToolsView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CGnToolsView 그리기

void CGnToolsView::OnDraw(CDC* /*pDC*/)
{
	CGnToolsDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	
	if( GnToolManager::Singletone() )
		GnToolManager::Singletone()->Render(m_hWnd);
}


// CGnToolsView 인쇄


void CGnToolsView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CGnToolsView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CGnToolsView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CGnToolsView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CGnToolsView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CGnToolsView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CGnToolsView 진단

#ifdef _DEBUG
void CGnToolsView::AssertValid() const
{
	CView::AssertValid();
}

void CGnToolsView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGnToolsDoc* CGnToolsView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGnToolsDoc)));
	return (CGnToolsDoc*)m_pDocument;
}
#endif //_DEBUG


// CGnToolsView 메시지 처리기


void CGnToolsView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	mGnFrame = GnFrame::Create(m_hWnd);
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
}


void CGnToolsView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
	if( mGnFrame )
		mGnFrame->RecreateRenderTarget(cx, cy);
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}


void CGnToolsView::OnSetFocus(CWnd* pOldWnd)
{
	CView::OnSetFocus(pOldWnd);
}


void CGnToolsView::OnAniPlay()
{
	//if (AfxGetMainWnd()->IsKindOf(RUNTIME_CLASS(CMainFrame)))
	//{
		//GtProperties& properties = GetWindowCreater()->GetAniProperties();
		//GnSMTextureAniCtrl* textureAni = properties.CreateSMTextureAniCtrl();
		//if( textureAni )
		//{
		//	textureAni->SetLoop(true);
		//	mGnFrame->SetTimeCtrl(GnGetTicks(), textureAni);
		//}
	//}
	 SetTimer(mTimerID, 0, NULL);
}


void CGnToolsView::OnAniPause()
{	
	mGnFrame->Stop();
	KillTimer(mTimerID);
}


void CGnToolsView::OnTimer(UINT_PTR nIDEvent)
{
	CView::OnTimer(nIDEvent);
	
	float time = GnGetTicks();
	if( GnToolManager::Singletone() )
	{
		GnToolManager::Singletone()->Update( time, m_hWnd );
	}

	if( GnToolManager::Singletone() )
	{
		GnToolManager::Singletone()->Render(m_hWnd);
	}
}
