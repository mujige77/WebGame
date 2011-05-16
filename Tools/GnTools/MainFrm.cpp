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
#include "GnTools.h"

#include "MainFrm.h"
#include "GnToolEBM.h"
#include <GnToolManager.h>
#include "GnMessageDefine.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWndEx)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWndEx)
	ON_WM_CREATE()
	ON_COMMAND(ID_WINDOW_MANAGER, &CMainFrame::OnWindowManager)
	ON_COMMAND_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &CMainFrame::OnApplicationLook)
	ON_UPDATE_COMMAND_UI_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &CMainFrame::OnUpdateApplicationLook)
	ON_WM_SETTINGCHANGE()
	ON_WM_TIMER()
	ON_COMMAND(ID_RBBT_PROPERTYENABLE, &CMainFrame::OnPropertyEnable)
	ON_COMMAND(ID_SAVE_OBJECTSTATE, &CMainFrame::OnSaveObjectstate)
END_MESSAGE_MAP()

// CMainFrame 생성/소멸

CMainFrame::CMainFrame()
{
	// TODO: 여기에 멤버 초기화 코드를 추가합니다.
	theApp.m_nAppLook = theApp.GetInt(_T("ApplicationLook"), ID_VIEW_APPLOOK_WINDOWS_7);
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	GnToolEBM::StartupEBM();
	GnToolManager::Singletone()->CreateRenderer(m_hWnd);
	GnSMManager::Create();

	BOOL bNameValid;
	// 보관된 값에 따라 비주얼 관리자 및 스타일을 설정합니다.
	OnApplicationLook(theApp.m_nAppLook);

	CMDITabInfo mdiTabParams;
	mdiTabParams.m_style = CMFCTabCtrl::STYLE_3D_ONENOTE; // 사용할 수 있는 다른 스타일...
	mdiTabParams.m_bActiveTabCloseButton = TRUE;      // FALSE로 설정하여 탭 영역 오른쪽에 닫기 단추를 배치합니다.
	mdiTabParams.m_bTabIcons = FALSE;    // TRUE로 설정하여 MDI 탭의 문서 아이콘을 활성화합니다.
	mdiTabParams.m_bAutoColor = TRUE;    // FALSE로 설정하여 MDI 탭의 자동 색 지정을 비활성화합니다.
	mdiTabParams.m_bDocumentMenu = TRUE; // 탭 영역의 오른쪽 가장자리에 문서 메뉴를 활성화합니다.
	EnableMDITabbedGroups(TRUE, mdiTabParams);

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

	// 메뉴 항목 이미지를 로드합니다(표준 도구 모음에 없음).
	CMFCToolBar::AddToolBarForImageCollection(IDR_MENU_IMAGES, theApp.m_bHiColorIcons ? IDB_MENU_IMAGES_24 : 0);

	GtWindowCreater::Create();
	if( GetWindowCreater()->CreateUsedWindows( this, theApp.m_bHiColorIcons ) == false )
	{
		TRACE0("도킹 창을 만들지 못했습니다.\n");
		return -1;
	}

	GetWindowCreater()->SetDockingWindows( this );

	// 도킹 창을 만듭니다.
	if (!CreateDockingWindows())
	{
		TRACE0("도킹 창을 만들지 못했습니다.\n");
		return -1;
	}

	// "Outlook" 탐색 모음을 만들고 설치합니다.
	if (!CreateOutlookBar(m_wndNavigationBar, ID_VIEW_NAVIGATION, m_wndTree, m_wndCalendar, 250))
	{
		TRACE0("탐색 창을 만들지 못했습니다.\n");
		return -1;      // 만들지 못했습니다.
	}

	// Outlook 표시줄이 만들어지고 왼쪽에 도킹할 수 있도록 허용해야 합니다.
	EnableDocking(CBRS_ALIGN_LEFT);
	EnableAutoHidePanes(CBRS_ALIGN_RIGHT);
	//m_wndFileView.EnableDocking(CBRS_ALIGN_ANY);
	//m_wndClassView.EnableDocking(CBRS_ALIGN_ANY);
	//DockPane(&m_wndClassView);
	//CDockablePane* pTabbedBar = NULL;
	//m_wndClassView.AttachToTabWnd(&m_wndFileView, DM_SHOW, TRUE, &pTabbedBar);
	//m_wndOutput.EnableDocking(CBRS_ALIGN_ANY);
	//DockPane(&m_wndOutput);
	//m_wndProperties.EnableDocking(CBRS_ALIGN_ANY);
	//DockPane(&m_wndProperties);
	

	// 향상된 창 관리 대화 상자를 활성화합니다.
	EnableWindowsDialog(ID_WINDOW_MANAGER, ID_WINDOW_MANAGER, TRUE);

	// 창 제목 표시줄에서 문서 이름 및 응용 프로그램 이름의 순서를 전환합니다.
	// 문서 이름이 축소판 그림과 함께 표시되므로 작업 표시줄의 기능성이 개선됩니다.
	ModifyStyle(0, FWS_PREFIXTITLE);
	return 0;
}


BOOL CMainFrame::DestroyWindow()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if( CMDIFrameWndEx::DestroyWindow() == false )
		return false;

	GtWindowCreater::Destroy();
	GnSMManager::Destory();
	GnToolEBM::ShutdownEBM();	
	return true;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIFrameWndEx::PreCreateWindow(cs) )
		return FALSE;
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return TRUE;
}

BOOL CMainFrame::CreateDockingWindows()
{
	//BOOL bNameValid;

	//// 클래스 뷰를 만듭니다.
	//CString strClassView;
	//bNameValid = strClassView.LoadString(IDS_CLASS_VIEW);
	//ASSERT(bNameValid);
	//if (!m_wndClassView.Create(strClassView, this, CRect(0, 0, 200, 200), TRUE,	ID_VIEW_CLASSVIEW,
	//	WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT | CBRS_FLOAT_MULTI))
	//{
	//	TRACE0("클래스 뷰 창을 만들지 못했습니다.\n");
	//	return FALSE; // 만들지 못했습니다.
	//}

	//// 파일 뷰를 만듭니다.
	//CString strFileView;
	//bNameValid = strFileView.LoadString(IDS_FILE_VIEW);
	//ASSERT(bNameValid);
	//if (!m_wndFileView.Create(strFileView, this, CRect(0, 0, 200, 200), TRUE, ID_VIEW_FILEVIEW,
	//	WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT| CBRS_FLOAT_MULTI))
	//{
	//	TRACE0("파일 뷰 창을 만들지 못했습니다.\n");
	//	return FALSE; // 만들지 못했습니다.
	//}

	//// 출력 창을 만듭니다.
	//CString strOutputWnd;
	//bNameValid = strOutputWnd.LoadString(IDS_OUTPUT_WND);
	//ASSERT(bNameValid);
	//if (!m_wndOutput.Create(strOutputWnd, this, CRect(0, 0, 100, 100), TRUE, ID_VIEW_OUTPUTWND,
	//	WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_BOTTOM | CBRS_FLOAT_MULTI))
	//{
	//	TRACE0("출력 창을 만들지 못했습니다.\n");
	//	return FALSE; // 만들지 못했습니다.
	//}

	// 속성 창을 만듭니다.
	//CString strPropertiesWnd;
	//bNameValid = strPropertiesWnd.LoadString(IDS_PROPERTIES_WND);
	//ASSERT(bNameValid);
	//if (!m_wndProperties.Create(strPropertiesWnd, this, CRect(0, 0, 200, 200), TRUE, ID_VIEW_MAINPROPERTIES,
	//	WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_RIGHT | CBRS_FLOAT_MULTI))
	//{
	//	TRACE0("속성 창을 만들지 못했습니다.\n");
	//	return FALSE; // 만들지 못했습니다.
	//}

	SetDockingWindowIcons(theApp.m_bHiColorIcons);
	return TRUE;
}

void CMainFrame::SetDockingWindowIcons(BOOL bHiColorIcons)
{
	//HICON hFileViewIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_FILE_VIEW_HC : IDI_FILE_VIEW), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
	//m_wndFileView.SetIcon(hFileViewIcon, FALSE);

	//HICON hClassViewIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_CLASS_VIEW_HC : IDI_CLASS_VIEW), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
	//m_wndClassView.SetIcon(hClassViewIcon, FALSE);

	//HICON hOutputBarIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_OUTPUT_WND_HC : IDI_OUTPUT_WND), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
	//m_wndOutput.SetIcon(hOutputBarIcon, FALSE);

	//HICON hPropertiesBarIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_PROPERTIES_WND_HC : IDI_PROPERTIES_WND), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
	//m_wndProperties.SetIcon(hPropertiesBarIcon, FALSE);

	UpdateMDITabbedBarsIcons();
}

BOOL CMainFrame::CreateOutlookBar(CMFCOutlookBar& bar, UINT uiID, CMFCShellTreeCtrl& tree, CCalendarBar& calendar, int nInitialWidth)
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

// CMainFrame 진단

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWndEx::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWndEx::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 메시지 처리기

void CMainFrame::OnWindowManager()
{
	ShowWindowsDialog();
}

void CMainFrame::OnApplicationLook(UINT id)
{
	CWaitCursor wait;

	theApp.m_nAppLook = id;

	switch (theApp.m_nAppLook)
	{
	case ID_VIEW_APPLOOK_WIN_2000:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManager));
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_OFF_XP:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOfficeXP));
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_WIN_XP:
		CMFCVisualManagerWindows::m_b3DTabsXPTheme = TRUE;
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_OFF_2003:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2003));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_VS_2005:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2005));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_VS_2008:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2008));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_WINDOWS_7:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows7));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(TRUE);
		break;

	default:
		switch (theApp.m_nAppLook)
		{
		case ID_VIEW_APPLOOK_OFF_2007_BLUE:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_LunaBlue);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_BLACK:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_ObsidianBlack);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_SILVER:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Silver);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_AQUA:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Aqua);
			break;
		}

		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2007));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(FALSE);
	}

	RedrawWindow(NULL, NULL, RDW_ALLCHILDREN | RDW_INVALIDATE | RDW_UPDATENOW | RDW_FRAME | RDW_ERASE);

	theApp.WriteInt(_T("ApplicationLook"), theApp.m_nAppLook);
}

void CMainFrame::OnUpdateApplicationLook(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio(theApp.m_nAppLook == pCmdUI->m_nID);
}

void CMainFrame::OnSettingChange(UINT uFlags, LPCTSTR lpszSection)
{
	CMDIFrameWndEx::OnSettingChange(uFlags, lpszSection);
	m_wndOutput.UpdateFonts();
}

void CMainFrame::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	
	CMDIFrameWnd* pActivFrame = NULL;
	CView* pView = NULL;

	pActivFrame = (CMDIFrameWnd*)GetActiveFrame();
	if( pActivFrame == NULL || pActivFrame->IsIconic() )
		return;
	
	pView = pActivFrame->GetActiveView();
	if( pView == NULL )
		return;

	if( pActivFrame->m_hWnd != ::GetActiveWindow() )
		return;

	pView->SendNotifyMessage(GTMG_ONTIMER, nIDEvent, NULL);
	CMDIFrameWndEx::OnTimer(nIDEvent);
}


void CMainFrame::OnPropertyEnable()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	//m_wndProperties.ShowPane(!m_wndProperties.IsVisible(), false, true);
	///m_wndClassView.ShowPane(true, false, true);
	//m_wndFileView.ShowPane(true, false, true);
	//GtProperties& prop = GetWindowCreater()->GetAniProperties();
	//prop.ShowPane(!prop.IsVisible(), false, true);
	GtMainProperties& mainProp = GetWindowCreater()->GetMainProperties();
	mainProp.ShowPane(!mainProp.IsVisible(), false, true);
}


void CMainFrame::OnSaveObjectstate()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	GtMainProperties& mainProp = GetWindowCreater()->GetMainProperties();
	mainProp.OnSaveObjectstate();
	GtProperties& aniProp = GetWindowCreater()->GetAniProperties();
	aniProp.OnSaveObjectstate();
	GtTemplateListForm& form = m_wndTemplateTasksPane.GetTemplateList();
	form.OnSaveObjectstate();
}
