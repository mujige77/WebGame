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
	mpTabCtrl = GnITabCtrl::CreateTabCtrl( "StartScene/243_83.png", 15.0f, -3.0f );
	if( mpTabCtrl == NULL )
		return NULL;
		
	GnITabPage* pTabPage = NULL;	
	GnIButton* buttons = NULL;
	
	// create New tab page
	pTabPage = GnNew GnITabPage();
	mpTabCtrl->AddTabCreateButtonImage( pTabPage, "StartScene/259_57 a.png", "StartScene/259_57.png" );
	
	// add buttons
	buttons = GnNew GnIButton( "StartScene/level select/277_121.png"
		, "StartScene/level select/276_120 276_158 276_197.png", NULL );
	buttons->SetIsHidePushDefaultButton( false );
	buttons->SetTegID( BT_SELECT_EASY );
	SetUIPosition( buttons, 277.0f, 121.0f );
	pTabPage->AddChild( buttons );
	
	buttons = GnNew GnIButton( "StartScene/level select/277_160.png"
		, "StartScene/level select/276_120 276_158 276_197.png", NULL );
	buttons->SetIsHidePushDefaultButton( false );
	buttons->SetTegID( BT_SELECT_NORMAL );
	SetUIPosition( buttons, 277.0f, 161.0f );
	pTabPage->AddChild( buttons );
	
	buttons = GnNew GnIButton( "StartScene/level select/277_198.png"
		, "StartScene/level select/276_120 276_158 276_197.png", NULL );
	buttons->SetIsHidePushDefaultButton( false );
	buttons->SetTegID( BT_SELECT_HARD );
	SetUIPosition( buttons, 277.0f, 200.0f );
	pTabPage->AddChild( buttons );
	
	// create Load tab page
	pTabPage = GnNew GnITabPage();
	mpTabCtrl->AddTabCreateButtonImage( pTabPage, "StartScene/375_57 a.png", "StartScene/375_57.png");
	
	// add buttons
	buttons = GnNew GnIButton( "StartScene/option/289_121.png"
		, "StartScene/option/288_120 288_159.png", NULL );
	buttons->SetIsHidePushDefaultButton( false );
	buttons->SetTegID( BT_SOUNDON );
	SetUIPosition( buttons, 289.0f, 121.0f );
	pTabPage->AddChild( buttons );
	
	buttons = GnNew GnIButton( "StartScene/option/289_160.png"
		, "StartScene/option/288_120 288_159.png", NULL );
	buttons->SetIsHidePushDefaultButton( false );
	buttons->SetTegID( BT_SOUNDOFF );
	SetUIPosition( buttons, 289.0f, 160.0f );
	pTabPage->AddChild( buttons );
	
	buttons = GnNew GnIButton( "StartScene/option/289_198.png"
		, "StartScene/option/288_120 288_159.png", NULL );
	buttons->SetIsHidePushDefaultButton( false );
	buttons->SetTegID( BT_RESETGAME );
	SetUIPosition( buttons, 289.0f, 198.0f );
	pTabPage->AddChild( buttons );
	
	mpTabCtrl->SetUIPoint( 243.0f, 83.0f );
	mpTabCtrl->SetRect( 243.0f, 59.0f, 247.0f + 205.0f, 59.0f + 215.0f );
	mpTabCtrl->SetActiveTab( 0 );
	AddChild( mpTabCtrl );
	return mpTabCtrl;
}