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

// GameDesignView.cpp : CGameDesignView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "GameDesign.h"
#endif

#include "GameDesignDoc.h"
#include "GameDesignView.h"
#include "GStageLevelDesignView.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGameDesignView

IMPLEMENT_DYNCREATE(CGameDesignView, CTabView)

BEGIN_MESSAGE_MAP(CGameDesignView, CTabView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CGameDesignView 생성/소멸

CGameDesignView::CGameDesignView()
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CGameDesignView::~CGameDesignView()
{
}

void CGameDesignView::DoDataExchange(CDataExchange* pDX)
{
	CTabView::DoDataExchange(pDX);
}
// void CGameDesignView::Serialize(CArchive& ar)
// {
// 	GtConvertString filePath = ar.m_strFileName.GetString();
// 	GnStream stream;
// 	if (ar.IsStoring())
// 	{	// storing code
// 		stream.Save( filePath.GetAciiString() );
// 		CMFCTabCtrl& tab = GetTabControl();
// 		for( gint i = 0 ; i < tab.GetTabsNum() ; i++ )
// 		{
// 			GDesignFormView* view =  (GDesignFormView*)tab.GetTabWnd( i );
// 			view->Save( &stream );
// 		}
// 	}
// 	else
// 	{	// loading code
// 		stream.Load( filePath.GetAciiString() );
// 		CMFCTabCtrl& tab = GetTabControl();
// 		for( gint i = 0 ; i < tab.GetTabsNum() ; i++ )
// 		{
// 			GDesignFormView* view =  (GDesignFormView*)tab.GetTabWnd( i );
// 			view->Load( &stream );
// 		}
// 	}
// }

void CGameDesignView::OnInitialUpdate()
{
	CTabView::OnInitialUpdate();

	CString name = GetDocument()->GetOpenPathName();
	if( name.GetLength() > 0 )
	{
		Load( name.GetString() );
	}
	else
	{
		GtConvertString convertName = GStageLevelDesignView::GetStaicName();
		AddView( RUNTIME_CLASS(GStageLevelDesignView), convertName.c_str(), 100 );
	}
}

void CGameDesignView::Save(LPCTSTR lpszPathName)
{
	GtConvertString filePath = lpszPathName;
	GnStream stream;
	if( stream.Save( filePath.GetAciiString() ) )
	{
		CMFCTabCtrl& tab = GetTabControl();
		gint32 tabCount = tab.GetTabsNum();

		stream.SaveStream( tabCount );
		for( gint32 i = 0 ; i < tabCount ; i++ )
		{
			GDesignFormView* view =  (GDesignFormView*)tab.GetTabWnd( i );
			gstring viewName = view->GetName();
			stream.SaveStream( viewName.c_str() );
		}

		for( gint i = 0 ; i < tabCount ; i++ )
		{
			GDesignFormView* view =  (GDesignFormView*)tab.GetTabWnd( i );		
			view->Save( &stream );
		}
	}	
}

void CGameDesignView::Load(LPCTSTR lpszPathName)
{
	GtConvertString filePath = lpszPathName;
	GnStream stream;
	if( stream.Load( filePath.GetAciiString() ) )
	{
		gint32 tabCount = 0;
		stream.LoadStream( tabCount );
		for( gint32 i = 0 ; i < tabCount ; i++ )
		{
			gchar viewName[256] = { 0, };
			gushort nameLen = 0;
			stream.LoadStream( nameLen );
			stream.LoadStreams( viewName, nameLen );
			CRuntimeClass* runtime = GDesignFormView::GetCreateFormViewFunction( viewName )();
			GtConvertString convertName = viewName;
			AddView( runtime, convertName.c_str(), 100 );
		}

		CMFCTabCtrl& tab = GetTabControl();
		for( gint i = 0 ; i < tabCount ; i++ )
		{
			GDesignFormView* view =  (GDesignFormView*)tab.GetTabWnd( i );
			view->Load( &stream );
		}
	}
}

void CGameDesignView::OnActivateView(CView* pView)
{
	CTabView::OnActivateView( pView );
// 	CFrameWnd* pFrame = AFXGetParentFrame(this);
// 	ASSERT_VALID(pFrame);
// 
// 	pFrame->SetActiveView( this );
}

void CGameDesignView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CGameDesignView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CGameDesignView 진단

#ifdef _DEBUG
void CGameDesignView::AssertValid() const
{
	CTabView::AssertValid();
}

void CGameDesignView::Dump(CDumpContext& dc) const
{
	CTabView::Dump(dc);
}

CGameDesignDoc* CGameDesignView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGameDesignDoc)));
	return (CGameDesignDoc*)m_pDocument;
}
#endif //_DEBUG


