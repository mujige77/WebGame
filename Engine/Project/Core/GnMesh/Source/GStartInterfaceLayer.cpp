#include "GnGamePCH.h"
#include "GStartInterfaceLayer.h"
#include "GnITabCtrl.h"
#include "GnIButton.h"

GStartInterfaceLayer::GStartInterfaceLayer()
{
	
}

GStartInterfaceLayer::~GStartInterfaceLayer()
{
	
}

GnInterfaceGroup* GStartInterfaceLayer::CreateInterface(gtuint uiIndex
	, GnBaseSlot2<GnInterface*, GnIInputEvent*>* pReceiveSlot)
{
	GnInterfaceGroup* pGroup = NULL;
	switch (uiIndex)
	{
		case UI_START_TAB:
		{
			pGroup = CreateMenu();
		}
		break;
	}
	
	if( pGroup )
		pGroup->SubscribeClickedEvent( pReceiveSlot );
	return pGroup;
}

GnInterfaceGroup* GStartInterfaceLayer::CreateMenu()
{
	mpTabCtrl = GnITabCtrl::CreateTabCtrl( "StartScene/TabBackground.png", 60.0f, 28.0f );
	GnITabPage* pTabPage = NULL;	
	GnIButton* buttons = NULL;
	
	// create New tab page
	pTabPage = GnNew GnITabPage();
	mpTabCtrl->AddTabCreateButtonImage( pTabPage, "StartScene/TabButton.png", "StartScene/TabButton on.png" );
	
	// add buttons
	buttons = GnNew GnIButton( "StartScene/New/290_122.png", "StartScene/New/288_120.png", NULL );
	SetUIPosition( buttons, 290.0f, 122.0f );
	pTabPage->AddChild( buttons );
	
	buttons = GnNew GnIButton( "StartScene/New/290_161.png", "StartScene/New/288_159.png", NULL );
	SetUIPosition( buttons, 290.0f, 161.0f );
	pTabPage->AddChild( buttons );
	
	buttons = GnNew GnIButton( "StartScene/New/290_200.png", "StartScene/New/288_198.png", NULL );
	SetUIPosition( buttons, 290.0f, 200.0f );
	pTabPage->AddChild( buttons );
	
	// create Load tab page
	pTabPage = GnNew GnITabPage();
	mpTabCtrl->AddTabCreateButtonImage( pTabPage, "StartScene/TabButton.png", "StartScene/TabButton on.png");
	
	// add buttons
	buttons = GnNew GnIButton( "StartScene/Load/278_122.png", "StartScene/Load/276_120.png", NULL );
	buttons->SetIsHidePushDefaultButton( false );
	SetUIPosition( buttons, 278.0f, 122.0f );
	pTabPage->AddChild( buttons );
	
	buttons = GnNew GnIButton( "StartScene/Load/278_161.png", "StartScene/Load/276_158.png", NULL );
	buttons->SetIsHidePushDefaultButton( false );
	SetUIPosition( buttons, 278.0f, 161.0f );
	pTabPage->AddChild( buttons );
	
	buttons = GnNew GnIButton( "StartScene/Load/278_200.png", "StartScene/Load/276_197.png", NULL );
	buttons->SetIsHidePushDefaultButton( false );
	SetUIPosition( buttons, 278.0f, 200.0f );
	pTabPage->AddChild( buttons );
	
	mpTabCtrl->SetUIPoint( 247.0f, 73.0f );
	mpTabCtrl->SetRect( 247.0f, 59.0f, 247.0f + 205.0f, 59.0f + 215.0f );
	mpTabCtrl->SetActiveTab( 0 );
	AddChild( mpTabCtrl );
	return mpTabCtrl;
}