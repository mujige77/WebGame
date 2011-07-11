#include "StdAfx.h"
#include "CocosTool.h"
#include "CategoryAnimationManager.h"


CategoryAnimationManager::CategoryAnimationManager(void)
{
}


CategoryAnimationManager::~CategoryAnimationManager(void)
{
}

void CategoryAnimationManager::Create(CMFCRibbonBar* wndRibbonBar)
{
	CMFCRibbonCategory* pCategory = wndRibbonBar->GetCategory(1);
	CMFCRibbonPanel* pPanel1 = pCategory->GetPanel(2);
	//CMFCRibbonPanel* pPanel1 = pCategory->AddPanel(_T("Control"));
	
	CArray <CMFCRibbonBaseElement*, CMFCRibbonBaseElement*> arElements;
	pPanel1->GetElementsByID( IDC_ANIBIGINTIME, arElements  );
	mpAniStartTime = (CMFCRibbonEdit*)arElements.GetAt( 0 );

	arElements.RemoveAll();
	pPanel1->GetElementsByID( IDC_ANIENDTIME, arElements  );
	mpAniEndTime = (CMFCRibbonEdit*)arElements.GetAt( 0 );
	
	arElements.RemoveAll();
	pPanel1->GetElementsByID( IDC_ANICURRENTTIME, arElements  );
	mpAniTimeSpin = (CMFCRibbonEdit*)arElements.GetAt( 0 );

	arElements.RemoveAll();
	pPanel1->GetElementsByID( IDC_ANITIMESLIDER, arElements  );
	mpAniTimeSlider = (CMFCRibbonSlider*)arElements.GetAt( 0 );

	CWnd* ps =  wndRibbonBar->GetDlgItem( ID_SCALERANGE );
	if( ps )
	{
		CMFCSpinButtonCtrl* spin = 
			(CMFCSpinButtonCtrl*)wndRibbonBar->GetNextDlgGroupItem( ps );
		if( spin )
		{
			GtNumberString num;
			num.SetNumber( 3,  GtToolSettings::GetScalePercent() );
			spin->SetPos( GtToolSettings::GetScalePercent() );
			ps->SetWindowText( num.GetString().c_str() );
		}
	}
}