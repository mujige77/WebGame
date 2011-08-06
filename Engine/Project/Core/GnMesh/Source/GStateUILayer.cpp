#include "GnGamePCH.h"
#include "GStateUILayer.h"
#include "GnITabCtrl.h"
#include "GnIButton.h"
#include "GnINumberLabel.h"

GStateUILayer::GStateUILayer()
{
	
}

GStateUILayer::~GStateUILayer()
{
	
}

GnInterfaceGroup* GStateUILayer::CreateInterface(gtuint uiIndex
	, GnBaseSlot2<GnInterface*, GnIInputEvent*>* pReceiveSlot)
{
	GnInterfaceGroup* pGroup = NULL;
	switch (uiIndex)
	{
		case UI_STATE_ITEMTAB:
		{
			
		}
		break;
		case UI_STATE_UNITTAB:
		{
		}
		break;
		case UI_STATE_USERTAB:
		{
			
		}
		break;
		case UI_STATE_OTHERUI:
		{
			pGroup = CreateOtherUI();
		}
		break;
	}
	
	if( pGroup )
		pGroup->SubscribeClickedEvent( pReceiveSlot );
	return pGroup;
}

GnInterfaceGroup* GStateUILayer::CreateMenu()
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
	SetUIPosition( buttons, 278.0f, 122.0f );
	pTabPage->AddChild( buttons );
	
	buttons = GnNew GnIButton( "StartScene/Load/278_161.png", "StartScene/Load/276_158.png", NULL );
	SetUIPosition( buttons, 278.0f, 161.0f );
	pTabPage->AddChild( buttons );
	
	buttons = GnNew GnIButton( "StartScene/Load/278_200.png", "StartScene/Load/276_197.png", NULL );
	SetUIPosition( buttons, 278.0f, 200.0f );
	pTabPage->AddChild( buttons );
	
	mpTabCtrl->SetUIPoint( 247.0f, 73.0f );
	mpTabCtrl->SetRect( 247.0f, 59.0f, 247.0f + 205.0f, 59.0f + 215.0f );
	mpTabCtrl->SetActiveTab( 0 );
	AddChild( mpTabCtrl );
	return mpTabCtrl;
}

GnInterfaceGroup* GStateUILayer::CreateOtherUI()
{
	GnInterfaceGroup* group = GnNew GnInterfaceGroup();
	GnIButton* buttons = NULL;
	GnINumberLabel* label = NULL;
	// add buttons
	buttons = GnNew GnIButton( "Upgrade/424_8.png", NULL, NULL );
	SetUIPosition( buttons, 424.0f, 8.0f );
	group->AddChild( buttons );
	
	gstring fullPath;
	GetFullPathFromWorkPath( "Upgrade/MoneyNumber.png", fullPath );
	
	label = GnNew GnINumberLabel( NULL, 5 );
	label->Init( "0", fullPath.c_str(), 16, 20, '.' );
	SetUIPosition( label, 111.0f, 276.0f );
	group->AddChild( label );
	
	label = GnNew GnINumberLabel( NULL, 10 );
	label->Init( "0", fullPath.c_str(), 16, 20, '.' );
	SetUIPosition( label, 332.0f, 276.0f );
	group->AddChild( label );
	
	group->SetRect( 424.0f, 8.0f, 458.0f, 39.0f );
	AddChild( group, INTERFACE_ZORDER );
	return group;
}