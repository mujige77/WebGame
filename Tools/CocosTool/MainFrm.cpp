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

// MainFrm.cpp : CMainFrame 클래스의 구현
//

#include "stdafx.h"
#include "CocosTool.h"

#include "MainFrm.h"
#include "GtToolEBM.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWndEx)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWndEx)
	ON_WM_CREATE()
	ON_COMMAND(ID_VIEW_CAPTION_BAR, &CMainFrame::OnViewCaptionBar)
	ON_UPDATE_COMMAND_UI(ID_VIEW_CAPTION_BAR, &CMainFrame::OnUpdateViewCaptionBar)
	ON_COMMAND(ID_TOOLS_OPTIONS, &CMainFrame::OnOptions)
	ON_COMMAND(IDC_SAVE_OBJECTSTATE, &CMainFrame::OnSaveObjectState)
	ON_COMMAND(ID_VIEW_SEQUENCEDOCKABLE, &CMainFrame::OnViewSequencedockable)
	ON_UPDATE_COMMAND_UI(ID_VIEW_SEQUENCEDOCKABLE, &CMainFrame::OnUpdateViewSequencedockable)
END_MESSAGE_MAP()

// CMainFrame 생성/소멸

CMainFrame::CMainFrame() : mpObject(NULL)
{
	// TODO: 여기에 멤버 초기화 코드를 추가합니다.
}

CMainFrame::~CMainFrame()
{
}

// CMainFrame 진단

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWndEx::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWndEx::Dump(dc);
}
#endif //_DEBUG



int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	GtToolEBM::StartupEBM();

	BOOL bNameValid;

	// 모든 사용자 인터페이스 요소를 그리는 데 사용하는 비주얼 관리자를 설정합니다.
	CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Aqua);
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2007));
	//CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows7));
	//CDockingManager::SetDockingMode(DT_SMART);
	//m_wndRibbonBar.SetWindows7Look(TRUE);

	m_wndRibbonBar.Create(this);
	m_wndRibbonBar.LoadFromResource(IDR_RIBBON);

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("상태 표시줄을 만들지 못했습니다.\n");
		return -1;      // 만들지 못했습니다.
	}

	CString strTitlePane1;
	CString strTitlePane2;
	bNameValid = strTitlePane1.LoadString(IDS_STATUS_PANE1);
	ASSERT(bNameValid);
	bNameValid = strTitlePane2.LoadString(IDS_STATUS_PANE2);
	ASSERT(bNameValid);
	m_wndStatusBar.AddElement(new CMFCRibbonStatusBarPane(ID_STATUSBAR_PANE1, strTitlePane1, TRUE), strTitlePane1);
	m_wndStatusBar.AddExtendedElement(new CMFCRibbonStatusBarPane(ID_STATUSBAR_PANE2, strTitlePane2, TRUE), strTitlePane2);

	// Visual Studio 2005 스타일 도킹 창 동작을 활성화합니다.
	CDockingManager::SetDockingMode(DT_SMART);
	// Visual Studio 2005 스타일 도킹 창 자동 숨김 동작을 활성화합니다.
	EnableAutoHidePanes(CBRS_ALIGN_ANY);

	// 탐색 창이 왼쪽에 만들어지므로 일시적으로 왼쪽에 도킹을 비활성화합니다.
	EnableDocking(CBRS_ALIGN_TOP | CBRS_ALIGN_BOTTOM | CBRS_ALIGN_RIGHT);

	// "Outlook" 탐색 모음을 만들고 설치합니다.
	if (!CreateOutlookBar(m_wndNavigationBar, ID_VIEW_NAVIGATION, 250))
	{
		TRACE0("탐색 창을 만들지 못했습니다.\n");
		return -1;      // 만들지 못했습니다.
	}
	
	if (!CreateDockableBar())
	{
		TRACE0("독킹 창을 만들지 못했습니다.\n");
		return -1;      // 만들지 못했습니다.
	}

	// 캡션 표시줄을 만듭니다.
	if (!CreateCaptionBar())
	{
		TRACE0("캡션 표시줄을 만들지 못했습니다.\n");
		return -1;      // 만들지 못했습니다.
	}

	// Outlook 표시줄이 만들어지고 왼쪽에 도킹할 수 있도록 허용해야 합니다.
	EnableDocking(CBRS_ALIGN_LEFT);
	EnableAutoHidePanes(CBRS_ALIGN_RIGHT);

	AttachNeedMessage( GTMG_SELECTOBJECT );
	AttachNeedMessage( GTMG_DESTORY );
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWndEx::PreCreateWindow(cs) )
		return FALSE;
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	cs.style = WS_OVERLAPPED | WS_CAPTION | FWS_ADDTOTITLE
		| WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX;

	return TRUE;
}

BOOL CMainFrame::CreateOutlookBar(CMFCOutlookBar& bar, UINT uiID, int nInitialWidth)
{
	bar.SetMode2003();

	BOOL bNameValid;
	CString strTemp;
	bNameValid = strTemp.LoadString(IDS_SHORTCUTS);
	ASSERT(bNameValid);
	if (!bar.Create(strTemp, this, CRect(0, 0, nInitialWidth, 32000), uiID, WS_CHILD | WS_VISIBLE | CBRS_LEFT))
	{
		return FALSE; // 만들지 못했습니다.
	}

	CMFCOutlookBarTabCtrl* pOutlookBar = (CMFCOutlookBarTabCtrl*)bar.GetUnderlyingWindow();

	if (pOutlookBar == NULL)
	{
		ASSERT(FALSE);
		return FALSE;
	}

	pOutlookBar->EnableInPlaceEdit(TRUE);

	static UINT uiPageID = 1;

	// 움직이거나, 자동으로 숨기거나, 크기를 조정할 수 있지만 닫을 수는 없습니다.
	DWORD dwStyle = AFX_CBRS_FLOAT | AFX_CBRS_AUTOHIDE | AFX_CBRS_RESIZE;
	CRect rectDummy(0, 0, 0, 0);

	//const DWORD dwTreeStyle = WS_CHILD | WS_VISIBLE | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS;

	//tree.Create(dwTreeStyle, rectDummy, &bar, 1200);
	//bNameValid = strTemp.LoadString(IDS_FOLDERS);
	//ASSERT(bNameValid);
	//pOutlookBar->AddControl(&tree, strTemp, 2, TRUE, dwStyle);

	//calendar.Create(rectDummy, &bar, 1201);
	//bNameValid = strTemp.LoadString(IDS_CALENDAR);
	//ASSERT(bNameValid);
	//pOutlookBar->AddControl(&calendar, strTemp, 3, TRUE, dwStyle);
	strTemp = _T("Tamplate Tasks");
	DWORD defaultStyle = WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_NOALIGN;
	if (!m_wndTemplateTasksPane.Create(strTemp, &bar, rectDummy, TRUE,
		ID_VIEW_TEMPLATETASKPANE, defaultStyle ))
	{
		TRACE0("속성 창을 만들지 못했습니다.\n");
		return FALSE; // 만들지 못했습니다.
	}
	pOutlookBar->AddControl(&m_wndTemplateTasksPane, strTemp, 2, TRUE, dwStyle);

	bar.SetPaneStyle(bar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

	pOutlookBar->SetImageList(theApp.m_bHiColorIcons ? IDB_PAGES_HC : IDB_PAGES, 24);
	pOutlookBar->SetToolbarImageList(theApp.m_bHiColorIcons ? IDB_PAGES_SMALL_HC : IDB_PAGES_SMALL, 16);
	pOutlookBar->RecalcLayout();

	BOOL bAnimation = theApp.GetInt(_T("OutlookAnimation"), TRUE);
	CMFCOutlookBarTabCtrl::EnableAnimation(bAnimation);

	bar.SetButtonsFont(&afxGlobalData.fontBold);

	return TRUE;
}

BOOL CMainFrame::CreateDockableBar()
{
	DWORD dwStyle = WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN 
		| CBRS_LEFT | CBRS_FLOAT_MULTI;	
	if (!mSequenceDockable.Create( _T("Sequence") , this, CRect(0, 0, 200, 200), TRUE
		, ID_VIEW_SEQUENCEDOCKABLE, dwStyle) )
	{
		TRACE0("속성 창을 만들지 못했습니다.\n");
		return false; // 만들지 못했습니다.
	}

	mSequenceDockable.EnableDocking(CBRS_ALIGN_ANY);
	

	if (!mSequenceModifyDockable.Create (_T("Source Code"), this, CRect (0, 0, 150, 150),
		TRUE /* Has gripper */, ID_VIEW_SEQUENCEMODIFYDOCKABLE,
		WS_CHILD | WS_VISIBLE | CBRS_BOTTOM | CBRS_FLOAT_MULTI,
		AFX_CBRS_REGULAR_TABS, AFX_CBRS_RESIZE | AFX_CBRS_AUTOHIDE))
	{
		TRACE0("Failed to create output bar\n");
		return -1;      // fail to create
	}

	DockPane( &mSequenceModifyDockable );
	DockPane( &mSequenceDockable );
	
	return true;
}

BOOL CMainFrame::CreateCaptionBar()
{
	if (!m_wndCaptionBar.Create(WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS, this, ID_VIEW_CAPTION_BAR, -1, TRUE))
	{
		TRACE0("캡션 표시줄을 만들지 못했습니다.\n");
		return FALSE;
	}

	BOOL bNameValid;

	CString strTemp, strTemp2;
	bNameValid = strTemp.LoadString(IDS_CAPTION_BUTTON);
	ASSERT(bNameValid);
	m_wndCaptionBar.SetButton(strTemp, ID_TOOLS_OPTIONS, CMFCCaptionBar::ALIGN_LEFT, FALSE);
	bNameValid = strTemp.LoadString(IDS_CAPTION_BUTTON_TIP);
	ASSERT(bNameValid);
	m_wndCaptionBar.SetButtonToolTip(strTemp);

	bNameValid = strTemp.LoadString(IDS_CAPTION_TEXT);
	ASSERT(bNameValid);
	m_wndCaptionBar.SetText(strTemp, CMFCCaptionBar::ALIGN_LEFT);

	m_wndCaptionBar.SetBitmap(IDB_INFO, RGB(255, 255, 255), FALSE, CMFCCaptionBar::ALIGN_LEFT);
	bNameValid = strTemp.LoadString(IDS_CAPTION_IMAGE_TIP);
	ASSERT(bNameValid);
	bNameValid = strTemp2.LoadString(IDS_CAPTION_IMAGE_TEXT);
	ASSERT(bNameValid);
	m_wndCaptionBar.SetImageToolTip(strTemp, strTemp2);

	return TRUE;
}

// CMainFrame 메시지 처리기

void CMainFrame::OnViewCaptionBar()
{
	m_wndCaptionBar.ShowWindow(m_wndCaptionBar.IsVisible() ? SW_HIDE : SW_SHOW);
	RecalcLayout(FALSE);
}

void CMainFrame::OnUpdateViewCaptionBar(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_wndCaptionBar.IsVisible());
}

void CMainFrame::OnViewSequencedockable()
{
	mSequenceDockable.ShowWindow(mSequenceDockable.IsVisible() ? SW_HIDE : SW_SHOW);
	RecalcLayout(FALSE);
}

void CMainFrame::OnUpdateViewSequencedockable(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(mSequenceDockable.IsVisible());
}

void CMainFrame::OnOptions()
{
	CMFCRibbonCustomizeDialog *pOptionsDlg = new CMFCRibbonCustomizeDialog(this, &m_wndRibbonBar);
	ASSERT(pOptionsDlg != NULL);

	pOptionsDlg->DoModal();
	delete pOptionsDlg;
}


BOOL CMainFrame::DestroyWindow()
{
	GcObjectMessage info;
	info.mpObject = NULL;
	info.mpSender = this;
	SendMediateMessage( GTMG_SELECTOBJECT, &info );

	if( CFrameWndEx::DestroyWindow() == false )
		return false;

	GetObjectFactory()->RemvoeAllObject();
	//SendMediateMessage( GTMG_DESTORY, NULL );	
	GtToolEBM::ShutdownEBM();

	// 마지막으로 루프 안시켜 주면 뻑남
	CCDirector::sharedDirector()->end();
	CCDirector::sharedDirector()->mainLoop();
	CCDirector::destoryDirector();	
	return true;
}

void CMainFrame::ReceiveMediateMessage(gtuint messageIndex, GcMediateObjectMessage* pSanderInfo)
{
	switch( messageIndex )
	{
	case GTMG_DESTORY:
		mpObject = NULL;
		break;
	case GTMG_SELECTOBJECT:
		{
			mpObject = pSanderInfo->mpObject;
		}
		break;
	}
}


void CMainFrame::OnSaveObjectState()
{
	GetObjectFactory()->SaveObjects( true );
	if( mpObject )
		GetObjectFactory()->AddObject( mpObject );
	m_wndTemplateTasksPane.GetTemplateList().OnSaveObjectstate();
}