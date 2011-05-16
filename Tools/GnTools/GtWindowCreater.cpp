#include "StdAfx.h"
#include "GnTools.h"
#include "GtWindowCreater.h"

GtWindowCreater* GtWindowCreater::mInstance = NULL;
GtWindowCreater* GtWindowCreater::GetInstance()
{
	return mInstance;
}


GtWindowCreater::GtWindowCreater(void)
{
}


GtWindowCreater::~GtWindowCreater(void)
{
}

GtWindowCreater* GtWindowCreater::Create()
{
	GnAssert( mInstance == NULL );
	mInstance = new GtWindowCreater();
	return mInstance;
}

void GtWindowCreater::Destroy()
{
	delete mInstance;
}

bool GtWindowCreater::CreateUsedWindows(CMDIFrameWndEx* pParent, BOOL bHiColorIcons)
{
	CString strPropertiesWnd;
	BOOL bNameValid = strPropertiesWnd.LoadString(IDS_MAINPROPERTIES_WND);
	ASSERT(bNameValid);
	if (!mMainProp.Create(strPropertiesWnd, pParent, CRect(0, 0, 200, 200), TRUE, ID_VIEW_MAINPROPERTIES,
		WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_RIGHT | CBRS_FLOAT_MULTI))
	{
		TRACE0("속성 창을 만들지 못했습니다.\n");
		return false; // 만들지 못했습니다.
	}

	bNameValid = strPropertiesWnd.LoadString(IDS_ANIPROPERTIES_WND);
	ASSERT(bNameValid);
	if (!mAniProperties.Create(strPropertiesWnd, pParent, CRect(0, 0, 200, 200), TRUE, ID_VIEW_ANIPROPERTIES,
		WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_RIGHT | CBRS_FLOAT_MULTI))
	{
		TRACE0("속성 창을 만들지 못했습니다.\n");
		return false; // 만들지 못했습니다.
	}

	SetDockingWindowIcons( bHiColorIcons );
	return true;
}

void GtWindowCreater::SetDockingWindows(CMDIFrameWndEx* pParent)
{
	if( mAniProperties.GetSafeHwnd() )
	{
		mAniProperties.EnableDocking(CBRS_ALIGN_ANY);
		pParent->DockPane( &mAniProperties );
	}

	if( mMainProp.GetSafeHwnd() )
	{
		mMainProp.EnableDocking(CBRS_ALIGN_ANY);
		pParent->DockPane( &mMainProp );
	}
}

void GtWindowCreater::SetDockingWindowIcons(BOOL bHiColorIcons)
{
	HICON hPropertiesBarIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(),
		MAKEINTRESOURCE(bHiColorIcons ? IDI_PROPERTIES_WND_HC : IDI_PROPERTIES_WND), IMAGE_ICON,
		::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
	mAniProperties.SetIcon(hPropertiesBarIcon, FALSE);
}