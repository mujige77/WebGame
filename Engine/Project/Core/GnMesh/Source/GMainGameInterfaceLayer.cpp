#include "GnMeshPCH.h"
#include "GnGamePCH.h"
#include "GMainGameInterfaceLayer.h"
#include "GnIButton.h"
#include "GEnergyBar.h"
#include "GnIProgressBar.h"
#include "GGameDefine.h"
#include "GItemInfo.h"
#include "GPlayingDataManager.h"
#include "GUserHaveItem.h"

GMainGameInterfaceLayer::GMainGameInterfaceLayer() : mForcesButtonInfos( GInterfaceLayer::FORCESBT_NUM )
	, mpForcesButtonGroup( NULL ), mpSkillButtonGroup( NULL ), mpForcesEnergyBar( NULL )
	, mForcesInputEvent( this, &GMainGameInterfaceLayer::InputForcesButton )
{
	
}
GnInterfaceGroup* GMainGameInterfaceLayer::CreateInterface(gtuint uiIndex
	, GnBaseSlot2<GnInterface*, GnIInputEvent*>* pReceiveSlot)
{
	GnInterfaceGroup* pGroup = NULL;
	switch (uiIndex)
	{
		case UI_MAIN_CONTROLLERS:
		{
			pGroup = CreateMainController();
		}
		break;
		case UI_MAIN_FORCESBUTTONS:
		{
			pGroup = CreateMainForcesButtons();			
			pGroup->SubscribeClickedEvent( &mForcesInputEvent );
			mpForcesButtonGroup = pGroup;
		}
		break;
		case UI_MAIN_SKILL:
		{
			pGroup = CreateMainSkillButtons();
			mpSkillButtonGroup = pGroup;
		}
		break;
		case UI_MAIN_OTHERUI:
		{
			pGroup = CreateMainMenu();
		}
		break;
		case UI_MAIN_DLG_PAUSE:
			pGroup = CreatePauseDialog();
			break;
		case UI_MAIN_DLG_WINSCORE:
			pGroup = CreateWinScoreDialog();
			break;
		case UI_MAIN_DLG_LOSE:
			pGroup = CreateLoseDialog();
			break;
	}
	
	if( pGroup )
	{
		pGroup->SubscribeClickedEvent( pReceiveSlot );
	}
	return pGroup;
}

void GMainGameInterfaceLayer::Update(float fTime)
{
	if( mpForcesButtonGroup )
		mpForcesButtonGroup->Update( fTime );
	
	if( mpSkillButtonGroup )
		mpSkillButtonGroup->Update( fTime );
	UpdateButtonState();
}

GnInterfaceGroup* GMainGameInterfaceLayer::CreateMainMenu()
{
	GnInterfaceGroup* group = GnNew GnInterfaceGroup();
	
	GnIButton* buttons = NULL;
	buttons = GnNew GnIButton( "Controll/454_0.png", NULL, NULL );
	SetUIPosition( buttons, 454.0f, 0.0f );
	group->AddChild( buttons );
	group->AddPersonalChild( buttons );
	
	AddChild( group, 1 );
	return group;
}

GnInterfaceGroup* GMainGameInterfaceLayer::CreateMainController()
{
	GnIButton* buttons[MOVE_NUM];
	buttons[MOVELEFT] = GnNew GnIButton( "Controll/3_247.png", "Controll/3_247 on.png", NULL );
	SetUIPosition( buttons[MOVELEFT], 3, 247 );

	
    buttons[MOVERIGHT] = GnNew GnIButton( "Controll/58_247.png", "Controll/58_247 on.png", NULL );
	SetUIPosition( buttons[MOVERIGHT], 58, 247 );
	
    buttons[MOVEUP] = GnNew GnIButton( "Controll/37_223.png", "Controll/37_223 on.png", NULL );	
	SetUIPosition( buttons[MOVEUP], 37, 223 );	
	
	buttons[MOVEDOWN] = GnNew GnIButton( "Controll/38_268.png", "Controll/38_268 on.png", NULL );
	SetUIPosition( buttons[MOVEDOWN], 38, 268 );
	
	buttons[MOVELEFTUP] = GnNew GnIButton( "Controll/3_224.png" );
	SetUIPosition( buttons[MOVELEFTUP], 3, 224 );
	
	buttons[MOVERIGHTUP] = GnNew GnIButton( "Controll/78_224.png" );
	SetUIPosition( buttons[MOVERIGHTUP], 78, 224 );
	
	buttons[MOVELEFTDOWN] = GnNew GnIButton( "Controll/3_287.png" );
	SetUIPosition( buttons[MOVELEFTDOWN], 3, 287 );
	
	buttons[MOVERIGHTDOWN] = GnNew GnIButton( "Controll/78_287.png"  );
	SetUIPosition( buttons[MOVERIGHTDOWN], 78, 287 );
	
	GnInterfaceGroup* pGroup = GnNew GnInterfaceGroup();
	pGroup->SetIsEnablePushMove( true );
	pGroup->SetRect( 0.5f, 219.0f, 0.5f+115.0f, 219.0f+104.0f );
	for (gtuint i = 0; i < MOVE_NUM ; i++ )
	{
		pGroup->AddChild( buttons[i] );
	}
	
	AddChild( pGroup, 1 );
	return pGroup;
}

GnInterfaceGroup* GMainGameInterfaceLayer::CreateMainForcesButtons()
{
	GnInterfaceGroup* group = GnNew GnInterfaceGroup();
	group->SetRect( 120.0f, 219.0f, 120.0f+232.0f, 219.0f+100.0f );
	
	GnIButton* buttons[FORCESBT_NUM];
	buttons[BT_C2] = GnNew GnIButton( "Controll/125_223.png", NULL, "Controll/125_223G.png" );
	SetUIPosition( buttons[BT_C2], 125.0f, 223.0f, eIndexC2 );
	
	
    buttons[BT_C3] = GnNew GnIButton( "Controll/170_223.png", NULL, "Controll/170_223G.png" );
	SetUIPosition( buttons[BT_C3], 170.0f, 223.0f, eIndexC3 );
	
    buttons[BT_C4] = GnNew GnIButton( "Controll/215_223.png", NULL, "Controll/215_223G.png" );	
	SetUIPosition( buttons[BT_C4], 215.0f, 223.0f, eIndexC4 );
	
	buttons[BT_C5] = GnNew GnIButton( "Controll/260_223.png", NULL, "Controll/260_223G.png"
		, GnIButton::TYPE_DISABLE );
	SetUIPosition( buttons[BT_C5], 260.0f, 223.0f, eIndexC5 );
	
	buttons[BT_C6] = GnNew GnIButton( "Controll/305_223.png", NULL, "Controll/305_223G.png"
		, GnIButton::TYPE_DISABLE );
	SetUIPosition( buttons[BT_C6], 305.0f, 223.0f, eIndexC6 );
	
    buttons[BT_C7] = GnNew GnIButton( "Controll/125_268.png", NULL, "Controll/125_268G.png"
		,GnIButton::TYPE_DISABLE );
	SetUIPosition( buttons[BT_C7], 125.0f, 268.0f, eIndexC7 );
	
    buttons[BT_C8] = GnNew GnIButton( "Controll/170_268.png", NULL, "Controll/170_268G.png"
		, GnIButton::TYPE_DISABLE );
	SetUIPosition( buttons[BT_C8], 170.0f, 268.0f, eIndexC8 );
	
	buttons[BT_C9] = GnNew GnIButton( "Controll/215_268.png", NULL, "Controll/215_268G.png",
		GnIButton::TYPE_DISABLE );
	SetUIPosition( buttons[BT_C9], 215.0f, 268.0f, eIndexC9 );
	
	buttons[BT_C10] = GnNew GnIButton( "Controll/260_268.png", NULL, "Controll/260_268G.png",
		GnIButton::TYPE_DISABLE );
	SetUIPosition( buttons[BT_C10], 260.0f, 268.0f, eIndexC10 );
	
	buttons[BT_C11] = GEnergyBar::Create( 100, 0.5, "Controll/305_268.png" );
	SetUIPosition( buttons[BT_C11], 305.0f, 268.0f );
	mpForcesEnergyBar = (GEnergyBar*)buttons[BT_C11];
	
	
	for (gtuint i = 0; i < FORCESBT_NUM; i++ )		
		group->AddChild( buttons[i] );
	
	
	
	GnInterface* energyBarLine = GnNew GnInterface( "Controll/309_288.png" );
	SetUIPosition( energyBarLine, 309.0f, 288.0f );
	group->AddChild( energyBarLine );
	
	AddChild( group, 1 );	
	
	SetForcesButtonInfo( buttons );
	return group;
}
GnInterfaceGroup* GMainGameInterfaceLayer::CreateMainSkillButtons()
{
	static const float position[4][2] =
	{
		{ 375.0f, 223.0f }, { 420.0f, 223.0f }, { 375.0f, 268.0f }, { 420.0f, 268.0f }
	};
	
	GnInterfaceGroup* group = GnNew GnInterfaceGroup();
	group->SetRect( 362.0f, 218.0f, 362.0f+120.0f, 218.0f+100.0f );
	
	gstring filename = GetFullPath( "ItemInfo.sqlite" );
	GnSQLite sqlite( filename.c_str() );
	
	GUserHaveItem* haveItem = GPlayingDataManager::GetSingleton()->GetPlayingHaveItem();
	GPlayingData* playingData = GPlayingDataManager::GetSingleton()->GetPlayingPlayerData();
	haveItem->OpenPlayerItem( playingData->GetPlayerName() );
	
	GnList<GUserHaveItem::Item> haveItems;
	haveItem->GetItems( eEquip, haveItems );	
	
	GnListIterator<GUserHaveItem::Item> iter = haveItems.GetIterator();
	gtuint itemCount = 0;
	while( iter.Valid() )
	{
		GUserHaveItem::Item& item = iter.Item();
		gtuint itemIndex = item.mIndex;
		
		GnSQLiteQuery query = sqlite.ExecuteSingleQuery( "SELECT * FROM GameItem WHERE idx=%d",
			item.mIndex );
		if( query.IsEof() )
		{
			GnLogA( "error execute query - getting UnitButton %d", item.mIndex );
			continue;
		}
		
		float cooltime = query.GetFloatField( 2 );
		
		GnIButton* buttons = GnNew GnIButton( GetItemInfo()->GetGameIconFileName( itemIndex ) );
		buttons->SetTegID( item.mIndex );
		buttons->SetIsDisableCantpushBlind( false );
		buttons->SetIsEnableCoolTime( true );
		buttons->SetCoolTime( cooltime );
		SetUIPosition( buttons, position[itemCount][0], position[itemCount][1] );
		
		group->AddChild( buttons );
		
		iter.Forth();
		++itemCount;
		if( ENABLE_MAX_EQUIP <= itemCount )
			break;
	}
	
	for ( ; itemCount < 4 ; itemCount++ )
	{
		GnIButton* buttons = GnNew GnIButton( NULL, NULL, "375_223G.png" );
		SetUIPosition( buttons, position[itemCount][0], position[itemCount][1] );
		group->AddChild( buttons );
	}
	
	haveItem->Close();
	
	AddChild( group, 1 );	
//	GnInterface* energyBarLine = GnNew GnInterface( "Controll/309_288.png" );
//	SetUIPosition( energyBarLine, 425.0f, 288.0f );
//	group->AddChild( energyBarLine );
	return group;
}

GnInterfaceGroup* GMainGameInterfaceLayer::CreatePauseDialog()
{
	GnInterfaceGroup* group = GnNew GnInterfaceGroup();	
	group->SetRect( 0.0f, 0.0f, GetGameState()->GetGameWidth(), GetGameState()->GetGameHeight() );
	
	GnInterface* label = NULL;
	label = GnNew GnInterface( "Controll/pause/354_26.png" );
	SetUIPosition( label, 354.0f, 26.0f );
	group->AddChild( label );
	
	
	GnIButton* buttons = NULL;
	// next button
	buttons = GnNew GnIButton( "Controll/pause/368_80.png", NULL, NULL );
	buttons->SetTegID( DIALOG_LEVELSELECT_BUTTON );
	SetUIPosition( buttons, 368.0f, 80.0f );
	group->AddChild( buttons );
	
	// prev button
	buttons = GnNew GnIButton( "Controll/pause/381_43.png", NULL, NULL );
	buttons->SetTegID( DIALOG_RESUME_BUTTON );
	SetUIPosition( buttons, 381.0f, 43.0f );
	group->AddChild( buttons );
	return group;
}

GnInterfaceGroup* GMainGameInterfaceLayer::CreateWinScoreDialog()
{
	GnInterfaceGroup* group = GnNew GnInterfaceGroup();	
	group->SetRect( 0.0f, 0.0f, GetGameState()->GetGameWidth(), GetGameState()->GetGameHeight() );
	
	// background
	GnInterface* back = NULL;
	back = GnNew GnInterface( "Controll/score/143_50.png" );
	SetUIPosition( back, 143.0f, 26.0f );
	group->AddChild( back );
	
	GnIButton* buttons = NULL;
	// replay button
	buttons = GnNew GnIButton( "Controll/score/165_142.png", "Controll/score/165_142a.png", NULL );
	buttons->SetTegID( DIALOG_REPLAY_BUTTON );
	SetUIPosition( buttons, 165.0f, 142.0f );
	group->AddChild( buttons );
	
	// next button
	buttons = GnNew GnIButton( "Controll/score/251_142.png", "Controll/score/251_142a.png", NULL );
	buttons->SetTegID( DIALOG_NEXT_BUTTON );
	SetUIPosition( buttons, 251.0f, 142.0f );
	group->AddChild( buttons );
	
	gstring fullPath;
	GetFullPathFromWorkPath( "Controll/score/232_113.png", fullPath );	
	GnINumberLabel* label = GnNew GnINumberLabel( NULL, 10 );
	label->Init( "0", fullPath.c_str(), 12, 14, '.' );
	label->SetTegID( DIALOG_TIME_NUM );
	SetUIPosition( label, 232.0f, 113.0f );	
	group->AddChild( label );
	
	GetFullPathFromWorkPath( "Controll/score/232_113.png", fullPath );	
	label = GnNew GnINumberLabel( NULL, 10 );
	label->Init( "0", fullPath.c_str(), 12, 14, '.' );
	label->SetTegID( DIALOG_MONEY_NUM );
	SetUIPosition( label, 232.0f, 156.0f );	
	group->AddChild( label );
	
	return group;
}

GnInterfaceGroup* GMainGameInterfaceLayer::CreateLoseDialog()
{
	GnInterfaceGroup* group = GnNew GnInterfaceGroup();	
	group->SetRect( 0.0f, 0.0f, GetGameState()->GetGameWidth(), GetGameState()->GetGameHeight() );
	
	// background
	GnInterface* back = NULL;
	back = GnNew GnInterface( "Controll/score/143_50.png" );
	SetUIPosition( back, 143.0f, 26.0f );
	group->AddChild( back );
	
	
	GnIButton* buttons = NULL;
	// replay button
	buttons = GnNew GnIButton( "Controll/score/165_142.png", "Controll/score/165_142a.png", NULL );
	SetUIPosition( buttons, 165.0f, 142.0f );
	group->AddChild( buttons );
	
	// next button
	buttons = GnNew GnIButton( "Controll/score/251_142.png", "Controll/score/251_142a.png", NULL );
	SetUIPosition( buttons, 251.0f, 142.0f );
	group->AddChild( buttons );
	
	gstring fullPath;
	GetFullPathFromWorkPath( "Controll/score/232_113.png", fullPath );	
	GnINumberLabel* label = GnNew GnINumberLabel( NULL, 10 );
	label->Init( "0", fullPath.c_str(), 12, 14, '.' );
	SetUIPosition( label, 232.0f, 113.0f );	
	group->AddChild( label );
	
	GetFullPathFromWorkPath( "Controll/score/232_113.png", fullPath );	
	label = GnNew GnINumberLabel( NULL, 10 );
	label->Init( "0", fullPath.c_str(), 12, 14, '.' );
	SetUIPosition( label, 232.0f, 156.0f );	
	group->AddChild( label );
	
	return group;
}

bool GMainGameInterfaceLayer::SetForcesButtonInfo(GnIButton** ppButtons)
{	
	GUserHaveItem* haveItem = GetCurrentHaveItem();
	
	gstring filename = GetFullPath( "ItemInfo.sqlite" );
	GnSQLite sqlite( filename.c_str() );
	for (gtuint i = 0; i < FORCESBT_NUM - 1 ; i++ )
	{
		GnSQLiteQuery query = sqlite.ExecuteSingleQuery( "SELECT * FROM GameItem WHERE idx=%d",
			i + INDEX_UNIT + 1 );
		if( query.IsEof() )
		{
			GnLogA( "error execute query - getting UnitButton %d", i + INDEX_UNIT + 1 );
			continue;
		}
	
		guint32 itemLevel = haveItem->GetItemLevel( ppButtons[i]->GetTegID() );
		if( itemLevel > 0 )
			ppButtons[i]->SetIsDisable( false );
		else
			ppButtons[i]->SetIsDisable( true );
		
		float energy = query.GetFloatField( 1 );
		float cooltime = query.GetFloatField( 2 );
		ppButtons[i]->SetIsDisableCantpushBlind( false );
		ppButtons[i]->SetIsCantPush( true );
		ppButtons[i]->SetIsEnableCoolTime( true );
		ppButtons[i]->SetCoolTime( cooltime );
		
		ButtonInfo& btInfo = mForcesButtonInfos.GetAt( i );
		btInfo.SetButton( ppButtons[i] );
		btInfo.SetCanPushEnergy( energy );
		btInfo.SetCoolTime( cooltime );
		btInfo.SetItemLevel( itemLevel );
	}
	
	haveItem->Close();
	return true;
}

void GMainGameInterfaceLayer::UpdateButtonState()
{
	const gtuint num = FORCESBT_NUM - 1;
	for (gtuint i = 0; i < num ; i++ )
	{
		ButtonInfo& btInfo = mForcesButtonInfos.GetAt( i );
		if( btInfo.GetButton()->IsDisable() )
			continue;
		if( mpForcesEnergyBar->GetCurrentEnergy() >= btInfo.GetCanPushEnergy() )
		{
			btInfo.GetButton()->SetIsCantPush( false );
		}
		else
		{
			if( btInfo.GetButton()->IsCantPush() == false )
				btInfo.GetButton()->SetIsCantPush( true );
		}
	}
}

void GMainGameInterfaceLayer::InputForcesButton(GnInterface* pInterface, GnIInputEvent* pEvent)
{
	if( pEvent->GetEventType() == GnIInputEvent::PUSH )
	{
		for (gtuint i = 0; i < FORCESBT_NUM ; i++ )
		{
			ButtonInfo& btInfo = mForcesButtonInfos.GetAt( i );		
			if( btInfo.GetButton() == pInterface )
			{
				mpForcesEnergyBar->SetCurrentEnergy( 
					mpForcesEnergyBar->GetCurrentEnergy() - btInfo.GetCanPushEnergy() );
				break;
			}
		}
	}
}